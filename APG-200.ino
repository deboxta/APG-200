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
#include "SinglePole.h"
#include "DualPole.h"
#include "Group.h"
#include "Mux.h"

//MUX
#define MUX1_PIN A2
Mux mux_analog(MUX1_PIN, A1, A5, A4, A3);
#define MUX2_PIN 7
Mux mux_digital(MUX2_PIN, 3, 4, 5, 6);

//Buttons
#define BUTTON_1_PIN 12 //D12
#define BUTTON_1_CC 129
#define BUTTON_1_VALUE 0

#define BUTTON_2_PIN 11 //D11
#define BUTTON_2_CC 130
#define BUTTON_2_VALUE 255

Button* writeBtn = new Button(BUTTON_1_PIN, BUTTON_1_CC, BUTTON_1_VALUE);
Button* manualBtn = new Button(BUTTON_2_PIN, BUTTON_2_CC, BUTTON_2_VALUE);

#define BAUD 57600 // 57600  //31250 for pg-200

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
  new Pot(mux_analog, POT_1_PIN, POT_1_CC), //pin of mux
  new Pot(mux_analog, POT_2_PIN, POT_2_CC), //pin of mux
  new Pot(mux_analog, POT_3_PIN, POT_3_CC), //pin of mux
  new Pot(mux_analog, POT_4_PIN, POT_4_CC), //pin of mux
  new Pot(mux_analog, POT_5_PIN, POT_5_CC), //pin of mux
  new Pot(mux_analog, POT_6_PIN, POT_6_CC), //pin of mux
  new Pot(mux_analog, POT_7_PIN, POT_7_CC), //pin of mux
  new Pot(mux_analog, POT_8_PIN, POT_8_CC), //pin of mux
  new Pot(mux_analog, POT_9_PIN, POT_9_CC), //pin of mux
  new Pot(mux_analog, POT_10_PIN, POT_10_CC), //pin of mux
  new Pot(mux_analog, POT_11_PIN, POT_11_CC), //pin of mux
  new Pot(mux_analog, POT_12_PIN, POT_12_CC), //pin of mux
  new Pot(mux_analog, POT_13_PIN, POT_13_CC), //pin of mux
  new Pot(mux_analog, POT_14_PIN, POT_14_CC), //pin of mux
  new Pot(mux_analog, POT_15_PIN, POT_15_CC), //pin of mux
  new Pot(mux_analog, POT_16_PIN, POT_16_CC), //pin of mux
  new Pot(mux_analog, POT_17_PIN, POT_17_CC, false), //pin of arduino
  new Pot(mux_analog, POT_18_PIN, POT_18_CC, false), //pin of arduino
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

//DCO 1 range
#define SWITCH_9_PIN 1
#define SWITCH_9_PIN2 2 //D2
#define SWITCH_9_BITPOS1 0
#define SWITCH_9_BITPOS2 1
#define SWITCH_9_GROUPCC 0
//DCO 1 waveform
#define SWITCH_10_PIN 8 //D8
#define SWITCH_10_PIN2 0
#define SWITCH_10_BITPOS1 2
#define SWITCH_10_BITPOS2 3
#define SWITCH_10_GROUPCC 0
//DCO 2 range
#define SWITCH_11_PIN 7
#define SWITCH_11_PIN2 6
#define SWITCH_11_BITPOS1 4
#define SWITCH_11_BITPOS2 5
#define SWITCH_11_GROUPCC 0
//DCO 2 waveform
#define SWITCH_12_PIN 5
#define SWITCH_12_PIN2 4
#define SWITCH_12_BITPOS1 6
#define SWITCH_12_BITPOS2 7
#define SWITCH_12_GROUPCC 0
//Crossmod
#define SWITCH_13_PIN 3
#define SWITCH_13_PIN2 2
#define SWITCH_13_BITPOS1 0
#define SWITCH_13_BITPOS2 1
#define SWITCH_13_GROUPCC 1
//LFO waveform
#define SWITCH_14_PIN 9 //D9
#define SWITCH_14_PIN2 10 //D10
#define SWITCH_14_BITPOS1 0
#define SWITCH_14_BITPOS2 1
#define SWITCH_14_GROUPCC 2

const int N_GROUPS = 3;

//Group group1(0, 4);
//Group group2(1, 7);
//Group group3(2, 3);


//Settings
int delayBetweenWrites = 20;


/* ================================================================================================ */

void setup ()
{
  Serial.begin (BAUD, SERIAL_8N1, true); // 9 bit mode
//  Serial.println("test");
  //inits
  mux_analog.init();
  mux_digital.init();

  writeBtn->init();
  manualBtn->init();

  for (int i = 0; i < N_POTS; i++) {
    pots[i]->init();
  }

//  group1.addSwitch(new DualPole(mux_digital, SWITCH_9_PIN, SWITCH_9_PIN2, SWITCH_9_BITPOS1, SWITCH_9_BITPOS2, SWITCH_9_GROUPCC, true, false));
//  group1.addSwitch(new DualPole(mux_digital, SWITCH_10_PIN, SWITCH_10_PIN2, SWITCH_10_BITPOS1, SWITCH_10_BITPOS2, SWITCH_10_GROUPCC, false, true));
//  group1.addSwitch(new DualPole(mux_digital, SWITCH_11_PIN, SWITCH_11_PIN2, SWITCH_11_BITPOS1, SWITCH_11_BITPOS2, SWITCH_11_GROUPCC, true, true));
//  group1.addSwitch(new DualPole(mux_digital, SWITCH_12_PIN, SWITCH_12_PIN2, SWITCH_12_BITPOS1, SWITCH_12_BITPOS2, SWITCH_12_GROUPCC, true, true));

//  group2.addSwitch(new DualPole(mux_digital, SWITCH_13_PIN, SWITCH_13_PIN2, SWITCH_13_BITPOS1, SWITCH_13_BITPOS2, SWITCH_13_GROUPCC, true, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_6_PIN, SWITCH_6_BITPOS1, SWITCH_6_GROUPCC, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_8_PIN, SWITCH_8_BITPOS1, SWITCH_8_GROUPCC, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_5_PIN, SWITCH_5_BITPOS1, SWITCH_5_GROUPCC, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_4_PIN, SWITCH_4_BITPOS1, SWITCH_4_GROUPCC, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_2_PIN, SWITCH_2_BITPOS1, SWITCH_2_GROUPCC, true));
//  group2.addSwitch(new SinglePole(mux_digital, SWITCH_1_PIN, SWITCH_1_BITPOS1, SWITCH_1_GROUPCC, true));

//  group3.addSwitch(new DualPole(SWITCH_14_PIN, SWITCH_14_PIN2, SWITCH_14_BITPOS1, SWITCH_14_BITPOS2, SWITCH_14_GROUPCC));
//  group3.addSwitch(new SinglePole(mux_digital, SWITCH_7_PIN, SWITCH_7_BITPOS1, SWITCH_7_GROUPCC, true));
//  group3.addSwitch(new SinglePole(mux_digital, SWITCH_3_PIN, SWITCH_3_BITPOS1, SWITCH_3_GROUPCC, true));

//  group1.init();
//  group2.init();
//  group3.init();



  //Startup ping
  delay(2500);
  send(128, 1);
  send(0, 0);

}  // end of setup


/* =================================================== */


void loop ()
{
  if (writeBtn->isPressed()) {
    send(writeBtn->getCC(), 1);
    send(writeBtn->getValue(), 0);
  }

  if (manualBtn->isPressed()) {
    send(manualBtn->getCC(), 1);
    send(manualBtn->getValue(), 0);
    send(0, 0);
    sendAll();
  }

  for (int i = 0; i < N_POTS; i++) {
    if (pots[i]->hasChanged()) {
//      send(pots[i]->getCC(), 1);
//      send(pots[i]->getValue(), 0);
      Serial.println(i);
    }
  }

//  if (group1.hasChanged()) {
//    send(group1.getCC(), 1);
//    send(group1.getMask(), 0);
//    send(group1.getValue(), 0);
//  }
//  if (group2.hasChanged()) {
//    send(group2.getCC(), 1);
//    send(group2.getMask(), 0);
//    send(group2.getValue(), 0);
//  }
//  if (group3.hasChanged()) {
//    send(group3.getCC(), 1);
//    send(group3.getMask(), 0);
//    send(group3.getValue(), 0);
//  }
}  // end of loop


/* =================================================== */

void sendAll() {
//      Serial.println("yo3");

  //Pots
  for (int i = 0; i < N_POTS; i++) {
    send(pots[i]->getCC(), 1);
    send(pots[i]->getValue(), 0);
  }

  //Switches
//  send(group1.getCC(), 1);
//  send(group1.getMask(), 0);
//  send(group1.getValue(), 0);
//
//  send(group2.getCC(), 1);
//  send(group2.getMask(), 0);
//  send(group2.getValue(), 0);
//
//  send(group3.getCC(), 1);
//  send(group3.getMask(), 0);
//  send(group3.getValue(), 0);

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
