#include "Button.h"

Button::Button(byte pin, byte CC, byte value) {
  this->pin = pin;
  this->CC = CC;
  this->value = value;
}

void Button::init() {
  pinMode(pin, INPUT);
  lastState = LOW;
}

void Button::update() {
  pressed = false;
  byte newState = digitalRead(pin);

  if (newState != lastState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (newState != state) {
      state = newState;
      if (state == LOW) {
        pressed = true;
      }
    }
  }
  lastState = newState;
}

bool Button::isPressed() {
  update();
  return (pressed);
}

byte Button::getValue() {
  return value;
}

byte Button::getCC() {
  return CC;
}
