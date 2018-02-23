//
// Created by mfbut on 1/20/2018.
//

#include <iostream>
#include <cmath>
#include <string>
#include "Property.h"
#include "Player.h"

Monopoly::Property::Property(CSVReader& boardFile) : owner(nullptr) {

  setId = boardFile.get_next_field_as_int();
  intraSetId = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  cost = boardFile.get_next_field_as_int();
  house_cost = boardFile.get_next_field_as_int();
  hotel_cost = boardFile.get_next_field_as_int();
  rent = boardFile.get_next_field_as_int();
  rent_with_house = boardFile.get_next_field_as_int();
  rent_with_hotel = boardFile.get_next_field_as_int();
  numHouses = 0;
  numHotels = 0;
  buildingTally = "";
}

int Monopoly::Property::getSetId() const {
  return setId;
}

int Monopoly::Property::getIntraSetId() const {
  return intraSetId;
}

const std::string& Monopoly::Property::getName() const {
  return name;
}

int Monopoly::Property::getCost() const {
  return cost;
}

int Monopoly::Property::getHouse_cost() const {
  return house_cost;
}

int Monopoly::Property::getHotel_cost() const {
  return hotel_cost;
}

int Monopoly::Property::getRent() const {
  return rent;
}

int Monopoly::Property::getRent_with_house() const {
  return rent_with_house;
}

int Monopoly::Property::getRent_with_hotel() const {
  return rent_with_hotel;
}

Monopoly::Player* Monopoly::Property::getOwner() const {
  return owner;
}

int Monopoly::Property::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Property::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

void Monopoly::Property::display() const {
  std::cout << name << " | ";
  if (owner == nullptr) {
    std::cout << "None | ";
  } else {
    std::cout << owner->getName() << " | ";
  }
}

std::string Monopoly::Property::getOwnerName() const {
  if (owner != nullptr) {
    return owner->getName();
  } else {
    return "None";
  }
}

std::string& Monopoly::Property::addh() {
    return buildingTally += 'h';
}

std::string& Monopoly::Property::minush() {
  buildingTally.pop_back();
  return buildingTally;
}

/*std::string& Monopoly::Property::minush() {
buildingTally.pop_back();
return buildingTally;
}*/

std::string& Monopoly::Property::gethouseString() {
  //std::cout << "hello " << this->buildingTally << std::endl;
  return buildingTally;
}
void Monopoly::Property::setOwner(Monopoly::Player* owner) {
  Property::owner = owner;
}

int Monopoly::Property::calculateRent(const Rules& rules) const { //changed calculate rent with stipulation
  if(numHouses > 0 || numHotels > 0) {
    return rent_with_house * std::pow(2, numHouses - 1);
  }
  else{
    return rent * (owner->ownsAllPropertiesInSet(setId) ? rules.getProperty_set_multiplier() : 1); //change this
  }
}

int Monopoly::Property::getNumHouses() const {
  return numHouses;
}

int Monopoly::Property::getNumHotels() const {
  return numHotels;
}
int Monopoly::Property::incNumHouses() {
  return numHouses++;
}
int Monopoly::Property::incNumHotels() { //not returning numHouses
  numHouses = 0;
  return numHotels++;
}
int Monopoly::Property::decNumHouses() {
  return numHouses--;
}
int Monopoly::Property::decNumHotels(const Rules& rules) { //not returning numHouses
  numHouses = rules.getNum_houses_before_hotel();
  return numHotels--;
}


