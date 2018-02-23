//
// Created by mfbut on 1/20/2018.
//

#include "Board.h"
#include <iostream>
#include "MonopolyUtility.h"
#include "Player.h"

Monopoly::Board::Board(const std::string& boardFileName, const Rules& rules) {
  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  if (boardFile.good()) {
    boardFile.skip_field();
    const int numSpaces = boardFile.get_next_field_as_int();

    for (int i = 0; i < num_lines_to_skip; ++i) {
      boardFile.skip_line();
    }

    for (int i = 0; i < numSpaces; ++i) {
      spaces.emplace_back(boardFile, i, rules);
      //spaces.push_back(Space(boardFile, i, rules));
    }

    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}

void Monopoly::Board::display() const {

  //const std::string header("Space Number | Space Name | Owner | Players");

  //std::cout << header << std::endl;
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string upgrade("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags(); //what are these
  std::cout.setf(std::ios::left); //what are these

  std::cout << spaceNumber; std::cout << " | ";

  std::cout.width(Space::length_of_longest_space_name);
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << owner; std::cout << " | ";

  std::cout.width(Space::length_of_longest_space_name);
  std::cout << upgrade; std::cout << " | ";

  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spaces) { //change this for the upgrades
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space.display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);
}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  for (const auto& space : spaces) {
    space_names.emplace_back(space.getName());
  }
  return Utility::get_max_string_length(space_names);
}

Monopoly::Space& Monopoly::Board::getSpace(int spaceNum) {
  return spaces[spaceNum];
}

Monopoly::Space& Monopoly::Board::getGoSpace() {
  for (auto& space : spaces) {
    if (space.getSpaceType() == SpaceType::goSpace) {
      return space;
    }
  }
  //this line should never execute
  return spaces[0];
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spaces.size());
}

const std::vector<Monopoly::Space>& Monopoly::Board::getSpaces() const {
  return spaces;
}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spaces) {
    space.removeAllPlayers();
  }
}

