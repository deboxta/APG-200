#include "Switch.h"

Switch::Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte CC, bool isMuxPinned): mux(mux) {
  this->isMuxPinned = isMuxPinned;
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->bitPos1 = bitPos1;
  this->bitPos2 = bitPos2;
  this->CC = CC;
}

Switch::Switch(Mux &mux, byte pin1, byte bitPos1, byte CC, bool isMuxPinned): mux(mux) {
  this->isMuxPinned = isMuxPinned;
  this->pin1 = pin1;
  this->bitPos1 = bitPos1;
  this->CC = CC;
}

Switch::Switch(Mux &mux, byte pin1, byte pin2, byte bitPos1, byte bitPos2, byte CC): mux(mux) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->bitPos1 = bitPos1;
  this->bitPos2 = bitPos2;
  this->CC = CC;
}

Switch::Switch(Mux &mux, byte pin1, byte bitPos1, byte CC): mux(mux) {
  this->pin1 = pin1;
  this->bitPos1 = bitPos1;
  this->CC = CC;
}

void Switch::init() {
  //pinMode(pin1, INPUT_PULLUP);

}

void Switch::update() {
  if (isMuxPinned) {
    mux.channel(pin1);
  }
  
  // read the state of the switch into a local variable:
  int reading =   digitalRead(getPin());


  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW (button pressed, assuming INPUT_PULLUP)
      if (buttonState == LOW) {
        value |= (1 << CC);
      }
      else
      {
        value |= (0 << CC);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

byte Switch::getPin() {
  if (isMuxPinned) {
    return mux.getPrimaryPin();
  } else {
    return pin1;
  }
}
byte Switch::getCC() {
  return CC;
}

byte Switch::getValue() {
  return value;
}
