#include <Servo.h>
#include <SoftPWM.h>

#define THUMB 4
#define INDEX 2
#define MAJEURE 3
#define RINGFINGER 6
#define PINKY 5
#define WRIST 7
#define LED_BLUE A0
#define LED_RED A1
#define LED_GREEN A2

class Roboterhand{
  private:
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
    const int ein_wrist = 180;
    
    const int aus_thumb = 35;
    const int aus_index = 50;
    const int aus_majeure = 55;
    const int aus_ringfinger = 50;
    const int aus_pinky = 50;
    const int aus_wrist = 0;

    int limit100(int input);
    int relToAbs(int min, int max, int rel);

  public:
    Roboterhand();
    void servoupdate();
    void printStatus();
    void servodetach();
    void servoattach();
    void setAll(int vals[], bool detach);
    void setThumb(int val, bool detach);
    void setIndex(int val, bool detach);
    void setMajeure(int val, bool detach);
    void setRingfinger(int val, bool detach);
    void setPinky(int val, bool detach);
    void setWrist(int val, bool detach);
    void smoothMovement(void (Roboterhand::*set)(int, bool), int mybegin, int myend, int mydelay);
    void setLEDColor(int r, int g, int b);
    void setLEDFadeTime(int fadeUpTime, int fadeDownTime);
    void refresh();
};
