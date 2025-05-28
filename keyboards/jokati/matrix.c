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

#include "quantum.h"
#include "drivers/spi_mux.h"

#include "matrix.h"
#include "print.h"

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    dprint("HALLO\n");
    bool matrix_has_changed = false;
    spi_mux_pio_mux_trigger_read();
    print("Read\n");
    return matrix_has_changed;
}