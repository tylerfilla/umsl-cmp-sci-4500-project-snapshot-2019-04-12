/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <iostream>
#include <pybind11/embed.h>
#include "engine.h"

namespace py = pybind11;

struct EngineImpl {
  /** The Python interpreter. */
  py::scoped_interpreter m_python;
};

Engine::Engine() : impl() {
  impl = std::make_unique<EngineImpl>();
}

Engine::~Engine() = default;

void Engine::execute(EngineOp& op) {
  py::eval("print('this is python code running')");
}
