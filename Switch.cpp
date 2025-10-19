#include "Switch.h"

Switch::Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte groupCC, bool isMuxPinned): mux(mux) {
  this->isMuxPinned = isMuxPinned;
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->bitPos1 = bitPos1;
  this->bitPos2 = bitPos2;
  this->groupCC = groupCC;
}

Switch::Switch(Mux &mux, byte pin1, byte bitPos1, byte groupCC, bool isMuxPinned): mux(mux) {
  this->isMuxPinned = isMuxPinned;
  this->pin1 = pin1;
  this->bitPos1 = bitPos1;
  this->groupCC = groupCC;
}

Switch::Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte groupCC): mux(mux) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->bitPos1 = bitPos1;
  this->bitPos2 = bitPos2;
  this->groupCC = groupCC;
}

Switch::Switch(Mux &mux, byte pin1, byte bitPos1, byte groupCC): mux(mux) {
  this->pin1 = pin1;
  this->bitPos1 = bitPos1;
  this->groupCC = groupCC;
}

void Switch::init() {
  
}

void Switch::update() {

}

byte Switch::getGroupCC() {
  return groupCC;
}

