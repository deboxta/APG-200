/*############################################
#
#  APG-200 
#  a PG200 emulator
#
#  (c) Yannick Côté
#
#  Emulate the roland PG-200 protocol
#
############################################*/

#include "Button.h"
#include "Potentiometer.h"
#include "Switch.h"
#include "Group.h"
#include "Mux.h"

//MUX
#define MUX1_PIN A2
Mux mux_analog(MUX1_PIN,A1,A5,A4,A3);
#define MUX2_PIN 7
Mux mux_digital(MUX2_PIN,3,4,5,6);

//Buttons
#define BUTTON_1_PIN 12
#define BUTTON_1_CC 129
#define BUTTON_1_VALUE 0

#define BUTTON_2_PIN 11
#define BUTTON_2_CC 130
#define BUTTON_2_VALUE 255

Button writeBtn(BUTTON_1_PIN, BUTTON_1_CC, BUTTON_1_VALUE);
Button manualBtn(BUTTON_2_PIN, BUTTON_2_CC, BUTTON_2_VALUE);

#define BAUD 31250 // 57600  //31250 for pg-200

//Potentiometers

//Env mod
#define POT_1_PIN 0
#define POT_1_CC 24
//LFO mod 
#define POT_2_PIN 1
#define POT_2_CC 25
//Release
#define POT_3_PIN 2
#define POT_3_CC 33
//Sustain 
#define POT_4_PIN 3
#define POT_4_CC 32
//Decay 
#define POT_5_PIN 4
#define POT_5_CC 31
//Attack  
#define POT_6_PIN 5
#define POT_6_CC 30
//LFO rate
#define POT_7_PIN 6
#define POT_7_CC 28
//LFO delay time
#define POT_8_PIN 7
#define POT_8_CC 29
//Pitch follow
#define POT_9_PIN 8
#define POT_9_CC 26
//Env amount 
#define POT_10_PIN 9
#define POT_10_CC 18
//LFO amount
#define POT_11_PIN 10
#define POT_11_CC 19
//Cut off freq
#define POT_12_PIN 11
#define POT_12_CC 23
//Fine tune
#define POT_13_PIN 12
#define POT_13_CC 16
//HPF
#define POT_14_PIN 13
#define POT_14_CC 21
//Source mix
#define POT_15_PIN 14
#define POT_15_CC 20
//Tune 
#define POT_16_PIN 15
#define POT_16_CC 17
//Resonance 
#define POT_17_PIN A0
#define POT_17_CC 22
//VCA level
#define POT_18_PIN A6
#define POT_18_CC 27

const int N_POTS = 18;

Pot* pots[N_POTS] = {
  new Pot(mux_analog, POT_1_PIN,POT_1_CC),  //pin of mux
  new Pot(mux_analog, POT_2_PIN,POT_2_CC),  //pin of mux
  new Pot(mux_analog, POT_3_PIN,POT_3_CC),  //pin of mux
  new Pot(mux_analog, POT_4_PIN,POT_4_CC),  //pin of mux
  new Pot(mux_analog, POT_5_PIN,POT_5_CC),  //pin of mux
  new Pot(mux_analog, POT_6_PIN,POT_6_CC),  //pin of mux
  new Pot(mux_analog, POT_7_PIN,POT_7_CC),  //pin of mux
  new Pot(mux_analog, POT_8_PIN,POT_8_CC),  //pin of mux
  new Pot(mux_analog, POT_9_PIN,POT_9_CC),  //pin of mux
  new Pot(mux_analog, POT_10_PIN,POT_10_CC),  //pin of mux
  new Pot(mux_analog, POT_11_PIN,POT_11_CC),  //pin of mux
  new Pot(mux_analog, POT_12_PIN,POT_12_CC),  //pin of mux
  new Pot(mux_analog, POT_13_PIN,POT_13_CC),  //pin of mux
  new Pot(mux_analog, POT_14_PIN,POT_14_CC),  //pin of mux
  new Pot(mux_analog, POT_15_PIN,POT_15_CC),  //pin of mux
  new Pot(mux_analog, POT_16_PIN,POT_16_CC),  //pin of mux
  new Pot(mux_analog, POT_17_PIN,POT_17_CC, false), //pin of arduino
  new Pot(mux_analog, POT_18_PIN,POT_18_CC, false), //pin of arduino
};


//Switches

//LFO switch DCO 1
#define SWITCH_1_PIN 8
#define SWITCH_1_BITPOS1 7
#define SWITCH_1_GROUPCC 1
//Env switch DCO 1
#define SWITCH_2_PIN 9
#define SWITCH_2_BITPOS1 6
#define SWITCH_2_GROUPCC 1
//Env polarity, DCOs
#define SWITCH_3_PIN 10
#define SWITCH_3_BITPOS1 2
#define SWITCH_3_GROUPCC 2
//LFO switch DCO 2
#define SWITCH_4_PIN 11
#define SWITCH_4_BITPOS1 5
#define SWITCH_4_GROUPCC 1
//Env switch DCO 2
#define SWITCH_5_PIN 12
#define SWITCH_5_BITPOS1 4
#define SWITCH_5_GROUPCC 1
//Env polarity, VCF
#define SWITCH_6_PIN 13
#define SWITCH_6_BITPOS1 2
#define SWITCH_6_GROUPCC 1
//Chorus
#define SWITCH_7_PIN 14
#define SWITCH_7_BITPOS1 3
#define SWITCH_7_GROUPCC 2
//VCA mode
#define SWITCH_8_PIN 15
#define SWITCH_8_BITPOS1 3
#define SWITCH_8_GROUPCC 1

const int N_GROUPS = 2;

Group* groups[N_GROUPS] = {
  new Group(1,6),
  new Group(2, 2)
};

//Settings
int delayBetweenWrites = 20;


/* ================================================================================================ */

void setup ()
{
  //inits
  mux_analog.init();
  mux_digital.init();
  
  writeBtn.init();
  manualBtn.init();
  
  for (int i = 0; i < N_POTS; i++) {
    pots[i]->init();
  }
  
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_6_PIN, SWITCH_6_BITPOS1, SWITCH_6_GROUPCC, true));
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_8_PIN, SWITCH_8_BITPOS1, SWITCH_8_GROUPCC, true));
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_5_PIN, SWITCH_5_BITPOS1, SWITCH_5_GROUPCC, true));
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_4_PIN, SWITCH_4_BITPOS1, SWITCH_4_GROUPCC, true));
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_2_PIN, SWITCH_2_BITPOS1, SWITCH_2_GROUPCC, true));
  groups[0]->addSwitch(new Switch(mux_digital, SWITCH_1_PIN, SWITCH_1_BITPOS1, SWITCH_1_GROUPCC, true));

  groups[1]->addSwitch(new Switch(mux_digital, SWITCH_7_PIN, SWITCH_7_BITPOS1, SWITCH_7_GROUPCC, true));
  groups[1]->addSwitch(new Switch(mux_digital, SWITCH_3_PIN, SWITCH_3_BITPOS1, SWITCH_3_GROUPCC, true));

  groups[0]->init();
  groups[1]->init();
  
  Serial.begin (BAUD, SERIAL_8N1, true); // 9 bit mode
  
  //Startup ping
  delay(2500);
  send(128, 1);
  send(0, 0);

}  // end of setup


/* =================================================== */


void loop ()
{
  if (writeBtn.isPressed()) {
    send(writeBtn.getCC(), 1);
    send(writeBtn.getValue(), 0);
  }

  if (manualBtn.isPressed()) {
    send(manualBtn.getCC(), 1);
    send(manualBtn.getValue(), 0);
    send(0,0);
    sendAll();
  }

  for (int i = 0; i < N_POTS; i++) {
    if (pots[i]->hasChanged()) {
      send(pots[i]->getCC(), 1);
      send(pots[i]->getValue(), 0);  
    }
  }

  for (int i = 0; i < N_GROUPS; i++) {
    if (groups[i]->hasChanged()) {
      send(groups[i]->getCC(), 1);
      send(groups[i]->getMask(), 0);
      send(groups[i]->getValue(), 0);  
    }
  }
}  // end of loop


/* =================================================== */

void sendAll() {
  //Pots
  for (int i = 0; i < N_POTS; i++) {
    send(pots[i]->getCC(), 1);
    send(pots[i]->getValue(), 0);
  }

  //Switches
  for (int i = 0; i < N_GROUPS; i++) {
    send(groups[i]->getCC(), 1);
    send(groups[i]->getMask(), 0);
    send(groups[i]->getValue(), 0);  
  }

}

void send(byte value, int ind) {
  delay(delayBetweenWrites);
  Serial.write9bit(to9Bits(value, ind));
}

int to9Bits(int address, int value)
{
  if (value == 1) {
    address += 0b100000000; //256;
  }
  return address;
}


/* =================================================== */


//8 value or address bits, 9th (left most one) bit indicates if byte is a value/mask or an address:
//0: Value or mask
//1: Address

//POTENTIOMETERS (addresses above 15 only)

//1: Address
//2: Value (0-255)

//Potmeter     Address
//Fine tune       16
//Tune            17
//Env amount      18
//LFO amount      19
//Source mix      20
//HPF             21
//Resonance       22
//Cut off freq    23
//Env mod         24

//Potmeter     Address
//LFO mod         25
//Pitch follow    26
//VCA level       27
//LFO rate        28
//LFO delay time  29
//Attack          30
//Decay           31
//Sustain         32
//Release         33

//SPECIAL COMMANDS

//Command                Address       Value
//Manual                  130           all address/value bytes (?)
//Write                   129           0
//Ping (sent on startup)  128           0
