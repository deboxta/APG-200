#include "Potentiometer.h"

Pot::Pot(Mux &mux, byte pin, byte CC, bool isMuxPinned): mux(mux) {
  this->isMuxPinned = isMuxPinned;
  this->pin = pin;
  this->CC = CC;
}

Pot::Pot(Mux &mux, byte pin, byte CC): mux(mux) {
  this->pin = pin;
  this->CC = CC;
}

void Pot::init() {
  //ResponsiveAnalogRead (for pots smooting)
  responsivePot = ResponsiveAnalogRead(getPin(), true, snapMultiplier);
  responsivePot.setAnalogResolution(1023);

  //Set values of pots so we don't enter the loop prematurely on startup
  read();
  lastState = state;
  lastValue = value;
//  update();
}

byte Pot::getPin() {
  if (isMuxPinned) {
    return mux.getPrimaryPin();
  } else {
    return pin;
  }
}

void Pot::update() {
  isChanged = false;
  read();

  int variation = abs(state - lastState);

  if (variation > threshold) {
    lastTime = millis(); //reset
  }

  timer = millis() - lastTime;

  if (timer < TIMEOUT && millis() >= TIMEOUT) {
    if (value != lastValue) {
      isChanged = true;
      lastValue = value;
    }
    lastState = state;
  }
}


void Pot::read() {
  if (isMuxPinned) {
    mux.channel(pin);
  }

  reading = analogRead(getPin());
  responsivePot.update(reading);
  state = responsivePot.getValue();
  value = map(state, 0, 1023, 0, 256);
}

byte Pot::getValue() {
  return value;
}

byte Pot::getCC() {
  return CC;
}

bool Pot::hasChanged() {
  update();
  return isChanged;
}
