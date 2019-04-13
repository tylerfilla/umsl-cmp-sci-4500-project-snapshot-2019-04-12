/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "global.h"

namespace {

global g__;

} // namespace

/** An immutable view of the global info. */
const global* const g = &g__;

/** A mutable view of the global info. */
global* const g_mut = &g__;
