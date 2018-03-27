/** MANU - robotic hand 
 *  Code for Arduino Nano (connected to ESP8266)
 *  Video on Youtube: https://youtu.be/UN8Itcejvu4
 *  
 *  created 27 March 2018
 *  by techniccontroller
 */

#include <Servo.h>

#include "Roboterhand.h"
#include <SoftwareSerial.h>
// ESP8266 is connected to Pins 10 and 11
SoftwareSerial WIFIserial(10,11); // RX | TX

// New object of a robotic hand (Roboterhand)
Roboterhand rob = Roboterhand();
int currentvals[]={0,0,0,0,0,0};

void setup() {
  // Communication to ESP8266 (webserver)
  WIFIserial.begin(9600);
  // USB Debug Connection
  Serial.begin(9600);
}

void loop() {
  // Wait for a command from webserver
  if(WIFIserial.available()){
    String command = WIFIserial.readStringUntil('/');
    Serial.println(command);
    if(command.startsWith("finger")){
      Serial.println("->finger");
      int nr = WIFIserial.parseInt();
      Serial.println(nr);
      if(WIFIserial.read() == '/') Serial.println("ok");
      int action = WIFIserial.parseInt();
      Serial.println(action);
      if(WIFIserial.read() == '/') Serial.println("ok end");
      switch(nr*2+action){
        case 0:
        rob.setThumb(0, true);
        break;
        case 1:
        rob.setThumb(100, true);
        break;
        case 2:
        rob.setIndex(0, true);
        break;
        case 3:
        rob.setIndex(100, true);
        break;
        case 4:
        rob.setMajeure(0, true);
        break;
        case 5:
        rob.setMajeure(100, true);
        break;
        case 6:
        rob.setRingfinger(0, true);
        break;
        case 7:
        rob.setRingfinger(100, true);
        break;
        case 8:
        rob.setPinky(0, true);
        break;
        case 9:
        rob.setPinky(100, true);
        break;
      }
    }
    else if(command.startsWith("led")){
      Serial.println("->led");
      int led = WIFIserial.parseInt();
      Serial.println(led);
      if(WIFIserial.read() == '/') Serial.println("ok");
      int value = WIFIserial.parseInt();
      Serial.println(value);
      if(WIFIserial.read() == '/') Serial.println("ok end");
      switch(led){
        case 0:
          rob.setLEDColor(value, -1, -1);
        break;
        case 1:
          rob.setLEDColor(-1, value, -1);
        break;
        case 2:
          rob.setLEDColor(-1, -1, value);
        break;
      }
    }
    else if(command.startsWith("slider")){
      Serial.println("->slider");
      int led = WIFIserial.parseInt();
      Serial.println(led);
      if(WIFIserial.read() == '/') Serial.println("ok");
      int value = WIFIserial.parseInt();
      Serial.println(value);
      if(WIFIserial.read() == '/') Serial.println("ok end");
      rob.setWrist(value, true);
    }
    else if(command.startsWith("complete")){
      Serial.println("->complete");
      int vals[]={0,0,0,0,0,0};
      bool refresh = false;
      for(int i = 0; i < 6; i++){
        Serial.print("ok: val = ");
        vals[i] = WIFIserial.parseInt();
        Serial.println(vals[i]);
        if(vals[i] != currentvals[i]) {
          refresh = true;
          currentvals[i] = vals[i];
        }
      }
      if(WIFIserial.read() == '/') Serial.println("ok end");
      if(refresh)rob.setAll(vals, true);
    }
  }
}

// Some example code snippets with different demo movements (not used yet)

// let the hand count to 5
void countRow(){
  rob.setThumb(100, true);
  rob.setIndex(100, true);
  rob.setMajeure(100, true);
  rob.setRingfinger(100, true);
  rob.setPinky(100, true);
  delay(1000);
  rob.setThumb(0, true);
  rob.setIndex(0, true);
  rob.setMajeure(0, true);
  rob.setRingfinger(0, true);
  rob.setPinky(0, true);
}

// move the hand in a wave shape
void wave(){
  rob.servoattach();
  for(int faktor = 0; faktor-50 <= 100; faktor += 10){
    int a[] = {faktor-0, faktor-10, faktor-20, faktor-30,faktor-40, faktor-50};
    rob.setAll(a, false);
    delay(50);
  }

  delay(1000);

  for(int faktor = 150; faktor >= 0; faktor -= 10){
    int a[] = {faktor-0, faktor-10, faktor-20, faktor-30,faktor-40, faktor-50};
    rob.setAll(a, false);
    rob.servoupdate();
    delay(300);
  }
  rob.servodetach();
}

// show the peace sign
void peace(){
  int a[] = {100, 0, 0, 100, 100, 50};
  rob.setAll(a, true);
}

// show the rock sign
void rock(){
  int a[] = {100, 0, 100, 100, 0, 50};
  rob.setAll(a, true);
}

// show thumb up sign
void thumbUp(){
  int a[] = {0, 100, 100, 100, 100, 50};
  rob.setAll(a, true);
}

// show index up sign
void indexUp(){
  int a[] = {100, 0, 100, 100, 100, 50};
  rob.setAll(a, true);
}

// show majeure up sign
void majeureUp(){
  int a[] = {100, 100, 0, 100, 100, 50};
  rob.setThumb(100, true);
  rob.setAll(a, true);
}





