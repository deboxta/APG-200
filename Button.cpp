#include "Button.h"

Button::Button(byte pin, byte CC, byte value) {
  this->pin = pin;
  this->CC = CC;
  this->value = value;
  lastState = HIGH;
  init();
}

void Button::init() {
  pinMode(pin, INPUT);
  update();
}

void Button::update() {
  byte newState = digitalRead(pin);
  debounceTimer = millis() - lastDebounceTime;

  if (newState != lastState) {
    lastDebounceTime = millis();

  
    if (debounceTimer > debounceDelay) {
      if (newState != state) {
            state = newState;
      }
      lastState = newState;
    }
  } else {
    state = HIGH;
  }
  
}

byte Button::getState() {
  update();
  return state;
}

bool Button::isPressed() {
  return (getState() == LOW);
}

byte Button::getValue() {
  return value;
}

byte Button::getCC() {
  return CC;
}

