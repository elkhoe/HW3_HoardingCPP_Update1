//
// Created by mfbut on 1/20/2018.
//

#include "Player.h"
#include <iostream>
#include <cctype>

unsigned long Monopoly::Player::length_of_longest_player_name;

Monopoly::Player::Player(int id,
                         const std::string& name,
                         int cash,
                         Space* spaceOn,
                         const PropertyManager& propertyManager)
    : id(id), name(name), cash(cash), spaceOn(spaceOn), propertyManager(propertyManager) {

}

const std::string& Monopoly::Player::getName() const {
  return name;
}

int Monopoly::Player::getCash() const {
  return cash;
}

void Monopoly::Player::setCash(int cash) {
  Player::cash = cash;
}

void Monopoly::Player::giveCash(const int amount) {
  cash += amount;
}

Monopoly::Move Monopoly::Player::getMove() {
  int move_number;
  std::cout << name << " please enter your move" << std::endl;
  std::cout << "1 to roll dice" << std::endl;
  std::cout << "2 to upgrade property with house or hotel" << std::endl;
  std::cout << "3 to sell a house or hotel" << std::endl;
  std::cout << "4 to leave the game" << std::endl; //this was originally "2 to leave the game"
  std::cout << "Your move: ";
  std::cin >> move_number;
  current_move = Move(move_number);

  return current_move;
}

void Monopoly::Player::display() {
  std::cout << '[' << name << " : $" << cash << ']';
}

int Monopoly::Player::getId() const {
  return id;
}

Monopoly::Space& Monopoly::Player::getSpaceOn() {
  return *spaceOn;
}
Monopoly::PropertyManager& Monopoly::Player::getPropertyManager() {
  return propertyManager;
}

void Monopoly::Player::setOn(Space& space, bool activateSpace) {
  this->spaceOn = &space;
  space.addPlayer(*this);

  if (activateSpace) {
    space.activate(*this);
  }

}

void Monopoly::Player::moveTo(Monopoly::Space& space, bool activateSpace) {
  spaceOn->removePlayer(*this);
  setOn(space);

}

bool Monopoly::Player::getBuyDecision(const Monopoly::Space& space) const {
  char choice;
  std::cout << "Would you like to buy " << space.getName() << " for $" << space.getCost() << '?' << std::endl;
  std::cout << "Rent on " <<space.getName() << " is $" << space.getBasicRent() << std::endl;
  std::cout << "Enter y for yes or n for no: ";
  std::cin >> choice;
  choice = static_cast<char>(tolower(choice));
  if (!(choice == 'y' || choice == 'n')) {
    std::cout << "Unknown choice of " << choice << " received for buy decision" << std::endl;
    return false;
  }
  return choice == 'y';
}

void Monopoly::Player::purchase(Monopoly::Property& property) {
  cash -= property.getCost();
  property.setOwner(this);
  propertyManager.takeOwnershipOf(property);
}

void Monopoly::Player::pay(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules) {
  int amount = propertyOn.calculateRent(rules);
  if (cash >= amount) {
    cash -= amount;
    owner.cash += amount;

    std::cout << name << " paid " << owner.name << " $" << amount << " for landing on " << propertyOn.getName()
              << std::endl;
  } else {
    owner.cash += cash;
    cash -= amount;
    propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the player we owe
    owner.propertyManager.updateOwner(owner); // the player we are paying to now owns all those properties
    std::cout << name << " went bankrupt to " << owner.name << " for landing on " << propertyOn.getName() << std::endl;;
  }
}

bool Monopoly::Player::ownsAllPropertiesInSet(const int setId) const {
  return propertyManager.ownsEntireSet(setId);
}

/**
 * Update all the references to this player so that they actually point to this player
 */
void Monopoly::Player::refreshReferencesTo() {
  propertyManager.updateOwner(*this);
  spaceOn->addPlayer(*this);
}

Monopoly::Player::~Player() {
  //spaceOn->removePlayer(*this);
}

int Monopoly::Player::getNetWorth() const {

  return cash + propertyManager.getValue(); //FIXME: add cost of their properties and cost of the upgrades on the properties
}





