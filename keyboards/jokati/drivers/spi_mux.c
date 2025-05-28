#include <hal.h>
#include "hardware/pio.h"
#include "pio/mux.pio.h"
#include "pio/spi.pio.h"

#include "debug.h"

/*mux and CS pio*/
#define MUX_PIO pio1
#define DMUX_BASE (0)
#define DMUX_NUM_PINS (4)
#define MUX_CS_SIDESET_BASE (DMUX_BASE + DMUX_NUM_PINS)
#define MUX_CS_SIDESET_NUM_PINS (5)

static uint mux_program_offset    = 0;
static uint mux_pio_state_machine = 0;

/*bitbang spi pio*/
#define SPI_PIO pio1
#define SPI_PIO_CLK_DIV (8.0f)
#define SPI_CLOCK_PIN (MUX_CS_SIDESET_BASE + MUX_CS_SIDESET_NUM_PINS)
#define SPI_RX_PIN (SPI_CLOCK_PIN + 1)

static uint spi_program_offset    = 0;
static uint spi_pio_state_machine = 0;

static inline void mux_pio_init(pio_sm_config *sm_config) {
    for (int i = 0; i < DMUX_NUM_PINS + MUX_CS_SIDESET_NUM_PINS; i++) {
        pio_gpio_init(MUX_PIO, DMUX_BASE + i);
    }
    pio_sm_set_consecutive_pindirs(MUX_PIO, mux_pio_state_machine, DMUX_BASE, DMUX_NUM_PINS + MUX_CS_SIDESET_NUM_PINS, true);
    sm_config_set_out_pins(sm_config, DMUX_BASE, DMUX_NUM_PINS);
    sm_config_set_sideset_pins(sm_config, MUX_CS_SIDESET_BASE);

    sm_config_set_clkdiv(sm_config, 8.0f);

    sm_config_set_out_shift(sm_config, true, true, 32);

    pio_sm_init(MUX_PIO, mux_pio_state_machine, mux_program_offset, sm_config);
    pio_set_irq0_source_enabled(MUX_PIO, pis_interrupt0, true);
    pio_interrupt_clear(MUX_PIO, 0);
}

static inline void spi_pio_init(pio_sm_config *sm_config) {
    pio_gpio_init(SPI_PIO, SPI_CLOCK_PIN);
    pio_gpio_init(SPI_PIO, SPI_RX_PIN);

    pio_sm_set_pindirs_with_mask(SPI_PIO, spi_pio_state_machine, (1 << SPI_CLOCK_PIN), (1 << SPI_CLOCK_PIN) | (1 << SPI_RX_PIN));
    sm_config_set_sideset_pins(sm_config, SPI_CLOCK_PIN);
    sm_config_set_in_pins(sm_config, SPI_RX_PIN);

    sm_config_set_clkdiv(sm_config, SPI_PIO_CLK_DIV);
    sm_config_set_fifo_join(sm_config, PIO_FIFO_JOIN_RX);
    /*Disable spi miso input stabilizer to remove input latency*/
    hw_set_bits(&SPI_PIO->input_sync_bypass, 1u << SPI_RX_PIN);

    sm_config_set_in_shift(sm_config, true, true, 32);

    pio_sm_init(SPI_PIO, spi_pio_state_machine, spi_program_offset, sm_config);
    pio_set_irq1_source_enabled(SPI_PIO, pis_interrupt1, true);
    pio_interrupt_clear(SPI_PIO, 1);
}

void spi_mux_pio_init(void) {
    uint pio_idx = pio_get_index(SPI_PIO);
    hal_lld_peripheral_unreset(pio_idx == 0 ? RESETS_ALLREG_PIO0 : RESETS_ALLREG_PIO1);
    mux_pio_state_machine = pio_claim_unused_sm(MUX_PIO, false);
    spi_pio_state_machine = pio_claim_unused_sm(SPI_PIO, false);

    mux_program_offset = pio_add_program(MUX_PIO, &mux_program);
    spi_program_offset = pio_add_program(SPI_PIO, &spi_program);

    pio_sm_config mux_pio_cfg = mux_program_get_default_config(mux_program_offset);
    pio_sm_config spi_pio_cfg = spi_program_get_default_config(spi_program_offset);

    /*Configure pio specific behavior*/
    mux_pio_init(&mux_pio_cfg);
    spi_pio_init(&spi_pio_cfg);

    pio_sm_set_enabled(MUX_PIO, mux_pio_state_machine, true);
    pio_sm_set_enabled(SPI_PIO, spi_pio_state_machine, true);
}

void spi_mux_pio_mux_trigger_read(void) {
    for (int i = 0x3210; i <= 0xFEDC; i += 0x1111) {
        pio_sm_put_blocking(MUX_PIO, mux_pio_state_machine, i);
        while (pio_sm_get_rx_fifo_level(SPI_PIO, spi_pio_state_machine) != 0) {
            uint32_t word0 = pio_sm_get_blocking(SPI_PIO, spi_pio_state_machine);
            dprintf("Received word %lu", word0);
        }
    }
    return;
}
