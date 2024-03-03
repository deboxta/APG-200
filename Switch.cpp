#include "Switch.h"

Switch::Switch(byte pins[], byte groupCC, byte pos) {
  this->pins = pins;
  this->groupCC = groupCC;
  this->pos = pos;
}

Switch::init() {
  
}

Switch::update() {
  byte newState = digitalRead(pin);
}

byte Switch::getGroupCC() {
  return groupCC;
}

