#ifndef GROUP_H
#define GROUP_H

#include <Arduino.h>
#include "Switch.h"

class Group {
  private:
    byte CC;
    byte bitMask;
    byte value;
    byte lastValue;
    int index = 0;
    Switch* switches[8];
    bool isChanged = false;
  public:
    Group(byte CC);
    void init();
    void update();
    byte getCC();
    byte getMask();
    byte getValue();
    void addSwitch(Switch* sw);
    bool hasChanged();
};

#endif
