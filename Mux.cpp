#include "Arduino.h"
#include "Mux.h"

uint8_t _g_channel_truth_table[16][4] = {
  // s0, s1, s2, s3     channel
    {0,  0,  0,  0}, // 0
    {1,  0,  0,  0}, // 1
    {0,  1,  0,  0}, // 2
    {1,  1,  0,  0}, // 3
    {0,  0,  1,  0}, // 4
    {1,  0,  1,  0}, // 5
    {0,  1,  1,  0}, // 6
    {1,  1,  1,  0}, // 7
    {0,  0,  0,  1}, // 8
    {1,  0,  0,  1}, // 9
    {0,  1,  0,  1}, // 10
    {1,  1,  0,  1}, // 11
    {0,  0,  1,  1}, // 12
    {1,  0,  1,  1}, // 13
    {0,  1,  1,  1}, // 14
    {1,  1,  1,  1}  // 15
};

Mux::Mux(byte primaryPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3) {
  this->primaryPin = primaryPin;
  _s0 = s0;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
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
