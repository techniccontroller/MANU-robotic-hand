#include <Servo.h>

#include "Roboterhand.h"

Roboterhand rob = Roboterhand();

void setup() {
  rob.setLEDFadeTime(1000, 1000);
}

void loop() {
  rob.setLEDColor(0,0,255);
  rob.smoothMovement(&Roboterhand::setWrist, 50, 0, 20);
  countRow();
  delay(1000);
  wave();
  delay(1000);
  rob.setLEDColor(255,0,255);
  rob.smoothMovement(&Roboterhand::setWrist, 0, 50, 20);
  peace();
  delay(1000);
  rock();
  delay(1000);
  thumbUp();
  delay(1000);
  rob.setLEDColor(0,255,255);
  indexUp();
  delay(1000);
  majeureUp();
  delay(3000);
}


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

void peace(){
  int a[] = {100, 0, 0, 100, 100, 50};
  rob.setAll(a, true);
}

void rock(){
  int a[] = {100, 0, 100, 100, 0, 50};
  rob.setAll(a, true);
}

void thumbUp(){
  int a[] = {0, 100, 100, 100, 100, 50};
  rob.setAll(a, true);
}

void indexUp(){
  int a[] = {100, 0, 100, 100, 100, 50};
  rob.setAll(a, true);
}

void majeureUp(){
  int a[] = {100, 100, 0, 100, 100, 50};
  rob.setThumb(100, true);
  rob.setAll(a, true);
}





