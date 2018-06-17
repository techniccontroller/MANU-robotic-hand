#include <Servo.h>
#include <SoftPWM.h>
#include "Roboterhand.h"
/*
#define THUMB 4
#define INDEX 2
#define MAJEURE 3
#define RINGFINGER 6
#define PINKY 5
#define WRIST 7


Servo servothumb;
Servo servoindex;
Servo servomajeure;
Servo servoringfinger;
Servo servopinky;
Servo servowrist;


char in;
int val_thumb = 35;
int val_index = 50;
int val_majeure = 55;
int val_ringfinger = 50;
int val_pinky = 50;
int val_wrist = 80;

const int ein_thumb = 155;
const int ein_index = 165;
const int ein_majeure = 180;
const int ein_ringfinger = 170;
const int ein_pinky = 180;

const int aus_thumb = 35;
const int aus_index = 50;
const int aus_majeure = 55;
const int aus_ringfinger = 50;
const int aus_pinky = 50;*/

void setup() { 
  
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);

  SoftPWMBegin();
  
  SoftPWMSet(LED_BLUE, 0);

  SoftPWMSetFadeTime(LED_BLUE, 1000, 1000);
  Serial.begin(9600);
  
} 

void loop() {
  SoftPWMSet(LED_BLUE, 255);
  while(true){
    in = ownRead();
    if(in != '0'){
      servoattach();
      Serial.println(in);
      switch (in){
        case 't':
          val_thumb = ownParseInt();
          break;
        case 'i':
          val_index = ownParseInt();
          break;
        case 'a':
          val_majeure = ownParseInt();
          break;
        case 'r':
          val_ringfinger = ownParseInt();
          break;
        case 'p':
          val_pinky = ownParseInt();
          break;
        case 'w':
          val_wrist = ownParseInt();
          break;
        // Movement inkremental open
        case 'c':
          val_thumb  = ein_thumb;
          break;
        case 'v':
          val_index  = ein_index;
          break;
        case 'b':
          val_majeure = ein_majeure;
          break;
        case 'n':
          val_ringfinger  = ein_ringfinger;
          break;
        case 'm':
          val_pinky  = ein_pinky;
          break;
        case 's':
          val_wrist += 20;
          break;  
        // Movement inkremental close
        case 'd':
          val_thumb = aus_thumb;
          break;
        case 'f':
          val_index = aus_index;
          break;
        case 'g':
          val_majeure = aus_majeure;
          break;
        case 'h':
          val_ringfinger = aus_ringfinger;
          break;
        case 'j':
          val_pinky = aus_pinky;
          break;
        case 'k':
          val_wrist -= 20;
          break;  
        default:
          ownParseInt();
      }
      serialStatus();
      servoupdate();
      delay(500);
      servodetach();
    }  
  }
}



int ownParseInt(){
  return Serial.parseInt();
}

char ownRead(){
  if (Serial.available()) return Serial.read();
  return '0';
}

