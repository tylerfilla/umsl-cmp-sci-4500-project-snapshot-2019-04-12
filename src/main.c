/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>
#include "version.h"

int main() {
  printf("cozmo %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
  printf("%s\n", VERSION_TIMESTAMP);
  printf("%s\n", VERSION_VCS_BRANCH);
  printf("%s\n", VERSION_VCS_HASH);
}
