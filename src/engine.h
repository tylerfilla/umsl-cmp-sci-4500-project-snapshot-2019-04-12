/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

struct EngineImpl;
struct EngineOp;

/** The program engine. */
class Engine {
  /** PImpl. */
  std::unique_ptr<EngineImpl> impl;

public:
  Engine();

  Engine(const Engine& rhs) = delete;

  Engine(Engine&& rhs) = delete;

  ~Engine();

  /**
   * Execute an operation.
   *
   * @param op The operation
   */
  void execute(EngineOp& op);
};

#endif // #ifndef ENGINE_H
