//
// Created by mfbut on 1/23/2018.
//

#include "Move.h"
#include <iostream>

Monopoly::Move::Move() : action(MoveAction::ERROR) {}

Monopoly::Move::Move(const int moveNumber) {
  if (moveNumber == 1) {
    action = MoveAction::rollDice;
  } else if (moveNumber == 2) {
    action = MoveAction::leaveGame;
  } else {
    action = MoveAction::ERROR;
    std::cout << "Unrecognized move number " << moveNumber << " in Move constructor" << std::endl;
  }
}

bool Monopoly::Move::endsTurn() {
  return true;
}

Monopoly::MoveAction Monopoly::Move::getAction() const {
  return action;
}

