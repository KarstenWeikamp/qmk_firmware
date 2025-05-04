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

#include "debounce.h"
#include "quantum.h"
#include "matrix.h"

#include "pio.h"
#include "spi.h"

void matrix_init_custom(void) {
    // TODO: initialize hardware here
    custom_spi_init();
    mux_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    return matrix_has_changed;
}