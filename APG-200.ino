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

#include <ResponsiveAnalogRead.h>

#include "Button.h"

#define BUTTON_1_PIN 2
#define BUTTON_1_CC 129
#define BUTTON_1_VALUE 0
#define BUTTON_2_PIN 6
#define BUTTON_2_CC 130
#define BUTTON_2_VALUE 255

Button writeBtn(BUTTON_1_PIN, BUTTON_1_CC, BUTTON_1_VALUE);
Button manualBtn(BUTTON_2_PIN, BUTTON_2_CC, BUTTON_2_VALUE);

int delayBetweenWrites = 20;

//Potentiometers
const int N_POTS = 2;
byte potPin[N_POTS] = {A0, A1};
int potCC[N_POTS] = {23, 17};
int potReading[N_POTS] = {0};
int potState[N_POTS] = {0};
int potPState[N_POTS] = {0}; //previous
int potDataState[N_POTS] = {0};
int potDataPState[N_POTS] = {0}; //previous

//Smoothing pot
byte potThreshold = 20;
unsigned long lastPotTime[N_POTS] = {0};
unsigned long potTimer[N_POTS] = {0};
const int POT_TIMEOUT = 300; //in milliseconds
//ResponsiveAnalogRead.h
float snapMultiplier = 0.01; // (0.0 - 1.0) - Increase for faster, but less smooth reading
ResponsiveAnalogRead responsivePot[N_POTS] = {};

/* =================================================== */

void setup ()
{
  //ResponsiveAnalogRead (for pots smooting)
  for (int i = 0; i < N_POTS; i++) {
    responsivePot[i] = ResponsiveAnalogRead(0, true, snapMultiplier);
    responsivePot[i].setAnalogResolution(1023);
  }

  //Set values of pots so we don't enter the loop prematurely on startup
  for (int i = 0; i < N_POTS; i++) {
    potRead(i);
    potPState[i] = potState[i];
  }

  Serial.begin (31250, SERIAL_8N1, true); // 9 bit mode

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


  potentiometers();
}  // end of loop


/* =================================================== */

void sendAll() {
  //Pots
  for (int i = 0; i < N_POTS; i++) {
    potRead(i);
    potDataState[i] = map(potState[i], 0, 1023, 0, 255);
    send(potCC[i], 1);
    send(potDataState[i], 0);
  }

  //Switches


}

void send(int value, int ind) {
  delay(delayBetweenWrites);
  Serial.write9bit(to9Bits(value, ind));
}

void potRead(int i) {
  potReading[i] = analogRead(potPin[i]);
  responsivePot[i].update(potReading[i]);
  potState[i] = responsivePot[i].getValue();
}

void potentiometers() {
  for (int i = 0; i < N_POTS; i++) {
    potRead(i);
    potDataState[i] = map(potState[i], 0, 1023, 0, 255);

    int potVar = abs(potState[i] - potPState[i]);

    if (potVar > potThreshold) {
      lastPotTime[i] = millis(); //reset
    }

    potTimer[i] = millis() - lastPotTime[i];

    if (potTimer[i] < POT_TIMEOUT && millis() >= POT_TIMEOUT) {
      if (potDataState[i] != potDataPState[i]) {
        send(potCC[i], 1);
        send(potDataState[i], 0);


        potDataPState[i] = potDataState[i];
      }
      potPState[i] = potState[i];

    }
  }
}

int to9Bits(int address, int value)
{
  if (value == 1) {
    address += 256;
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

