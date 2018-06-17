#define THUMB 4
#define INDEX 2
#define MAJEURE 3
#define RINGFINGER 6
#define PINKY 5
#define WRIST 7
#define LED_BLUE A0
#define LED_RED A1
#define LED_GREEN A2


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
const int aus_pinky = 50;


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