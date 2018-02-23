//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include "Space.h"
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"
#include "Auction.h"

unsigned long Monopoly::Space::length_of_longest_space_name;

Monopoly::Space::Space(CSVReader& boardFile, const int spaceNumber, const Rules& rules)
    : spaceNumber(spaceNumber), rules(rules) {
  std::string space_type_string = boardFile.get_next_field();

  if (space_type_string == "Go") {
    spaceType = SpaceType::goSpace;
    goPtr = std::make_unique<Go>(boardFile);
    boardFile.skip_line(); // skip the remainder of the line in the file
  } else if (space_type_string == "Property") {
    spaceType = SpaceType::propertySpace;
    propertyPtr = std::make_unique<Property>(boardFile);
  } else {
    std::cout << "Unrecognized Space type found in " << boardFile.getFileName() << std::endl;
  }
}

void Monopoly::Space::display() const {
  const auto frmt_flags = std::cout.flags();

  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  std::cout.width(Monopoly::Player::length_of_longest_player_name);
  if (spaceType == SpaceType::goSpace) {
    const std::string temp = "None";
    std::cout << temp << " | ";
  } else if (spaceType == SpaceType::propertySpace) {
    std::cout << propertyPtr->getOwnerName() << " | ";
  } else {
    std::cout << " This space has an unknown type" << std::endl;
  }
  std::cout.flags(frmt_flags);

  auto player = playersOnSpace.cbegin();
  for (; player != playersOnSpace.cend(); ++player) {
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }

    (*player)->display();
    std::cout << ", ";

  }

  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }

}

const std::string& Monopoly::Space::getName() const {
  if (spaceType == SpaceType::goSpace) {
    return goPtr->getName();
  } else {
    return propertyPtr->getName();
  }
}

void Monopoly::Space::addPlayer(Monopoly::Player& player) {
  auto playerIt = playersOnSpace.cbegin();
  for (; playerIt != playersOnSpace.cend(); ++playerIt) {
    if (player.getId() < (*playerIt)->getId()) {
      break;
    }
  }
  playersOnSpace.insert(playerIt, &player);
}

void Monopoly::Space::removePlayer(const Monopoly::Player& player) {
  for (auto playerIt = playersOnSpace.cbegin(); playerIt != playersOnSpace.cend(); ++playerIt) {
    if ((*playerIt)->getId() == player.getId()) {
      playersOnSpace.erase(playerIt);
      return;
    }
  }
}

void Monopoly::Space::removeAllPlayers() {
  playersOnSpace.clear();
}

Monopoly::SpaceType Monopoly::Space::getSpaceType() const {
  return spaceType;
}

int Monopoly::Space::getSpaceNumber() const {
  return spaceNumber;
}

void Monopoly::Space::activate(Monopoly::Player& activatingPlayer, std::vector<Player>& players){
  if (spaceType == SpaceType::goSpace) {
    // -1 below because they've already been given some of the salary for
    // "passing" go
    activatingPlayer.giveCash(goPtr->getSalary() * (rules.getSalary_multiplier_for_landing_on_go() - 1));
  } else if (spaceType == SpaceType::propertySpace) {
    Player* owner = propertyPtr->getOwner();
    if (owner == nullptr) {
      if (activatingPlayer.getCash() >= propertyPtr->getCost()) { //can afford the property
        bool toBuy = activatingPlayer.getBuyDecision(*this);
        if (toBuy) {
          std::cout << activatingPlayer.getName() << " bought " << getName() << " for $" << propertyPtr->getCost()
                    << std::endl;
          activatingPlayer.purchase(*propertyPtr);
} else if(!toBuy){
  Auction auction;
  std::string highestbidder = "bob";
  int auction_members = players.size();

  for(int i = 0; i < players.size(); i++){

  players[i].set_is_in_auction_bool(true);
  }
  auction.set_auction_has_max_bidder(false);
  auction.set_highestbid(0);


  std::cout << "Starting the auction for " << getName() << std::endl;

  while((auction_members > 1)){
  for(int i = 0; i < auction_members; i++){

    if(players[i].get_is_in_auction_bool() == true){

      if (auction.get_highestbid() > players[i].getCash()){
        players[i].set_is_in_auction_bool(false);
        auction_members--;
        continue;
      }

      if (!auction.get_auction_has_max_bidder()){
        std::cout << "No one has bid on "<< getName() << " [$" << getCost() << "] yet" << std::endl;
      }
        else if (auction.get_auction_has_max_bidder()){
        std::cout <<"The current bid for "<< getName() << " [$" << getCost() << "]" << " is $" << auction.get_highestbid() << " by "<< highestbidder << std::endl;
  }
    std::cout << players[i].getName() <<", enter a bid of at least " << (auction.get_highestbid()+1) << " to bid on the property or a value less that that to leave the auction" << std::endl;
    std::cout << "Your bid:" << std::endl;
    int newbid1;
    std::cin >> newbid1;
   auction.set_newbid(newbid1);

    auction.set_auction_has_max_bidder(true);

    if(auction.get_newbid() < auction.get_highestbid()+1){
      players[i].set_is_in_auction_bool(false);
      auction_members--;
      continue;
    }

    else if(auction.get_newbid() > auction.get_highestbid()){
      highestbidder = players[i].getName();
      auction.set_highestbid(newbid1);
    }
  }
  }
  }

for(int i=0; i < players.size(); i++){
  if(players[i].getName() == highestbidder){
    players[i].auction_win(*propertyPtr, auction.get_highestbid());
  }
    else if(auction.get_highestbid() == 0){
      owner = nullptr;
    }
  }
}
///////
}

       else { // not enough money to buy property
        std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << getName() << ". "
                  << getName() << " costs $" << getCost() << " but you only have $" << activatingPlayer.getCash()
                  << std::endl;
//starting auction
                  Auction auction;
                  std::string highestbidder = "bob";
                  int auction_members = players.size();

                  for(int i = 0; i < players.size(); i++){

                  players[i].set_is_in_auction_bool(true);
                  }
                  auction.set_auction_has_max_bidder(false);
                  auction.set_highestbid(0);


                  std::cout << "Starting the auction for " << getName() << std::endl;

                  while((auction_members > 1)){
                  for(int i = 0; i < auction_members; i++){

                    if(players[i].get_is_in_auction_bool() == true){

                      if (auction.get_highestbid() > players[i].getCash()){
                        players[i].set_is_in_auction_bool(false);
                        auction_members--;
                        continue;
                      }

                      if (!auction.get_auction_has_max_bidder()){
                        std::cout << "No one has bid on "<< getName() << " [$" << getCost() << "] yet" << std::endl;
                      }
                        else if (auction.get_auction_has_max_bidder()){
                        std::cout <<"The current bid for "<< getName() << " [$" << getCost() << "]" << " is $" << auction.get_highestbid() << " by "<< highestbidder << std::endl;
                  }
                    std::cout << players[i].getName() <<", enter a bid of at least " << (auction.get_highestbid()+1) << " to bid on the property or a value less that that to leave the auction" << std::endl;
                    std::cout << "Your bid:" << std::endl;
                    int newbid1;
                    std::cin >> newbid1;
                   auction.set_newbid(newbid1);

                    auction.set_auction_has_max_bidder(true);

                    if(auction.get_newbid() < auction.get_highestbid()+1){
                      players[i].set_is_in_auction_bool(false);
                      auction_members--;
                      continue;
                    }

                    else if(auction.get_newbid() > auction.get_highestbid()){
                      highestbidder = players[i].getName();
                      auction.set_highestbid(newbid1);
                    }
                  }
                  }
                  }

                for(int i=0; i < players.size(); i++){
                  if(players[i].getName() == highestbidder){
                    players[i].auction_win(*propertyPtr, auction.get_highestbid());
                  }
                }
      }}
     else if(owner->getId() == activatingPlayer.getId()) {// player landed on their own property
      std::cout << activatingPlayer.getName() << ", you landed on " << getName() << "which you already own" << std::endl;
    } else { //landed on a space another player owes
      activatingPlayer.pay(*owner, *propertyPtr, rules);



    }}}



int Monopoly::Space::getSalary() const {
  if (spaceType == SpaceType::goSpace) {
    return goPtr->getSalary();
  } else {
    std::cout << "Get Salary called on non Go Space" << std::endl;
    return -99;
  }
}

int Monopoly::Space::getCost() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getCost();
  } else {
    std::cout << "Get Cost called on non Property Space" << std::endl;
    return -99;
  }
}

int Monopoly::Space::getSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getSetId();
  } else {
    return -99;
  }
}

int Monopoly::Space::getIntraSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getIntraSetId();
  } else {
    return -99;
  }
}

int Monopoly::Space::getBasicRent() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getRent();
  } else {
    return -99;
  }
}
