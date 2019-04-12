/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef VERSION_H
#define VERSION_H

/**
 * The program version major number.
 *
 * This number increments for breaking changes.
 */
#define VERSION_MAJOR __vmajor

/**
 * The program version minor number.
 *
 * This number increments for backward-compatible changes and resets when the
 * major number changes.
 */
#define VERSION_MINOR __vminor

/**
 * The program version patch number.
 *
 * This number increments for small tweaks and bugfixes and resets when the
 * major and minor numbers change.
 */
#define VERSION_PATCH __vpatch

#endif // #ifndef VERSION_H
