/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef ENGINE_OP_LIST_FRIEND_OP_H
#define ENGINE_OP_LIST_FRIEND_OP_H

#include "../engine_op.h"

namespace engine_op {

/** Operation to list friends. */
class ListFriendOp : public EngineOp {
public:
  /** A list mode. */
  enum class Mode {
    all,
    targeted,
  };

private:
  /** The list mode. */
  Mode m_mode;

  /** The target friend ID. */
  int m_friend_id;

public:
  ListFriendOp();

  ListFriendOp(const ListFriendOp& rhs) = delete;

  ListFriendOp(ListFriendOp&& rhs) noexcept = delete;

  ~ListFriendOp() final;

  ListFriendOp& operator=(const ListFriendOp& rhs) = delete;

  ListFriendOp& operator=(ListFriendOp&& rhs) noexcept = delete;

  /**
   * @return The list mode
   */
  Mode get_mode() const {
    return m_mode;
  }

  /**
   * @param p_mode The list mode
   */
  void set_mode(Mode p_mode) {
    m_mode = p_mode;
  }

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

#endif // #ifndef ENGINE_OP_LIST_FRIEND_OP_H
