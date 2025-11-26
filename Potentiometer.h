#ifndef MY_POT_H
#define MY_POT_H

#include <ResponsiveAnalogRead.h>
#include "Mux.h"

class Pot {
  private:
    byte pin;
    byte CC;

    int reading = 0;
    int state = 0; //real values of pot
    int lastState = 0; //previous
    int value = 0; //mapped values of pot (sent)
    int lastValue = 0; //previous

    Mux* mux;
    bool isMuxPinned = true;

    //Smoothing pot
    const byte threshold = 25;
    unsigned long lastTime = 0;
    unsigned long timer = 0;
    const byte TIMEOUT = 200; //in milliseconds
    
    //ResponsiveAnalogRead.h
    const float snapMultiplier = 0.01; // (0.0 - 1.0) - Increase for faster, but less smooth reading
    ResponsiveAnalogRead responsivePot;
    
    bool isChanged = false;

    byte getPin();
  public:
    Pot(Mux *mux, byte pin, byte CC, bool isMuxPinned);
    Pot(Mux *mux, byte pin, byte CC);
    void init();
    void update();

    byte getValue();
    byte getCC();

    void read();
    bool hasChanged();
};

#endif
