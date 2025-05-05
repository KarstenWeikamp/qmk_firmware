// Copyright 2025 Karsten Weikamp (@KarstenWeikamp)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>

#include "hal.h"
#include "spi.h"

#define LEN (255)
uint8_t rxbuf[LEN];

// Configure SPI0 (RP2040_SSI0) as master, e.g. mode 0, 1MHz
const SPIConfig spi_cfg = {
    // On RP2040, only clock rate and polarity/phase matter; other fields are dummy.
    .end_cb = NULL,
};

inline void custom_spi_init(void) {
    spiStart(&SPID0, &spi_cfg);
}
inline void custom_irq_spi_rx(void) {
    spiStartReceiveI(&SPID0, 1, rxbuf);
}

inline void startup_dummy_read(void) {
    spiStartIgnore(&SPID0, 1);
}