//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GAMESTATE_H
#define HOARDINGCPPVERSION_GAMESTATE_H
#include <vector>
#include <string>
#include <fstream>

#include "Rules.h"
#include "Move.h"
#include "Board.h"
#include "DiceRoller.h"
#include "Player.h"

namespace Monopoly {
  class GameState {
   public:
    static std::vector<std::string> get_player_names();
    GameState(const std::string& RulesFileName,
              const std::string& BoardFileName,
              const std::string& RandomFileName,
              const std::vector<std::string>& playerNames);

    void playGame();
    bool isGameOver() const;
    Player& getCurrentPlayer();
    void make_move(Player& player, Move& move);
    void declareWinner();
    void changeTurn();
    void upgradePlayerProperty(std::vector<Property*>& PropertyList);
    void upgradeBuilding(Property*& propertyptr, const Rules& rules);
    void sellBuilding(Property*& propertyptr, const Rules& rules);
    void printProperty(std::vector<Property*>& PropertyList, Rules& rules, int& counter);
    void printPropertySell(std::vector<Property*>& PropertyList, Rules& rules, int& counter);
    void sellPlayerProperty(std::vector<Property*>& PropertyList);
    void removeFromGame(Player& player);


    void display() const;

   private:

    Rules rules;
    Board board;
    DiceRoller diceRoller;
    int turn_count;
    unsigned long player_turn;
    std::vector<Player> players;
  };
}

#endif //HOARDINGCPPVERSION_GAMESTATE_H
