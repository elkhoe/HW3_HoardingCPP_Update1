//
// Created by mfbut on 1/20/2018.
//

#include "Go.h"
#include <iostream>

Monopoly::Go::Go(CSVReader& boardFile) : landing_multiplier(1) {
  salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();

}

int Monopoly::Go::getSalary() const {
  return salary;
}

const std::string& Monopoly::Go::getName() const {
  return name;
}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

void Monopoly::Go::display() const {
  std::cout << name << " | None | ";
}
