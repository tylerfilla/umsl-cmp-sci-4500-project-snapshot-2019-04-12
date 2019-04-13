/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <iostream>
#include "engine.h"

struct EngineImpl {
};

Engine::Engine() : impl() {
  impl = std::make_unique<EngineImpl>();
}

Engine::~Engine() = default;

void Engine::execute(EngineOp& op) {
  std::cout << "engine\n";
}
