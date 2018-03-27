/** MANU - robotic hand 
 *  Code for Arduino Nano (connected to ESP8266)
 *  Video on Youtube: https://youtu.be/UN8Itcejvu4
 *  
 *  created 27 March 2018
 *  by techniccontroller
 */
 
#include <Servo.h>
#include <SoftPWM.h>

// Definition of Pins for different fingers and LEDs
#define THUMB 4
#define INDEX 2
#define MAJEURE 3
#define RINGFINGER 6
#define PINKY 5
#define WRIST 7
#define LED_BLUE A0
#define LED_RED A1
#define LED_GREEN A2

// class for the robotic hand (German: Roboterhand == robotic hand)
class Roboterhand{
  private:
    Servo servothumb;
    Servo servoindex;
    Servo servomajeure;
    Servo servoringfinger;
    Servo servopinky;
    Servo servowrist;

    // maximum values for finger in opened position (German ein == in)
    const int ein_thumb = 155;
    const int ein_index = 165;
    const int ein_majeure = 180;
    const int ein_ringfinger = 170;
    const int ein_pinky = 150;
    const int ein_wrist = 180;
    
    // minimum values for fingers in closed position (German aus == out)
    const int aus_thumb = 40;
    const int aus_index = 50;
    const int aus_majeure = 55;
    const int aus_ringfinger = 50;
    const int aus_pinky = 60;
    const int aus_wrist = 0;
    
    // initial values for fingers
    int val_thumb = aus_thumb;
    int val_index = aus_index;
    int val_majeure = aus_majeure;
    int val_ringfinger = aus_ringfinger;
    int val_pinky = aus_pinky;
    int val_wrist = aus_wrist;
    
    // saturation function (limits values to 0-100)
    int limit100(int input);
    
    // calculate relative positions (0-100) to actual servo positions
    int relToAbs(int min, int max, int rel);
    
    // initial values for LEDs
    int val_red = 0;
    int val_green = 0;
    int val_blue = 0;

  public:
    Roboterhand();
    // updates all servos with there new positions values
    void servoupdate();
    
    // debug function: prints all current finger/servo positions
    void printStatus();
    
    // attach/detach all servos
    void servodetach();
    void servoattach();
    
    // set all finger positons at on time vals=[thumb,index,middle,ring,pinky,wrist]
    // (values between 0 and 100 [%])
    // detach: will update the servos directly
    void setAll(int vals[], bool detach);
    
    // set single finger positions (values between 0 and 100 [%])
    // detach: will update the servos directly
    void setThumb(int val, bool detach);
    void setIndex(int val, bool detach);
    void setMajeure(int val, bool detach);
    void setRingfinger(int val, bool detach);
    void setPinky(int val, bool detach);
    void setWrist(int val, bool detach);
    
    // create a smooth Movement for single finger
    void smoothMovement(void (Roboterhand::*set)(int, bool), int mybegin, int myend, int mydelay);
    
    // set color of LEDs
    void setLEDColor(int r, int g, int b);
    
    // set Fadetime of LEDs (see SoftPWM.h)
    void setLEDFadeTime(int fadeUpTime, int fadeDownTime);
    
    // attach & update & detach all servos
    void refresh();
};
