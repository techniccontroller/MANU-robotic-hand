#include <ESP8266WiFi.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//---------------------------------------------------------------------
// WiFi

byte my_WiFi_Mode = 1;  // WIFI_STA = 1 = Workstation  WIFI_AP = 2  = Accesspoint

const char * ssid_sta     = "FB7390-H38";
const char * password_sta = "alfeld91236";

const char * ssid_ap = "ESP_HTML_01";
const char * password_ap = "123456";

WiFiServer server(8080);
WiFiClient client;

char* namenFinger[] = {"Daumen", "Zeigefinger", "Mittelfinger", "Ringfinger", "Kleiner Finger"};

#define ACTION_EIN 0
#define ACTION_AUS 1
int action;
char TCP_command[5000];

void setup() {
  Serial.begin(9600);
  if(my_WiFi_Mode == 2){
    // Accesspoint WiFi starten
    WiFi_Start_AP();
  }
  else{
    // Workstation WiFi starten
    WiFi_Start_STA();
  }

}

void WiFi_Start_STA() {
  unsigned long timeout;

  WiFi.mode(WIFI_STA);   //  Workstation

  WiFi.begin(ssid_sta, password_sta);
  timeout = millis() + 12000L;
  while (WiFi.status() != WL_CONNECTED && millis() < timeout) {
    delay(10);
  }

  if (WiFi.status() == WL_CONNECTED) {
    server.begin();
    my_WiFi_Mode = WIFI_STA;
    /*Serial.print("Connected IP - Address : ");
    for (int i = 0; i < 3; i++) {
      Serial.print( WiFi.localIP()[i]);
      Serial.print(".");
    }
    Serial.println(WiFi.localIP()[3]);*/
  } else {
    WiFi.mode(WIFI_OFF);
    //Serial.println("WLAN-Connection failed");
  }
}

void WiFi_Start_AP() {
  WiFi.mode(WIFI_AP);   // Accesspoint
  WiFi.softAP(ssid_ap, password_ap);
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  my_WiFi_Mode = WIFI_AP;

  // IP-Adresse: 192.168.4.1
}

void loop() {
  WiFI_Traffic();

}

void WiFI_Traffic() {

  char my_char;
  int htmlPtr = 0;
  unsigned long my_timeout;
  bool firsttime = false;

  // Check if a client has connected
  client = server.available();
  if (client)  {
    
    while (client.connected()){
      // Read the incoming TCP command
      htmlPtr = 0;
      my_char = 0;
      firsttime = false;
      while (client.available() && my_char != '\r') {
        my_char = client.read();
        TCP_command[htmlPtr++] = my_char;
        firsttime = true;
      }
      if(firsttime){
        // Transfer command to Arduino
        Serial.print(TCP_command);
        // Response to client
        client.print(TCP_command);
      }
    }
  }  
  //---------------------------------------------------------------------
}
