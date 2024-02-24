#include "Button.h"

Button::Button(byte pin, byte CC, byte value) {
  this->pin = pin;
  this->CC = CC;
  this->value = value;
}

void Button::init() {
  pinMode(pin, INPUT);
  state = HIGH;
  lastState = HIGH;
  update();
}

void Button::update() {
  state = HIGH;
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

