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
    Switch* switches[10];
    bool isChanged = false;
    int nbInGroup;
  public:
    Group(byte CC, int nbInGroup);
    void init();
    void update();
    byte getCC();
    byte getMask();
    byte getValue();
    void addSwitch(Switch* sw);
    bool hasChanged();
};

#endif
