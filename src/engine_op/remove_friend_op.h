/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef ENGINE_OP_REMOVE_FRIEND_OP_H
#define ENGINE_OP_REMOVE_FRIEND_OP_H

#include "../engine_op.h"

namespace engine_op {

/** Operation to remove friends. */
class RemoveFriendOp : public EngineOp {
  /** The target friend ID. */
  int m_friend_id;

public:
  RemoveFriendOp();

  RemoveFriendOp(const RemoveFriendOp& rhs) = delete;

  RemoveFriendOp(RemoveFriendOp&& rhs) noexcept = delete;

  ~RemoveFriendOp() final;

  RemoveFriendOp& operator=(const RemoveFriendOp& rhs) = delete;

  RemoveFriendOp& operator=(RemoveFriendOp&& rhs) noexcept = delete;

  /**
   * @return The target friend ID
   */
  int get_friend_id() const {
    return m_friend_id;
  }

  /**
   * @param p_friend_id The target friend ID
   */
  void set_friend_id(int p_friend_id) {
    m_friend_id = p_friend_id;
  }
};

} // namespace engine_op

#endif // #ifndef ENGINE_OP_REMOVE_FRIEND_OP_H
