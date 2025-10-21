#include "Arduino.h"
#include "Mux.h"

Mux::Mux(byte primaryPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3) {
  this->primaryPin = primaryPin;
  _s0 = s0;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
}

void Mux::init() {
  pinMode(primaryPin, INPUT_PULLUP);
  
  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
}

void Mux::channel(uint8_t channel) {
  digitalWrite(_s0, channel & 0x01); // Set S0
  digitalWrite(_s1, (channel >> 1) & 0x01); // Set S1
  digitalWrite(_s2, (channel >> 2) & 0x01); // Set S2
  digitalWrite(_s3, (channel >> 3) & 0x01); // Set S3
}

byte Mux::getPrimaryPin(){
  return primaryPin;
}
