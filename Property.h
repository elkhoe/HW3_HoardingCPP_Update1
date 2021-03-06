//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTY_H
#define HOARDINGCPPVERSION_PROPERTY_H
#include <string>
#include "CSVReader.h"
#include "Rules.h"

namespace Monopoly {
  class Player;

  class Property {
   public:
    explicit Property(CSVReader& boardFile);
    void setOwner(Player* owner);

    int getSetId() const;
    int getIntraSetId() const;
    const std::string& getName() const;
    int getCost() const;
    int getHouse_cost() const;
    int getHotel_cost() const;
    int getRent() const;
    int getRent_with_house() const;
    int getRent_with_hotel() const;
    Player* getOwner() const;
    std::string getOwnerName() const;
    std::string& addh ();
    std::string& minush();
    //std::string& minush();
    std::string& gethouseString();
    int calculateRent(const Rules& rules) const;
    int incNumHouses();
    int incNumHotels();
    int decNumHouses();
    int decNumHotels(const Rules& rules);
    int getNumHouses()const ;
    int getNumHotels() const;



   private:
    int setId;
    int intraSetId;
    std::string name;
    std::string buildingTally;
    int cost;
    int house_cost;
    int hotel_cost;
    int rent;
    int rent_with_house;
    int rent_with_hotel;
    Player* owner;
    int landing_multiplier;
    int numHouses;
    int numHotels;
   public:
    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);
    void display() const;

  };
}

#endif //HOARDINGCPPVERSION_PROPERTY_H
