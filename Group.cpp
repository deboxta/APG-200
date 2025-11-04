#include "Group.h"

Group::Group(byte CC, int nbInGroup) {
  this->CC = CC;
  this->nbInGroup = nbInGroup;
}

void Group::init() {
  for (int i = 0; i < nbInGroup; i++) {
    switches[i]->init();
  }
}

void Group::addSwitch(Switch* sw) {
  switches[index] = sw;
  index++;
}

void Group::update() {
  isChanged = false;

  byte newValue = 0b00000000;
  for (int i = 0; i < nbInGroup; i++) {
    switches[i]->update();
    lastValue = value;

    newValue = newValue ^ switches[i]->getValue();
  }
  value = newValue;

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
