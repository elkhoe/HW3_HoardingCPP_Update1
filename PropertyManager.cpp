//
// Created by mfbut on 1/27/2018.
//

#include "PropertyManager.h"
#include "Board.h"
#include "Player.h"

Monopoly::PropertyManager::PropertyManager(const Monopoly::Board& board) {
  for (const auto& space : board.getSpaces()) {
    if (space.getSpaceType() == SpaceType::propertySpace) {
      if (propertySets.count(space.getSetId()) == 0) {
        propertySets[space.getSetId()] = PropertySet(space.getSetId());
      } else {
        propertySets.at(space.getSetId()).incNumPropertiesInSet();
      }
    }
  }
}

void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::Property& property) {
  propertySets.at(property.getSetId()).addProperty(property);
}

/**
 * Move all of the properties within the property set into this
 * property manager. Leaves the given propertySet empty
 * @param propertySet
 */
void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::PropertySet& propertySet) {
  for (const auto& property : propertySet.getProperties()) {
    takeOwnershipOf(*property);
  }
  propertySet.clear();
}

bool Monopoly::PropertyManager::ownsEntireSet(const int setId) const {
  return propertySets.at(setId).ownsAll();
}

void Monopoly::PropertyManager::givePropertiesTo(Monopoly::PropertyManager& receiver) {
  for (auto& propertySet : propertySets) {
    receiver.takeOwnershipOf(propertySet.second); // second is the actual property. first is the property set id
  }
}

void Monopoly::PropertyManager::updateOwner(Monopoly::Player& newOwner) {
  for (auto& propertySet : propertySets) {
    propertySet.second.updateOwner(newOwner);
  }
}

int Monopoly::PropertyManager::getValue() const {
  int value = 0;

  for (const auto& propertySet : propertySets) {
    value += propertySet.second.getValue();
  }
  return value;
}

std::map<int, Monopoly::PropertySet>& Monopoly::PropertyManager::getEntireMap() {
  return propertySets;

}

