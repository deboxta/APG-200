#include "Group.h"

Group::Group(byte groupCC, Switch switches[]) {
  this->pins = pins;
  this->groupCC = groupCC;
  this->pos = pos;
}

Group::init() {
  
}

Group::update() {
  byte newState = digitalRead(pin);
}

byte Group::getGroupCC() {
  return groupCC;
}
