/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef ENGINE_OP_START_INTERACTIVE_OP_H
#define ENGINE_OP_START_INTERACTIVE_OP_H

#include "../engine_op.h"

namespace engine_op {

/** Operation to start interactive usage. */
class StartInteractiveOp : public EngineOp {
public:
  StartInteractiveOp();

  StartInteractiveOp(const StartInteractiveOp& rhs) = delete;

  StartInteractiveOp(StartInteractiveOp&& rhs) noexcept = delete;

  ~StartInteractiveOp() final;

  StartInteractiveOp& operator=(const StartInteractiveOp& rhs) = delete;

  StartInteractiveOp& operator=(StartInteractiveOp&& rhs) noexcept = delete;
};

} // namespace engine_op

#endif // #ifndef ENGINE_OP_START_INTERACTIVE_OP_H
