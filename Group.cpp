#include "Group.h"

Group::Group(byte CC) {
  this->CC = CC;
}

void Group::init() {

}

void Group::addSwitch(Switch* sw) {
  switches[index] = sw;
  index++;
}

void Group::update() {
  isChanged = false;

  byte newValue = 0b00000000;
  for (int i = 0; i < 7; i++) {
    switches[i]->update();
    lastValue = value;

    newValue = newValue ^ switches[i]->getValue();
//    Serial.println(newValue);
//    Serial.println(value);

  }
  value = newValue;

  if (lastValue != value) {
    bitMask = lastValue ^ value;
    isChanged = true;
//    Serial.println("value changed!");
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
