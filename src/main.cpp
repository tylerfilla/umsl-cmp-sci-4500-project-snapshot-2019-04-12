/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "global.h"

namespace coz {

void cmdargs() {
}

} // namespace coz

int main(int argc, const char** argv) {
  g_mut->argc = argc;
  g_mut->argv = argv;

  coz::cmdargs();
}
