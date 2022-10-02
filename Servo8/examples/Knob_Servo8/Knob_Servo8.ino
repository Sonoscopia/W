/* 
 Controlling a servo position using a potentiometer (variable resistor) 
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo serv1, serv2, serv3, serv4, serv5, serv6, serv7, serv8 ;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup()
{
  serv1.attach(2);  // attaches the servo on pin 9 to the servo object
  serv2.attach(3);
  serv3.attach(4);
  serv4.attach(7);
  serv5.attach(8);
  serv6.attach(11);
  serv7.attach(12);
  serv8.attach(13);
  Serial.begin(9600);
}

void loop() 
{ 
  //val = analogRead(potpin) >> 4;            // reads the value of the potentiometer (value between 0 and 1023) 
  //val = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180) 
  if(Serial.available()>0) {val = Serial.parseInt(); Serial.println(val);}
  serv1.write(val);                  // sets the servo position according to the scaled value 
  serv2.write(val);
  serv3.write(val);
  serv4.write(val);
  serv5.write(val);
  serv6.write(val);
  serv7.write(val);
  serv8.write(val);
  delay(15);                           // waits for the servo to get there 
} 

