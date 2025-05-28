#include "drivers/spi_mux.h"
#include "quantum.h"

void keyboard_pre_init_user(void) {
    spi_mux_pio_init();
}
