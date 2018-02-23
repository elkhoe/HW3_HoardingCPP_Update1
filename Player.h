//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PLAYER_H
#define HOARDINGCPPVERSION_PLAYER_H
#include <string>
#include <map>

#include "Property.h"
#include "Space.h"
#include "PropertyManager.h"
#include "Rules.h"
#include "Move.h"

namespace Monopoly {
  class Player {
   public:
    static unsigned long length_of_longest_player_name;
    Player(int id, const std::string& name, int cash, Space* spaceOn, const PropertyManager& propertyManager);
    Player(const Player& player) = default;
    Space& getSpaceOn();
    PropertyManager& getPropertyManager();
    virtual ~Player();

    void setOn(Space& space, bool activateSpace = true);
    void moveTo(Space& space, bool activateSpace = true);

    const std::string& getName() const;
    int getCash() const;
    void setCash(int cash);
    void giveCash(const int amount);

    void purchase(Property& property);

    bool getBuyDecision(const Space& space) const;

    void pay(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules);
    bool ownsAllPropertiesInSet(const int setId) const;
    int getNetWorth() const;
    void refreshReferencesTo();

    Move getMove();

    void display();
    int getId() const;

   private:
    int id;
    std::string name;
    int cash;
    Move current_move;
    Space* spaceOn;
    PropertyManager propertyManager;

  };
}

#endif //HOARDINGCPPVERSION_PLAYER_H
