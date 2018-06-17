#include <Servo.h>
#include <SoftPWM.h>


Servo servothumb;          // Define thumb servo
Servo servoindex;          // Define index servo
Servo servomajeure;
Servo servoringfinger;
Servo servopinky;
Servo servowrist;



void setup() { 
  servoattach();
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);

  SoftPWMBegin();
  
  SoftPWMSet(A0, 0);

  SoftPWMSetFadeTime(A0, 1000, 1000);

  
} 

void loop() {
  SoftPWMSet(A0, 255);
  delay(1000);
  servoattach();
  alltozero();           
  delay(500);           
  servodetach();
  SoftPWMSet(A0, 0);
  delay(10000);

}
// Motion to set the servo into "virtual" 0 position: allto90
void allto90() {         
  servothumb.write(90);
  servoindex.write(90);
  servomajeure.write(90);
  servoringfinger.write(90);
  servopinky.write(90);
  servowrist.write(90);
}
// Motion to set the servo into "rest" position: alltozero
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
  servothumb.attach(2);
  servoindex.attach(3);
  servomajeure.attach(4);
  servoringfinger.attach(5);
  servopinky.attach(6);
  servowrist.attach(7);
}

