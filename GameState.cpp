//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include "GameState.h"
#include "MonopolyUtility.h"
#include "Move.h"
#include "GameState.h"
#include "PropertyManager.h"

Monopoly::GameState::GameState(const std::string& RulesFileName,
                               const std::string& BoardFileName,
                               const std::string& RandomFileName,
                               const std::vector<std::string>& playerNames)
    : rules(RulesFileName),
      board(BoardFileName, rules),
      diceRoller(RandomFileName),
      turn_count(0),
      player_turn(0),
      players() {

  PropertyManager emptyPropertyManager(board);

  for (unsigned int i = 0; i < playerNames.size(); ++i) {
    players.emplace_back(i, playerNames[i], rules.getStarting_cash(), &board.getSpace(0), emptyPropertyManager);

  }

  /*
   * Placing the player on the space needed to be done after
   * all the players were created because the players'  locations
   * in memory keep moving as they get inserted into the players
   * vector
   */
  for (auto& player : players) {
    player.setOn(board.getGoSpace(), false);
  }

  Player::length_of_longest_player_name =
      Utility::max(Utility::get_max_string_length(playerNames), std::string("Owner").size()); //don't know what this does

}

void Monopoly::GameState::display() const {

  board.display();

}

std::vector<std::string> Monopoly::GameState::get_player_names() {
  int num_players;
  std::vector<std::string> names;

  std::cout << "Enter how many players will be playing: ";
  std::cin >> num_players;
  names.resize(num_players);

  for (int i = 0; i < num_players; ++i) {
    std::cout << "Enter the name of player " << i + 1<< ": ";
    std::cin >> names[i];
  }
  return names;
}

void Monopoly::GameState::playGame() {
  Move move;
  while (!isGameOver()){
    display();
    do {
      move = getCurrentPlayer().getMove();
      make_move(getCurrentPlayer(), move);
    } while (!move.endsTurn());
    changeTurn();
  }
  display();
  declareWinner();
}

/**
 * Check if the game is over or not
 * @return
 */
bool Monopoly::GameState::isGameOver() const {
  return players.size() <= static_cast<unsigned long>(rules.getNum_players_left_to_end_game())
      || (rules.isTurnLimit() && turn_count >= rules.getTurn_limit());
}

Monopoly::Player& Monopoly::GameState::getCurrentPlayer() { //returns reference to player
  return players[player_turn];
}

void Monopoly::GameState::make_move(Monopoly::Player& player, Monopoly::Move& move) {
  int mapSize = player.getPropertyManager().getEntireMap().size();
  if (move.getAction() == MoveAction::rollDice) {
    int spacesToMove = diceRoller.getDiceRoll();
    int newLocation = spacesToMove + player.getSpaceOn().getSpaceNumber();
    int timesPastGo = newLocation / board.getNumSpaces();

    std::cout << player.getName() <<", you rolled a " << spacesToMove << std::endl;

    // give the player their salary for passing go
    player.giveCash(board.getGoSpace().getSalary() * timesPastGo);

    newLocation %= board.getNumSpaces();
    player.moveTo(board.getSpace(newLocation));

    if (player.getCash() < 0) {
      removeFromGame(player);
    }
  } else if (move.getAction() == MoveAction::upgradeProperty) {
    for(int i =0; i < mapSize; i++) {
      if (player.ownsAllPropertiesInSet(i) && player.getCash() >= 0) {
        upgradePlayerProperty(player.getPropertyManager().getEntireMap().at(i).getProperties());
      } else {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
         //FIXME: make sure that the turn doesn't end
      }
    }

  } else if (move.getAction() == MoveAction::sellProperty)
  {
    for(int i =0; i < mapSize; i++) {
      if (player.ownsAllPropertiesInSet(i) && player.getCash() >= 0) {
        sellPlayerProperty(player.getPropertyManager().getEntireMap().at(i).getProperties());
      } else {
        std::cout << "You have no upgrades to sell" << std::endl;
        //FIXME: make sure that the turn doesn't end
      }
    }
  } else if (move.getAction() == MoveAction::leaveGame) {
    removeFromGame(player);
  }
}

void Monopoly::GameState::declareWinner() {
  int maxWorth = 0;

  //find the maximum net worth
  for (const auto& player : players) {
    int cur_player_worth = player.getNetWorth();
    if (cur_player_worth > maxWorth) {
      maxWorth = cur_player_worth;
    }
  }

  std::cout << "The winners are" << std::endl;
  for (const auto& player : players) {
    if (player.getNetWorth() == maxWorth) {
      std::cout << player.getName() << std::endl;
    }
  }

}

void Monopoly::GameState::changeTurn() {
  turn_count++;
  player_turn = (player_turn + 1) % players.size();
}

void Monopoly::GameState::upgradePlayerProperty(std::vector<Property*>& PropertyList) {
  int counter =0;
  int userInput = 0;
      std::cout << "Which property do you want to upgrade?" << std::endl;
        printProperty(PropertyList, rules, counter);
      std::cin >> userInput;
      upgradeBuilding(PropertyList.at(userInput), rules);
  return;
}
void Monopoly::GameState::upgradeBuilding(Property*& propertyptr, const Rules& rules) { //specify if building is hotel or house
  if(rules.getNum_houses_before_hotel() == propertyptr->getNumHouses()) {
    propertyptr->incNumHotels();
  }else {
    propertyptr->incNumHouses();
  }
  return;
}

void Monopoly::GameState::sellPlayerProperty(std::vector<Property*>& PropertyList) {
  int userInput = 0;
  std::cout << "Which property do you want to sell?" << std::endl;
  int counter = 0;
  printPropertySell( PropertyList, rules, counter);
  std::cin >> userInput;
  sellBuilding(PropertyList.at(userInput), rules);
  return;
}

void Monopoly::GameState::sellBuilding(Property*& propertyptr, const Rules &rules) {
  if(propertyptr->getNumHotels() > 0) {
    propertyptr->decNumHotels(rules);
    return;
  }else {
    propertyptr->decNumHouses();
  }
}
void Monopoly::GameState::printProperty(std::vector<Property*>& PropertyList, Rules& rules, int& counter) {
 /* if(rules.Must_build_evenly()) {
    for(const auto& propertyptr : PropertyList) {
      if(propertyptr->getNumHouses() < )
      propertyptr->getNumHouses()
    }
  }*/
  for(const auto& propertyptr : PropertyList) {
    if(rules.getNum_houses_before_hotel() == propertyptr->getNumHouses()) {
      std::cout << counter << ". "
                << propertyptr->getName()
                << " [$" << propertyptr->getHotel_cost() << "]" << std::endl;
      ++counter;
    }
    else {
      std::cout << counter << ". "
                << propertyptr->getName()
                << " [$" << propertyptr->getHouse_cost() << "]" << std::endl;
      ++counter;
    }
  }
  return;
}

void Monopoly::GameState::printPropertySell(std::vector<Property*>& PropertyList, Rules& rules, int& counter ) {
  for(const auto& propertyptr : PropertyList) {
    if(rules.getNum_houses_before_hotel() == propertyptr->getNumHouses()) {
      std::cout << counter << ". "
                << propertyptr->getName()
                << " [$" << propertyptr->getHotel_cost() / 2 << "]" << std::endl;
      ++counter;
    }
    else {
      std::cout << counter << ". "
                << propertyptr->getName()
                << " [$" << propertyptr->getHouse_cost() / 2 << "]" << std::endl;
      ++counter;
    }
  }
  return;
}

void Monopoly::GameState::removeFromGame(Monopoly::Player& player) {
  // remove the player from the vector
  for (auto playerIt = players.cbegin(); playerIt != players.cend(); ++playerIt) {
    if (playerIt->getId() == player.getId()) {
      player.getSpaceOn().removePlayer(player);
      players.erase(playerIt);
      break;
    }
  }
  /*
  * update all pointers to players now that we've moved their locations in memory
  * Currently these are just the property owner pointers and the pointers on the spaces that point to who is on them
  * Has to be in a separate loop from the other because we need to get the players' new location in memory first
  */
  board.removeAllPlayers(); // remove all references from the spaces on the board to the players
  for (auto& rem_player :players) {
    rem_player.refreshReferencesTo();
  }

  //because we removed a player and everyone shifted over we need to
  player_turn--;

}



