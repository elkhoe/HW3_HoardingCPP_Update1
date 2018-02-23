//
// Created by mfbut on 1/27/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTYMANAGER_H
#define HOARDINGCPPVERSION_PROPERTYMANAGER_H
#include <map>
#include <vector>

#include "Property.h"
#include "PropertySet.h"

namespace Monopoly {
  class Board;
  class Player;

  class PropertyManager {
   public:
    explicit PropertyManager(const Board& board);

    PropertyManager(const PropertyManager& orig) = default;
    void takeOwnershipOf(Property& property);
    void takeOwnershipOf(PropertySet& propertySet);
    bool ownsEntireSet(const int setId) const;
    void givePropertiesTo(PropertyManager& receiver);
    void updateOwner(Player& newOwner);
    int getValue() const;
   private:
    std::map<int, PropertySet> propertySets;
  };
}

#endif //HOARDINGCPPVERSION_PROPERTYMANAGER_H
