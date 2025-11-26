#include "Switch.h"


Switch::Switch(Mux* mux, byte pin, byte bitPos, byte CC, bool isMuxPinned) {
  this->mux = mux;
  this->pin = pin;
  this->bitPos = bitPos;
  this->CC = CC;
  this->isMuxPinned = isMuxPinned;

  if (isMuxPinned == false) {
    pinMode(pin, INPUT_PULLUP);
  }
}

Switch::Switch(byte pin, byte bitPos, byte CC) {
  this->pin = pin;
  this->bitPos = bitPos;
  this->CC = CC;

  pinMode(pin, INPUT_PULLUP);
}

byte Switch::getValue(){
  return value;
}

byte Switch::getCC() {
  return CC;
}

byte Switch::getPin(){}
