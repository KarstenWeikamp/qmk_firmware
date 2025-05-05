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

#pragma once

#define HAL_USE_SPI TRUE
#define HAL_USE_SPI TRUE // enable ChibiOS SPI driver:contentReference[oaicite:0]{index=0}
#define HAL_USE_DMA TRUE // enable DMA support on RP2040
#define HAL_USE_PAL TRUE // enable GPIO (PAL) if using pin callbacks
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_NONE

#include_next <halconf.h>