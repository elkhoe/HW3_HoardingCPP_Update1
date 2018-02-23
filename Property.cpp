//
// Created by mfbut on 1/20/2018.
//

#include <iostream>
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

void Monopoly::Property::setOwner(Monopoly::Player* owner) {
  Property::owner = owner;
}

int Monopoly::Property::calculateRent(const Rules& rules) const {
  return rent * (owner->ownsAllPropertiesInSet(setId) ? rules.getProperty_set_multiplier() : 1);

}

