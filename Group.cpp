#include "Group.h"

Group::Group(byte CC, byte nbInGroup) {
  this->CC = CC;
  this->nbInGroup = nbInGroup;
}

void Group::addSwitch(Switch* sw) {
  switches[index] = sw;
  index++;
}

void Group::init() {
  update();
}

void Group::update() {
  isChanged = false;

  byte lastValue = value;
  value = 0b00000000; //reset
  
  for (byte i = 0; i < nbInGroup; i++) {
    switches[i]->init();
    switches[i]->update();
    value = value ^ switches[i]->getValue();
  }

  if (lastValue != value) {
    bitMask = lastValue ^ value;
    isChanged = true;
  }
}

byte Group::getCC() {
  return CC;
}

byte Group::getMask() {
  return bitMask;
}

byte Group::getValue() {
  return value;
}

bool Group::hasChanged() {
  update();
  return isChanged;
}
