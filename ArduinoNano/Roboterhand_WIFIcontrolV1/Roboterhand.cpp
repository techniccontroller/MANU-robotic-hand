/** MANU - robotic hand 
 *  Code for Arduino Nano (connected to ESP8266)
 *  Video on Youtube: https://youtu.be/UN8Itcejvu4
 *  
 *  created 27 March 2018
 *  by techniccontroller
 */
 
#include "Roboterhand.h"
#include <Arduino.h>

// Constructor with initalisation
Roboterhand::Roboterhand(){
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT); 
}

// Saturation 0 to 100
int Roboterhand::limit100(int input){
  if(input > 100) return 100;
  if(input < 0) return 0;
  else return input;
}

// Convert percent to absolut angle
int Roboterhand::relToAbs(int min, int max, int rel){
  return (limit100(rel)*(max-min))/100+min;
}

// Print every angle
void Roboterhand::printStatus(){
  Serial.print(val_thumb);
  Serial.print(", ");
  Serial.print(val_index);
  Serial.print(", ");
  Serial.print(val_majeure);
  Serial.print(", ");
  Serial.print(val_ringfinger);
  Serial.print(", ");
  Serial.print(val_pinky);
  Serial.print(", ");
  Serial.print(val_wrist);
  Serial.println();
}

// update all servos with the new angle
void Roboterhand::servoupdate(){
  servothumb.write(val_thumb);
  servoindex.write(val_index);
  servomajeure.write(val_majeure);
  servoringfinger.write(val_ringfinger);
  servopinky.write(val_pinky);
  servowrist.write(val_wrist);
}

// detach all servos
void Roboterhand::servodetach(){
  servothumb.detach();
  servoindex.detach();
  servomajeure.detach();
  servoringfinger.detach();
  servopinky.detach();
  servowrist.detach();
}

// attach all servos
void Roboterhand::servoattach(){
  servothumb.attach(THUMB);
  servoindex.attach(INDEX);
  servomajeure.attach(MAJEURE);
  servoringfinger.attach(RINGFINGER);
  servopinky.attach(PINKY);
  servowrist.attach(WRIST);
}

// set all servos to new positions (percent)
void Roboterhand::setAll(int vals[], bool detach){
  val_thumb = relToAbs(aus_thumb, ein_thumb, vals[0]);
  val_index = relToAbs(aus_index, ein_index, vals[1]);;
  val_majeure = relToAbs(aus_majeure, ein_majeure, vals[2]);;
  val_ringfinger = relToAbs(aus_ringfinger, ein_ringfinger, vals[3]);
  val_pinky = relToAbs(aus_pinky, ein_pinky, vals[4]);
  val_wrist = relToAbs(aus_wrist, ein_wrist, vals[5]);
  if(detach) refresh();
}

// set only Thumbservo to new postion (percent)
void Roboterhand::setThumb(int val, bool detach){
	val_thumb = relToAbs(aus_thumb, ein_thumb, val);
  if(detach) refresh();
}

// set only Indexservo to new postion (percent)
void Roboterhand::setIndex(int val, bool detach){
	val_index = relToAbs(aus_index, ein_index, val);
  if(detach) refresh();
}

// set only Majeureservo to new postion (percent)
void Roboterhand::setMajeure(int val, bool detach){
	val_majeure = relToAbs(aus_majeure, ein_majeure, val);
  if(detach) refresh();
}

// set only Ringfingerservo to new postion (percent)
void Roboterhand::setRingfinger(int val, bool detach){
	val_ringfinger = relToAbs(aus_ringfinger, ein_ringfinger, val);
  if(detach) refresh();
}

// set only Pinkyservo to new postion (percent)
void Roboterhand::setPinky(int val, bool detach){
	val_pinky = relToAbs(aus_pinky, ein_pinky, val);
  if(detach) refresh();
}

// set only Wristservo to new postion (percent)
void Roboterhand::setWrist(int val, bool detach){
  val_wrist = relToAbs(aus_wrist, ein_wrist, val);
  if(detach) refresh();
}

// Do an smooth movement with the given function
void Roboterhand::smoothMovement(void (Roboterhand::*set)(int, bool), int mybegin, int myend, int mydelay){
  for(int i = mybegin; i != myend; mybegin < myend ? i++ : i--){
    (this->*set)(i, false);
    delay(mydelay);
  }
  servodetach();
}

// set Color of the LED-Strip
void Roboterhand::setLEDColor(int r, int g, int b){
  if(r >= 0) val_red = r;
  if(g >= 0) val_green = g;
  if(b >= 0) val_blue = b;
  digitalWrite(LED_RED, val_red);
  digitalWrite(LED_GREEN, val_green);
  digitalWrite(LED_BLUE, val_blue);
}

// Set FadeTime of the LED-Strip
void Roboterhand::setLEDFadeTime(int fadeUpTime, int fadeDownTime){
  SoftPWMSetFadeTime(LED_RED, fadeUpTime, fadeDownTime);
  SoftPWMSetFadeTime(LED_GREEN, fadeUpTime, fadeDownTime);
  SoftPWMSetFadeTime(LED_BLUE, fadeUpTime, fadeDownTime);
}

// refresh servo positions
void Roboterhand::refresh(){
  servoattach();
  servoupdate();
  delay(500);
  servodetach();
}

