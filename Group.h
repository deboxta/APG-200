#ifndef GROUP_H
#define GROUP_H

#include "Switch.h"

class Group {
  private:
    byte CC;
    byte bitMask = 0b00000000;;
    byte value = 0b00000000;;
    byte index = 0;
    Switch* switches[7];
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
