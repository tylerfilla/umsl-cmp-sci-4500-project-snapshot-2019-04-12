/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef GLOBAL_H
#define GLOBAL_H

/** Global info. */
struct global {
  /** The program argument count. */
  int argc;

  /** The program argument vector. */
  const char** argv;
};

#ifdef __cplusplus
extern "C" {
#endif

/** An immutable view of the global info. */
extern const struct global* const g;

/** A mutable view of the global info. */
extern struct global* const g_mut;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef GLOBAL_H
