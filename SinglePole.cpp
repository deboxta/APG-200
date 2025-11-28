#include "SinglePole.h"

SinglePole::SinglePole(Mux* mux, byte pin, byte bitPos, byte CC, bool isMuxPinned): Switch(mux, pin, bitPos, CC, isMuxPinned) {
}

SinglePole::SinglePole(byte pin, byte bitPos, byte CC): Switch(pin, bitPos, CC) {
}

void SinglePole::init() {
  if (isMuxPinned) {
    mux->channel(pin);
  }
  
  // read the state of the switch into a local variable:
  buttonState = digitalRead(getPin());

  if (buttonState == LOW) {
    value &= ~(1 << bitPos);
  }
  else if (buttonState == HIGH)
  {
    value |= (1 << bitPos);          
  }
}

void SinglePole::update() {
  if (isMuxPinned) {
    mux->channel(pin);
  }
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(getPin());


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
      if (buttonState == HIGH) {
        value &= ~(1 << bitPos);
      }
      else if (buttonState == LOW)
      {
        value |= (1 << bitPos);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

byte SinglePole::getPin() {
  if (isMuxPinned) {
    return mux->getPrimaryPin();
  } else {
    return pin;
  }
}
