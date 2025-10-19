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
#define POT_1_PIN 1
#define POT_1_CC 23

#define POT_2_PIN 0
#define POT_2_CC 17

#define POT_3_PIN A0
#define POT_3_CC 22

#define POT_4_PIN A6
#define POT_4_CC 28

const int N_POTS = 4;

Pot pots[N_POTS] = {
  Pot(mux_analog, POT_1_PIN,POT_1_CC),  //pin of mux
  Pot(mux_analog, POT_2_PIN,POT_2_CC),  //pin of mux
  Pot(mux_analog, POT_3_PIN,POT_3_CC, false), //pin of arduino
  Pot(mux_analog, POT_4_PIN,POT_4_CC, false), //pin of arduino
};


//Switches
#define SWITCH_1_PIN 0
#define SWITCH_1_GROUPCC 0

const int N_SWITCHES = 0;

Group groups[3] = {
  Group(0),
  Group(1),
  Group(2)
};

//Switch switches[N_SWITCHES] = {
//  Switch({2}, SWITCH_1_GROUPCC, 1),
//  Switch({3})
//}

//Settings
int delayBetweenWrites = 20;


/* ================================================================================================ */

void setup ()
{
  //MUX
  pinMode(MUX1_PIN, INPUT);
  pinMode(MUX2_PIN, INPUT);

  
  //inits
  writeBtn.init();
  manualBtn.init();
  for (int i = 0; i < N_POTS; i++) {
    pots[i].init();
  }
  //Switch sw = Switch(mux_digital, 0, 1, 0, 1, false);
  //groups[0].addSwitch(sw);

  
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
    if (pots[i].hasChanged()) {
      send(pots[i].getCC(), 1);
      send(pots[i].getValue(), 0);  
    }
  }
}  // end of loop


/* =================================================== */

void sendAll() {
  //Pots
  for (int i = 0; i < N_POTS; i++) {
    send(pots[i].getCC(), 1);
    send(pots[i].getValue(), 0);
  }

  //Switches


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
