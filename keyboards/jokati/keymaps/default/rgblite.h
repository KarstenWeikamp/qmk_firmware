// Copyright 2022 Makoto Kurauchi (@MakotoKurauchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ws2812.h"

static inline void rgblite_init(void) {
    ws2812_init();
}