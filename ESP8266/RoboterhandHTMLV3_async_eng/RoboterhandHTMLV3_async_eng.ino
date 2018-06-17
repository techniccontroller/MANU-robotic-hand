#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//---------------------------------------------------------------------
// WiFi
const char * ssid_ap = "ESP_MANU_HTML";
const char * password_ap = "roboterhandMANU";

ESP8266WebServer server(80);

void handle_led() {
  // get the value of request argument "nr"&"value" and convert it to an int
  int nr, value;
  nr = server.arg("nr").toInt();
  value = server.arg("value").toInt();
  Serial.print("led/");
  Serial.print(nr);
  Serial.print('/');
  Serial.print(value);
  Serial.print('/');
}

void handle_slider() {
  // get the value of request argument "nr"&"value" and convert it to an int
  int nr, value;
  nr = server.arg("nr").toInt();
  value = server.arg("value").toInt();
  Serial.print("slider/");
  Serial.print(nr);
  Serial.print('/');
  Serial.print(value);
  Serial.print('/');
}

void handle_finger() {
  // get the value of request argument "nr"&"value" and convert it to an int
  int nr, value;
  nr = server.arg("nr").toInt();
  value = server.arg("value").toInt();
  Serial.print("finger/");
  Serial.print(nr);
  Serial.print('/');
  Serial.print(value);
  Serial.print('/');
}



void setup() {
  Serial.begin(9600);
  // Accesspoint WiFi starten
  WiFi_Start_AP();

   if (!SPIFFS.begin())
  {
    // Serious problem
    //Serial.println("SPIFFS Mount failed");
  } else {
    //Serial.println("SPIFFS Mount succesfull");
  }
  server.on("/led", handle_led);
  server.on("/slider", handle_slider);
  server.on("/finger", handle_finger);
  server.serveStatic("/", SPIFFS, "/index.html");
  server.begin();
}

void WiFi_Start_AP() {
  WiFi.mode(WIFI_AP);   // Accesspoint
  WiFi.softAP(ssid_ap, password_ap);
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  // IP-Adresse: 192.168.4.1
}

void loop() {
  server.handleClient();
}
