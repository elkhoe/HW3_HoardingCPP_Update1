//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GO_H
#define HOARDINGCPPVERSION_GO_H

#include <string>
#include "CSVReader.h"
namespace Monopoly {
  class Go {
   public:
    explicit Go(CSVReader& boardFile);
    int getSalary() const;
    const std::string& getName() const;
    void display() const;
   private:
    int salary;
    int landing_multiplier;
   public:
    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);
   private:
    std::string name;

  };
}

#endif //HOARDINGCPPVERSION_GO_H
