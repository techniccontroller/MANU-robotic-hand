/** MANU - robotic hand 
 *  Code for ESP8266 (connected to Arduino Nano)
 *  Video on Youtube: https://youtu.be/UN8Itcejvu4
 *  
 *  created 27 March 2018
 *  by techniccontroller
 */
 
#include <ESP8266WiFi.h>
#include "indexl.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

//---------------------------------------------------------------------
// WiFi
const char * ssid_ap = "ESP_MANU_HTML";
const char * password_ap = "robotichandMANU";

WiFiServer server(80);
WiFiClient client;

void setup() {
  // Serial connection to Arduino Nano
  Serial.begin(9600);
  // start Accesspoint WiFi
  WiFi_Start_AP();
}

void WiFi_Start_AP() {
  WiFi.mode(WIFI_AP);   // Accesspoint
  WiFi.softAP(ssid_ap, password_ap);
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  my_WiFi_Mode = WIFI_AP;
  // default IP: 192.168.4.1
}

void loop() {
  WiFI_Traffic();
}

void WiFI_Traffic() {

  char my_char;
  int htmlPtr = 0;
  unsigned long my_timeout;

  // Check if a client has connected
  client = server.available();
  if (!client)  {
    return;
  }

  my_timeout = millis() + 250L;
  while (!client.available() && (millis() < my_timeout) ) delay(10);
  delay(10);
  if (millis() > my_timeout)  {
    // Client Connection Timeout
    return;
  }
  // Read the first line of the request
  String command1 = client.readStringUntil('/');  //This stores the irrelevant portion of the URL
  String command = client.readStringUntil('/');   //This will parse the rest of the URL into valid inputs

  // Send command to Arduino depending on command from client --not the best solution, I know;)--
  if(command == "led"){
    int nr, value;
    nr = client.parseInt();
    if(client.read() == '/'){
      value = client.parseInt();
      Serial.print("led/");
      Serial.print(nr);
      Serial.print('/');
      Serial.print(value);
      Serial.print('/');
    }
  }
  else if(command == "slider"){
    int nr, value;
    nr = client.parseInt();
    if(client.read() == '/'){
      value = client.parseInt();
      Serial.print("slider/");
      Serial.print(nr);
      Serial.print('/');
      Serial.print(value);
      Serial.print('/');
    }
  }
  else if(command == "finger"){
    int nr, value;
    nr = client.parseInt();
    if(client.read() == '/'){
      value = client.parseInt();
      Serial.print("finger/");
      Serial.print(nr);
      Serial.print('/');
      Serial.print(value);
      Serial.print('/');
    }
  }
  else {  // Prepare the response, send html file back to client
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += file1;  
    client.flush();
    // Send the response to the client
    while(s.length()>2000){
      String dummy = s.substring(0,2000);
      client.print(dummy);
      s.replace(dummy," ");
    }
    client.print(s);
    delay(1);
  }
}
