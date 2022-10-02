/*
 * S-RC001 - 8x relay controller using Arduino Nano
 * MIDI controllable like Phobos' Ensembles plus concurrent control using arcade buttons 
 * Phobos/W (www.sonoscopia.pt)
 * code by Tiago Ângelo (www.tiagoangelo.net)
*/

#include <MIDI.h>
#define MIDICH 1
#define START 96
#define SIZE 8

// ARCADE BUTTON PINS (input)
#define B1 A0
#define B2 A1
#define B3 A2
#define B4 A3
#define B5 A4
#define B6 A5
#define B7 9
#define B8 10
// RELAY PINS (output)
#define R8 2
#define R7 4
#define R6 5
#define R5 6
#define R4 7
#define R3 8
#define R2 11
#define R1 12

// make note to pin array
byte note2pin[SIZE];
byte pitch;

// button variables
byte butstate[SIZE], _butstate[SIZE];
byte buttons[SIZE] = {B1, B2, B3, B4, B5, B6, B7, B8};

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin(MIDICH);
  MIDI.turnThruOn();

  //set input pins
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);
  pinMode(B5, INPUT_PULLUP);
  pinMode(B6, INPUT_PULLUP);
  pinMode(B7, INPUT_PULLUP);
  pinMode(B8, INPUT_PULLUP);

  // set output pins 
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  // set init value
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  digitalWrite(R5, HIGH);
  digitalWrite(R6, HIGH);
  digitalWrite(R7, HIGH);
  digitalWrite(R8, HIGH);

  // set note2pin array
  note2pin[0] = R1;
  note2pin[1] = R2;
  note2pin[2] = R3;
  note2pin[3] = R4;
  note2pin[4] = R5;
  note2pin[5] = R6;
  note2pin[6] = R7;
  note2pin[7] = R8;
}

void loop() {
 // MIDI CONTROL 
 if(MIDI.read()){
      switch(MIDI.getType()){
        case midi::NoteOn:
          pitch = MIDI.getData1();
          if(pitch >= START && pitch < START+SIZE){
            digitalWrite(note2pin[pitch-START], LOW);
          }
        break;

        case midi::NoteOff:
          pitch = MIDI.getData1();
          if(pitch >= START && pitch < START+SIZE){
            digitalWrite(note2pin[pitch-START], HIGH);
          }
        break;
      }
  } 
  
  // BUTTON CONTROL
  for(int i = 0; i < SIZE; i++){
    _butstate[i] = butstate[i]; // update previous state
    butstate[i] = digitalRead(buttons[i]); // read current state
    if(butstate[i] != _butstate[i]){
      digitalWrite(note2pin[i], butstate[i]);
    }
  } 
}
