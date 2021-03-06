//
// Created by mfbut on 1/27/2018.
//
#include <iostream>
#include <map>
#include "PropertySet.h"

Monopoly::PropertySet::PropertySet(int setId) : setId(setId), numPropertiesInSet(1) {}

/*
Monopoly::PropertySet::PropertySet(const Monopoly::Property& property) :
    setId(property.getSetId()), numPropertiesInSetOwned(0){
  properties.push_back(&property);
}
*/

void Monopoly::PropertySet::incNumPropertiesInSet() {
  numPropertiesInSet++;
}

/**
 * Does a sorted insert of the property into the set based on the intraset id
 * @param property
 */
void Monopoly::PropertySet::addProperty(Monopoly::Property& property) {

  // not a part of the set so don't add it in
  if (property.getSetId() != setId) {
    return;
  }

  auto propItr = properties.cbegin();

  //locate insertion position
  for (; propItr != properties.cend(); ++propItr) {
    if (property.getIntraSetId() < (*propItr)->getIntraSetId()) {
      break;
    }
  }
  //add it in
  properties.insert(propItr, &property);
}

void Monopoly::PropertySet::removeProperty(const Monopoly::Property& property) {
  // not a part of the set so don't can't remove it
  if (property.getSetId() != setId) {
    return;
  }

  auto propItr = properties.cbegin();

  //locate insertion position
  for (; propItr != properties.cend(); ++propItr) {
    if (property.getIntraSetId() == (*propItr)->getIntraSetId()) {
      properties.erase(propItr);
      return;
    }
  }
}

void Monopoly::PropertySet::clear() {
  properties.clear();
}

bool Monopoly::PropertySet::ownsAll() const {
  return static_cast<int>(properties.size()) == numPropertiesInSet;
}

std::vector<Monopoly::Property*>& Monopoly::PropertySet::getProperties() {
  return properties;
}

void Monopoly::PropertySet::updateOwner(Monopoly::Player& newOwner) {
  for (auto& propertyPtr : properties) {
    propertyPtr->setOwner(&newOwner);
  }
}

Monopoly::PropertySet::~PropertySet() {
  /*
   * Since property sets
   */
  for (auto& property : properties) {
    if (property) {
      property->setOwner(nullptr);
    }
  }
}

int Monopoly::PropertySet::getValue() const {
  int value = 0;
  for (const auto& property : properties) {
    value += property->getCost();
    value += property->getHouse_cost() * property->getNumHouses();
    value += property->getHotel_cost() * property->getNumHotels();
  }
  return value;
}

int Monopoly::PropertySet::getNumPropertiesInSet() const {
  return numPropertiesInSet;
}









