/* Copyright 2025 Karsten Weikamp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "quantum.h"
#include "matrix.h"

#include "pio.h"
#include "spi.h"

void matrix_init_custom(void) {
    custom_spi_init();
    mux_init();
}

static void read_adc_row(uint8_t adc_num) {
    // Set cs of adc_num
    // gpio_write_pin_low(row_pins[adc_num]);
    // Init adc (first conversion of xc7468 is invalid)
    startup_dummy_read();

    mux_trigger_row_read();
    // After were done reading all values pull cs back up
    //  gpio_write_pin_high(row_pins[adc_num]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t idx = 0; idx < MATRIX_ROWS; idx++) {
        read_adc_row(idx);
    }

    return matrix_has_changed;
}