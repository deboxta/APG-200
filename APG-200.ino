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

Pot pot1(&mux_analog, POT_1_PIN, POT_1_CC); //pin of mux
Pot pot2(&mux_analog, POT_2_PIN, POT_2_CC); //pin of mux
Pot pot3(&mux_analog, POT_3_PIN, POT_3_CC); //pin of mux
Pot pot4(&mux_analog, POT_4_PIN, POT_4_CC); //pin of mux
Pot pot5(&mux_analog, POT_5_PIN, POT_5_CC); //pin of mux
Pot pot6(&mux_analog, POT_6_PIN, POT_6_CC); //pin of mux
Pot pot7(&mux_analog, POT_7_PIN, POT_7_CC); //pin of mux
Pot pot8(&mux_analog, POT_8_PIN, POT_8_CC); //pin of mux
Pot pot9(&mux_analog, POT_9_PIN, POT_9_CC); //pin of mux
Pot pot10(&mux_analog, POT_10_PIN, POT_10_CC); //pin of mux
Pot pot11(&mux_analog, POT_11_PIN, POT_11_CC); //pin of mux
Pot pot12(&mux_analog, POT_12_PIN, POT_12_CC); //pin of mux
Pot pot13(&mux_analog, POT_13_PIN, POT_13_CC); //pin of mux
Pot pot14(&mux_analog, POT_14_PIN, POT_14_CC); //pin of mux
Pot pot15(&mux_analog, POT_15_PIN, POT_15_CC); //pin of mux
Pot pot16(&mux_analog, POT_16_PIN, POT_16_CC); //pin of mux
Pot pot17(&mux_analog, POT_17_PIN, POT_17_CC, false); //pin of arduino
Pot pot18(&mux_analog, POT_18_PIN, POT_18_CC, false); //pin of arduino

const byte N_POTS = 18;
//
Pot* pots[N_POTS] = {
  &pot1,&pot2,&pot3,&pot4,&pot5,&pot6,&pot7,&pot8,&pot9,&pot10,&pot11,&pot12,&pot13,&pot14,&pot15,&pot16,&pot17,&pot18
};
//Pot* pots[N_POTS] = {
//  new Pot(&mux_analog, POT_1_PIN, POT_1_CC), //pin of mux
//  new Pot(&mux_analog, POT_2_PIN, POT_2_CC), //pin of mux
//  new Pot(&mux_analog, POT_3_PIN, POT_3_CC), //pin of mux
//  new Pot(&mux_analog, POT_4_PIN, POT_4_CC), //pin of mux
//  new Pot(&mux_analog, POT_5_PIN, POT_5_CC), //pin of mux
//  new Pot(&mux_analog, POT_6_PIN, POT_6_CC), //pin of mux
//  new Pot(&mux_analog, POT_7_PIN, POT_7_CC), //pin of mux
//  new Pot(&mux_analog, POT_8_PIN, POT_8_CC), //pin of mux
//  new Pot(&mux_analog, POT_9_PIN, POT_9_CC), //pin of mux
//  new Pot(&mux_analog, POT_10_PIN, POT_10_CC), //pin of mux
//  new Pot(&mux_analog, POT_11_PIN, POT_11_CC), //pin of mux
//  new Pot(&mux_analog, POT_12_PIN, POT_12_CC), //pin of mux
//  new Pot(&mux_analog, POT_13_PIN, POT_13_CC), //pin of mux
//  new Pot(&mux_analog, POT_14_PIN, POT_14_CC), //pin of mux
//  new Pot(&mux_analog, POT_15_PIN, POT_15_CC), //pin of mux
//  new Pot(&mux_analog, POT_16_PIN, POT_16_CC), //pin of mux
//  new Pot(&mux_analog, POT_17_PIN, POT_17_CC, false), //pin of arduino
//  new Pot(&mux_analog, POT_18_PIN, POT_18_CC, false), //pin of arduino
//};


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

//const byte N_GROUPS = 2;

Group group1(0, 4);
Group group2(1, 7);
Group group3(2, 3);

DualPole dualPole1(&mux_digital, SWITCH_9_PIN, SWITCH_9_PIN2, SWITCH_9_BITPOS1, SWITCH_9_BITPOS2, SWITCH_9_GROUPCC, true, false);
DualPole dualPole2(&mux_digital, SWITCH_10_PIN, SWITCH_10_PIN2, SWITCH_10_BITPOS1, SWITCH_10_BITPOS2, SWITCH_10_GROUPCC, false, true);
DualPole dualPole3(&mux_digital, SWITCH_11_PIN, SWITCH_11_PIN2, SWITCH_11_BITPOS1, SWITCH_11_BITPOS2, SWITCH_11_GROUPCC, true, true);
DualPole dualPole4(&mux_digital, SWITCH_12_PIN, SWITCH_12_PIN2, SWITCH_12_BITPOS1, SWITCH_12_BITPOS2, SWITCH_12_GROUPCC, true, true);

DualPole dualPole5(&mux_digital, SWITCH_13_PIN, SWITCH_13_PIN2, SWITCH_13_BITPOS1, SWITCH_13_BITPOS2, SWITCH_13_GROUPCC, true, true);
SinglePole singlePole1(&mux_digital, SWITCH_6_PIN, SWITCH_6_BITPOS1, SWITCH_6_GROUPCC, true);
SinglePole singlePole2(&mux_digital, SWITCH_8_PIN, SWITCH_8_BITPOS1, SWITCH_8_GROUPCC, true);
SinglePole singlePole3(&mux_digital, SWITCH_5_PIN, SWITCH_5_BITPOS1, SWITCH_5_GROUPCC, true);
SinglePole singlePole4(&mux_digital, SWITCH_4_PIN, SWITCH_4_BITPOS1, SWITCH_4_GROUPCC, true);
SinglePole singlePole5(&mux_digital, SWITCH_2_PIN, SWITCH_2_BITPOS1, SWITCH_2_GROUPCC, true);
SinglePole singlePole6(&mux_digital, SWITCH_1_PIN, SWITCH_1_BITPOS1, SWITCH_1_GROUPCC, true);

DualPole dualPole6(SWITCH_14_PIN, SWITCH_14_PIN2, SWITCH_14_BITPOS1, SWITCH_14_BITPOS2, SWITCH_14_GROUPCC);
SinglePole singlePole7(&mux_digital, SWITCH_7_PIN, SWITCH_7_BITPOS1, SWITCH_7_GROUPCC, true);
SinglePole singlePole8(&mux_digital, SWITCH_3_PIN, SWITCH_3_BITPOS1, SWITCH_3_GROUPCC, true);

//Settings
#define delayBetweenWrites 20


/* ================================================================================================ */

void setup ()
{
  Serial.begin (BAUD, SERIAL_8N1, true); // 9 bit mode
  //  Serial.println("test");
  //inits
  mux_analog.init();
  mux_digital.init();

  writeBtn.init();
  manualBtn.init();
  
  group1.addSwitch(&dualPole1);
  group1.addSwitch(&dualPole2);
  group1.addSwitch(&dualPole3);
  group1.addSwitch(&dualPole4);

  group2.addSwitch(&dualPole5);
  group2.addSwitch(&singlePole1);
  group2.addSwitch(&singlePole2);
  group2.addSwitch(&singlePole3);
  group2.addSwitch(&singlePole4);
  group2.addSwitch(&singlePole5);
  group2.addSwitch(&singlePole6);

  group3.addSwitch(&dualPole6);
  group3.addSwitch(&singlePole7);
  group3.addSwitch(&singlePole8);

  group1.init();
  group2.init();
  group3.init();

//  pot1.init();
//  pot2.init();
//  pot3.init();
//  pot4.init();
//  pot5.init();
//  pot6.init();
//  pot7.init();
//  pot8.init();
//  pot9.init();
//  pot10.init();
//  pot11.init();
//  pot12.init();
//  pot13.init();
//  pot14.init();
//  pot15.init();
//  pot16.init();
//  pot17.init();
//  pot18.init();

  for (byte i = 0; i < N_POTS; i++) {
    pots[i]->init();
  }
  
//  Serial.println("ok");

  //Startup ping
  delay(2500);
  send(128, 1);
  send(0, 0);

}  // end of setup


/* =================================================== */


void loop ()
{
  for (byte i = 0; i < N_POTS; i++) {
    if (pots[i]->hasChanged()) {
      send(pots[i]->getCC(), 1);
      send(pots[i]->getValue(), 0);
//      Serial.println("ho");
    }
  }
  
  if (writeBtn.isPressed()) {
    send(writeBtn.getCC(), 1);
    send(writeBtn.getValue(), 0);
  }

  if (manualBtn.isPressed()) {
    send(manualBtn.getCC(), 1);
    send(manualBtn.getValue(), 0);
    send(0, 0);
    sendAll();
  }

//  if (pot1.hasChanged()) {
//    send(pot1.getCC(), 1);
//    send(pot1.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot2.hasChanged()) {
//    send(pot2.getCC(), 1);
//    send(pot2.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot3.hasChanged()) {
//    send(pot3.getCC(), 1);
//    send(pot3.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot4.hasChanged()) {
//    send(pot4.getCC(), 1);
//    send(pot4.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot5.hasChanged()) {
//    send(pot5.getCC(), 1);
//    send(pot5.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot6.hasChanged()) {
//    send(pot6.getCC(), 1);
//    send(pot6.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot7.hasChanged()) {
//    send(pot7.getCC(), 1);
//    send(pot7.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot8.hasChanged()) {
//    send(pot8.getCC(), 1);
//    send(pot8.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot9.hasChanged()) {
//    send(pot9.getCC(), 1);
//    send(pot9.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot10.hasChanged()) {
//    send(pot10.getCC(), 1);
//    send(pot10.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot11.hasChanged()) {
//    send(pot11.getCC(), 1);
//    send(pot11.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot12.hasChanged()) {
//    send(pot12.getCC(), 1);
//    send(pot12.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot13.hasChanged()) {
//    send(pot13.getCC(), 1);
//    send(pot13.getValue(), 0);
////      Serial.println("ho");
//  }
//  if (pot14.hasChanged()) {
//    send(pot14.getCC(), 1);
//    send(pot14.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot15.hasChanged()) {
//    send(pot15.getCC(), 1);
//    send(pot15.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot16.hasChanged()) {
//    send(pot16.getCC(), 1);
//    send(pot16.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot17.hasChanged()) {
//    send(pot17.getCC(), 1);
//    send(pot17.getValue(), 0);
////    Serial.println("ho");
//  }
//  if (pot18.hasChanged()) {
//    send(pot18.getCC(), 1);
//    send(pot18.getValue(), 0);
////    Serial.println("ho");
//  }
  
  if (group1.hasChanged()) {
    send(group1.getCC(), 1);
    send(group1.getMask(), 0);
    send(group1.getValue(), 0);
//        Serial.println("fuck0");

  }
  if (group2.hasChanged()) {
    send(group2.getCC(), 1);
    send(group2.getMask(), 0);
    send(group2.getValue(), 0);
//    Serial.println("fuck1");
  }
  if (group3.hasChanged()) {
    send(group3.getCC(), 1);
    send(group3.getMask(), 0);
    send(group3.getValue(), 0);
//    Serial.println("fuck2");
  }
}  // end of loop


/* =================================================== */

void sendAll() {

  //Pots
  for (byte i = 0; i < N_POTS; i++) {
    send(pots[i]->getCC(), 1);
    send(pots[i]->getValue(), 0);
  }

//  send(pot1.getCC(), 1);
//  send(pot1.getValue(), 0);
//  send(pot2.getCC(), 1);
//  send(pot2.getValue(), 0);
//  send(pot3.getCC(), 1);
//  send(pot3.getValue(), 0);
//  send(pot4.getCC(), 1);
//  send(pot4.getValue(), 0);
//  send(pot5.getCC(), 1);
//  send(pot5.getValue(), 0);
//  send(pot6.getCC(), 1);
//  send(pot6.getValue(), 0);
//  send(pot7.getCC(), 1);
//  send(pot7.getValue(), 0);
//  send(pot8.getCC(), 1);
//  send(pot8.getValue(), 0);
//  send(pot9.getCC(), 1);
//  send(pot9.getValue(), 0);
//  send(pot10.getCC(), 1);
//  send(pot10.getValue(), 0);
//  send(pot11.getCC(), 1);
//  send(pot11.getValue(), 0);
//  send(pot12.getCC(), 1);
//  send(pot12.getValue(), 0);
//  send(pot13.getCC(), 1);
//  send(pot13.getValue(), 0);
//  send(pot14.getCC(), 1);
//  send(pot14.getValue(), 0);
//  send(pot15.getCC(), 1);
//  send(pot15.getValue(), 0);
//  send(pot16.getCC(), 1);
//  send(pot16.getValue(), 0);
//  send(pot17.getCC(), 1);
//  send(pot17.getValue(), 0);
//  send(pot18.getCC(), 1);
//  send(pot18.getValue(), 0);

  //Switches
  send(group1.getCC(), 1);
  send(group1.getMask(), 0);
  send(group1.getValue(), 0);

  send(group2.getCC(), 1);
  send(group2.getMask(), 0);
  send(group2.getValue(), 0);

  send(group3.getCC(), 1);
  send(group3.getMask(), 0);
  send(group3.getValue(), 0);

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
