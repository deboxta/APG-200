#include "Group.h"

Group::Group(byte groupCC) {
  this->groupCC = groupCC;
}

void Group::init() {
  
}

void Group::addSwitch(Switch sw) {
  //switches[index] = sw;
  index++;
}

void Group::update() {
  //byte newState = digitalRead(pin);
}

byte Group::getGroupCC() {
  return groupCC;
}
