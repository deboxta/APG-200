#include "DualPole.h"

DualPole::DualPole(Mux &mux, byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC, bool isMuxPinned, bool isMuxPinned2): Switch(mux, pin, bitPos, CC, isMuxPinned) {
  this->isMuxPinned2 = isMuxPinned2;
  this->pin2 = pin2;
  this->bitPos2 = bitPos2;

}

DualPole::DualPole(byte pin, byte pin2, byte bitPos, byte bitPos2, byte CC): Switch(pin, bitPos, CC) {
  this->pin2 = pin2;
  this->bitPos2 = bitPos2;
}

void DualPole::init() {
  if (isMuxPinned == false) {
    pinMode(pin, INPUT_PULLUP);
  }
  if (isMuxPinned2 == false) {
    pinMode(pin2, INPUT_PULLUP);
  }
}

void DualPole::update() {
  pinUpdate(pin, bitPos, isMuxPinned, lastButtonState);
  pinUpdate(pin2, bitPos2, isMuxPinned2, lastButtonState2);
}

void DualPole::pinUpdate(byte pinU, byte bitPosU, bool isMux, int &lastState) {
  if (isMux) {
    mux.channel(pinU);
  }
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(getPin(pinU));


  // If the switch changed, due to noise or pressing:
  if (reading != lastState) {
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
        value &= ~(1 << bitPosU);
      }
      else if (buttonState == HIGH)
      {
        value |= (1 << bitPosU);          
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastState = reading;
}

byte DualPole::getPin(byte id) {
  if (id == pin){
    if (isMuxPinned) {
      return mux.getPrimaryPin();
    }
    else {
      return pin;
    }
  }
  else {
    if (isMuxPinned2) {
      return mux.getPrimaryPin();
    }
    else {
      return pin2;
    }
  }

}
