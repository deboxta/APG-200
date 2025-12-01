#include "Group.h"

Group::Group(byte CC) {
  this->CC = CC;
}

void Group::addSwitch(Switch* sw) {
  switches[index] = sw;
  index++;
}

void Group::init() {
  for (byte i = 0; i < index; i++) {
    switches[i]->init();
    value = value ^ switches[i]->getValue();
  }
  //every bits are changed since first pass
  bitMask = 0b11111111;
  
//  Serial.println(bitMask, BIN);
//  Serial.println(value, BIN);
}

void Group::update() {
  isChanged = false;

  byte lastValue = value;
  value = 0b00000000; //reset
  
  for (byte i = 0; i < index; i++) {
    switches[i]->update();
    value = value ^ switches[i]->getValue();
  }

  if (lastValue != value) {
    bitMask = lastValue ^ value;
    isChanged = true;
//    Serial.println("update");
//    Serial.println(CC);
//    Serial.println(bitMask, BIN);
//    Serial.println(value, BIN);

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
