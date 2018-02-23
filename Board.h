//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_BOARD_H
#define HOARDINGCPPVERSION_BOARD_H
#include <vector>
#include <string>
#include "Space.h"
#include "Rules.h"

namespace Monopoly {
  //class Space;
  class Board {
   public:
    Board(const std::string& boardFileName, const Rules& rules);
    void display() const;
    Space& getSpace(int spaceNum);
    Space& getGoSpace();
    int getNumSpaces() const;
    const std::vector<Space>& getSpaces() const;
    void removeAllPlayers();
   private:
    std::vector<Space> spaces;
    unsigned long calc_length_of_longest_space_name() const;

  };
}

#endif //HOARDINGCPPVERSION_BOARD_H
