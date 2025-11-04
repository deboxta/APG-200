#include "Switch.h"


Switch::Switch(Mux &mux, byte pin, byte bitPos, byte CC, bool isMuxPinned) : mux(mux) {
  this->pin = pin;
  this->bitPos = bitPos;
  this->CC = CC;
  this->isMuxPinned = isMuxPinned;
}

Switch::Switch(byte pin, byte bitPos, byte CC) {
  this->pin = pin;
  this->bitPos = bitPos;
  this->CC = CC;
}

byte Switch::getValue(){
  return value;
}

byte Switch::getCC() {
  return CC;
}

byte Switch::getPin(){}
