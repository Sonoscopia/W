/*
 * using code for a 4051 * analog multiplexer / demultiplexer
 * by david c. and tomek n.* for k3 / malm� h�gskola
 * edited by Ross R.
 * edited by Igor de Oliveira Sá.
 * +
 * Adafruit I2C servo controller based on PCA9685
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 */  
 
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // deafault addres 0x40

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  90 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  390 // this is the 'maximum' pulse length count (out of 4096)

// 4051
#define S0 2
#define S1 3
#define S2 4

#define NUMPOTS 8
#define DEBUG 1

byte r0 = 0;      //value of select pin at the 4051 (s0)
byte r1 = 0;      //value of select pin at the 4051 (s1)
byte r2 = 0;      //value of select pin at the 4051 (s2)

unsigned int pots[NUMPOTS];
unsigned int _pots[NUMPOTS]; // previous pot value


void setup(){  
  if(DEBUG) Serial.begin(9600);
    
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  pwm.begin();
  //pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm.setPWMFreq(50); // TowerPro SG90 runs @50Hz
  delay(10);

}

void loop () {
  readPots();
  if(DEBUG) printArray(pots, NUMPOTS);
  moveServos();
}

void moveServos(){
  for (byte i=0; i<NUMPOTS; i++) {
    if(_pots[i] > pots[i]+2 || _pots[i] < pots[i]-2){
      int pulselen = map(pots[i], 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(i, 0, pulselen);
    }    
  }
}

void readPots(){
  for (byte i=0; i<NUMPOTS; i++) {
    // select the bit  
    //r0 = bitRead(count,0);    // use this with arduino 0013 (and newer versions)     
    //r1 = bitRead(count,1);    // use this with arduino 0013 (and newer versions)     
    //r2 = bitRead(count,2);    // use this with arduino 0013 (and newer versions)     
    r0 = i & 0x01;      // old version of setting the bits
    r1 = (i>>1) & 0x01;      // old version of setting the bits
    r2 = (i>>2) & 0x01;      // old version of setting the bits

    digitalWrite(S0, r0);
    digitalWrite(S1, r1);
    digitalWrite(S2, r2);

    //Either read or write the multiplexed pin here
    _pots[i] = pots[i];
    pots[i] = map(constrain(analogRead(A0), 0, 1000), 0, 1000, 0, 180);
  }  
}

void printArray(unsigned int* a, unsigned int m){
  for(int i = 0; i < NUMPOTS; i++){
    Serial.print(a[i]);
    Serial.print("   ");
  }
  Serial.println();
}
