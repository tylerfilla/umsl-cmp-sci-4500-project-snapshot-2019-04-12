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
#define VERSION_MAJOR __version_major

/**
 * The program version minor number.
 *
 * This number increments for backward-compatible changes and resets when the
 * major number changes.
 */
#define VERSION_MINOR __version_minor

/**
 * The program version patch number.
 *
 * This number increments for small tweaks and bugfixes and resets when the
 * major and minor numbers change.
 */
#define VERSION_PATCH __version_patch

/** The program version timestamp. */
#define VERSION_TIMESTAMP __DATE__ " " __TIME__

/** The program version control branch name. */
#define VERSION_VCS_BRANCH __git_refspec_str

/** The program version control commit hash. */
#define VERSION_VCS_HASH __git_hash_str

#endif // #ifndef VERSION_H
