#include <Servo.h>
#include <SoftPWM.h>

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
int val_thumb = 0;
int val_index = 0;
int val_majeure = 60;
int val_ringfinger = 0;
int val_pinky = 0;
int val_wrist = 80;

final int ein_thumb = 155;
final int ein_index = 165;
final int ein_majeure = 180;
final int ein_ringfinger = 170;
final int ein_pinky = 180;

final int aus_thumb = 35;
final int aus_index = 50;
final int aus_majeure = 55;
final int aus_ringfinger = 50;
final int aus_pinky = 50;

void setup() { 
  
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);

  SoftPWMBegin();
  
  SoftPWMSet(A0, 0);

  SoftPWMSetFadeTime(A0, 1000, 1000);
  Serial.begin(9600);
  
} 

void loop() {
  SoftPWMSet(A0, 255);
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
          val_thumb -= 5;
          break;
        case 'v':
          val_index -= 5;
          break;
        case 'b':
          val_majeure -= 5;
          break;
        case 'n':
          val_ringfinger -= 5;
          break;
        case 'm':
          val_pinky -= 5;
          break;
        case 's':
          val_wrist += 20;
          break;  
        // Movement inkremental close
        case 'd':
          val_thumb += 5;
          break;
        case 'f':
          val_index += 5;
          break;
        case 'g':
          val_majeure += 5;
          break;
        case 'h':
          val_ringfinger += 5;
          break;
        case 'j':
          val_pinky += 5;
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

void serialStatus(){
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

void servoupdate(){
  servothumb.write(val_thumb);
  servoindex.write(val_index);
  servomajeure.write(val_majeure);
  servoringfinger.write(val_ringfinger);
  servopinky.write(val_pinky);
  servowrist.write(val_wrist);
  
}

// all Servo set to 90 degree: allto90
void allto90() {         
  servothumb.write(90);
  servoindex.write(90);
  servomajeure.write(90);
  servoringfinger.write(90);
  servopinky.write(90);
  servowrist.write(90);
}
// all Servo set to zero degree: alltozero
void alltozero() {         
  servothumb.write(0);
  servoindex.write(0);
  servomajeure.write(0);
  servoringfinger.write(0);
  servopinky.write(0);
  servowrist.write(0);
}


// Motion to set the servo into "max" position: alltomax
void alltomax() {
  servothumb.write(180);
  servoindex.write(180);
  servomajeure.write(180);
  servoringfinger.write(180);
  servopinky.write(180);
  servowrist.write(180);
}

void servodetach(){
  servothumb.detach();
  servoindex.detach();
  servomajeure.detach();
  servoringfinger.detach();
  servopinky.detach();
  servowrist.detach();
}

void servoattach(){
  servothumb.attach(THUMB);
  servoindex.attach(INDEX);
  servomajeure.attach(MAJEURE);
  servoringfinger.attach(RINGFINGER);
  servopinky.attach(PINKY);
  servowrist.attach(WRIST);
}

int ownParseInt(){
  return Serial.parseInt();
}

char ownRead(){
  if (Serial.available()) return Serial.read();
  return '0';
}

