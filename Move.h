//
// Created by mfbut on 1/23/2018.
//

#ifndef HOARDINGCPPVERSION_MOVE_H
#define HOARDINGCPPVERSION_MOVE_H

namespace Monopoly {
  enum class MoveAction { rollDice = 1, leaveGame = 2, ERROR };
  class Move {
   public:
    Move();
    MoveAction getAction() const;
    Move(const int moveNumber);
    bool endsTurn();
   private:
    MoveAction action;
  };
}

#endif //HOARDINGCPPVERSION_MOVE_H
