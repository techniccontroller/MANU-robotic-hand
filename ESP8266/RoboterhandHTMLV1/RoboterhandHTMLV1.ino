#include <ESP8266WiFi.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//---------------------------------------------------------------------
// WiFi

byte my_WiFi_Mode = 2;  // WIFI_STA = 1 = Workstation  WIFI_AP = 2  = Accesspoint

const char * ssid_ap = "ESP_HTML_01";
const char * password_ap = "123456";

WiFiServer server(80);
WiFiClient client;

#define MAX_PACKAGE_SIZE 2048
char HTML_String[5000];
char HTTP_Header[150];
char* namenFinger[] = {"Daumen", "Zeigefinger", "Mittelfinger", "Ringfinger", "Kleiner Finger"};

#define ACTION_EIN 0
#define ACTION_AUS 1
int action;

void setup() {
  Serial.begin(9600);
  // Accesspoint WiFi starten
  WiFi_Start_AP();
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
  //---------------------------------------------------------------------
  htmlPtr = 0;
  my_char = 0;
  while (client.available() && my_char != '\r') {
    my_char = client.read();
    HTML_String[htmlPtr++] = my_char;
  }
  client.flush();
  HTML_String[htmlPtr] = 0;


  if (Find_Start ("/?", HTML_String) < 0 && Find_Start ("GET / HTTP", HTML_String) < 0 ) {
    send_not_found();
    return;
  }

  //---------------------------------------------------------------------
  // Benutzereingaben einlesen und verarbeiten
  //---------------------------------------------------------------------
  action = Pick_Parameter_Zahl("ACTION=", HTML_String);
  Serial.write(action);

  //---------------------------------------------------------------------
  //Antwortseite aufbauen

  make_HTML();

  //---------------------------------------------------------------------
  // Header aufbauen
  strcpy(HTTP_Header , "HTTP/1.1 200 OK\r\n");
  strcat(HTTP_Header, "Content-Length: ");
  strcati(HTTP_Header, strlen(HTML_String));
  strcat(HTTP_Header, "\r\n");
  strcat(HTTP_Header, "Content-Type: text/html\r\n");
  strcat(HTTP_Header, "Connection: close\r\n");
  strcat(HTTP_Header, "\r\n");
  client.print(HTTP_Header);
  delay(20);
  send_HTML();
}

void WiFi_Start_AP() {
  WiFi.mode(WIFI_AP);   // Accesspoint
  WiFi.softAP(ssid_ap, password_ap);
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  my_WiFi_Mode = WIFI_AP;

  // IP-Adresse: 192.168.4.1
}

void make_HTML() {

  strcpy( HTML_String, "<!DOCTYPE html>");
  strcat( HTML_String, "<html>");
  strcat( HTML_String, "<head>");
  strcat( HTML_String, "<title>HTML Demo</title>");
  strcat( HTML_String, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">");
  
  strcat( HTML_String, "<style>");
  strcat( HTML_String, "button {"
                          "background-color: #990033;"
                          "border: none;"
                          "color: white;"
                          "padding: 7px 15px;"
                          "text-align: center;"
                          "cursor: pointer;"
                        "}");
  strcat( HTML_String, "</style>");
  strcat( HTML_String, "</head>");
  strcat( HTML_String, "<body bgcolor=\"#adcede\">");
  strcat( HTML_String, "<font color=\"#000000\" face=\"VERDANA,ARIAL,HELVETICA\">");
  strcat( HTML_String, "<h1>Roboterhand MANU</h1>");


  strcat( HTML_String, "<form>");
  strcat( HTML_String, "<table>");
  for(int i = 0; i < 5; i++){
    strcat( HTML_String, "<tr>");
    strcat( HTML_String, "<td>");
    strcat( HTML_String, namenFinger[i]);
    strcat( HTML_String, "</td>");
    strcat( HTML_String, "<td>");
    strcat( HTML_String, "<button style= \"width:120px\" name=\"ACTION\" value=\"");
    strcati(HTML_String, (i*2)+ACTION_EIN);
    strcat( HTML_String, "\">EIN</button>");
    strcat( HTML_String, "</td>");
    strcat( HTML_String, "<td>");
    strcat( HTML_String, "<button style= \"width:120px\" name=\"ACTION\" value=\"");
    strcati(HTML_String, (i*2)+ACTION_AUS);
    strcat( HTML_String, "\">AUS</button>");
    strcat( HTML_String, "</td>");
    strcat( HTML_String, "</tr>");
  }
  strcat( HTML_String, "</table>");
  strcat( HTML_String, "</form>");
  strcat( HTML_String, "<br>");
  strcat( HTML_String, "</font>");
  strcat( HTML_String, "</body>");
  strcat( HTML_String, "</html>");
}
//--------------------------------------------------------------------------
void send_HTML() {
  char my_char;
  int  my_len = strlen(HTML_String);
  int  my_ptr = 0;
  int  my_send = 0;

  //--------------------------------------------------------------------------
  // in Portionen senden
  while ((my_len - my_send) > 0) {
    my_send = my_ptr + MAX_PACKAGE_SIZE;
    if (my_send > my_len) {
      client.print(&HTML_String[my_ptr]);
      delay(20);
      my_send = my_len;
    } else {
      my_char = HTML_String[my_send];
      // Auf Anfang eines Tags positionieren
      while ( my_char != '<') my_char = HTML_String[--my_send];
      HTML_String[my_send] = 0;
      client.print(&HTML_String[my_ptr]);
      delay(20);
      HTML_String[my_send] =  my_char;
      my_ptr = my_send;
    }
  }
  client.stop();
}
//---------------------------------------------------------------------
void strcati(char* tx, int i) {
  char tmp[8];

  itoa(i, tmp, 10);
  strcat (tx, tmp);
}
//---------------------------------------------------------------------
void strcati2(char* tx, int i) {
  char tmp[8];

  itoa(i, tmp, 10);
  if (strlen(tmp) < 2) strcat (tx, "0");
  strcat (tx, tmp);
}
//---------------------------------------------------------------------
void send_not_found() {
  // Sende Not Found
  client.print("HTTP/1.1 404 Not Found\r\n\r\n");
  delay(20);
  client.stop();
}
//---------------------------------------------------------------------
int Pick_Parameter_Zahl(const char * par, char * str) {
  int myIdx = Find_End(par, str);
  
  if (myIdx >= 0) return  Pick_Dec(str, myIdx);
  else return -1;
}
//---------------------------------------------------------------------
int Find_End(const char * such, const char * str) {
  int tmp = Find_Start(such, str);
  if (tmp >= 0)tmp += strlen(such);
  return tmp;
}
//---------------------------------------------------------------------
int Find_Start(const char * such, const char * str) {
  int tmp = -1;
  int ww = strlen(str) - strlen(such);
  int ll = strlen(such);

  for (int i = 0; i <= ww && tmp == -1; i++) {
    if (strncmp(such, &str[i], ll) == 0) tmp = i;
  }
  return tmp;
}
//---------------------------------------------------------------------
int Pick_Dec(const char * tx, int idx ) {
  int tmp = 0;
  
  for (int p = idx; p < idx + 5 && (tx[p] >= '0' && tx[p] <= '9') ; p++) {
    tmp = 10 * tmp + tx[p] - '0';
  }
  return tmp;
}
//----------------------------------------------------------------------------
int Pick_N_Zahl(const char * tx, char separator, byte n) {

  int ll = strlen(tx);
  int tmp = -1;
  byte anz = 1;
  byte i = 0;
  while (i < ll && anz < n) {
    if (tx[i] == separator)anz++;
    i++;
  }
  if (i < ll) return Pick_Dec(tx, i);
  else return -1;
}
//---------------------------------------------------------------------
int Pick_Hex(const char * tx, int idx ) {
  int tmp = 0;

  for (int p = idx; p < idx + 5 && ( (tx[p] >= '0' && tx[p] <= '9') || (tx[p] >= 'A' && tx[p] <= 'F')) ; p++) {
    if (tx[p] <= '9')tmp = 16 * tmp + tx[p] - '0';
    else tmp = 16 * tmp + tx[p] - 55;
  }

  return tmp;
}
//---------------------------------------------------------------------
void Pick_Text(char * tx_ziel, char  * tx_quelle, int max_ziel) {

  int p_ziel = 0;
  int p_quelle = 0;
  int len_quelle = strlen(tx_quelle);

  while (p_ziel < max_ziel && p_quelle < len_quelle && tx_quelle[p_quelle] && tx_quelle[p_quelle] != ' ' && tx_quelle[p_quelle] !=  '&') {
    if (tx_quelle[p_quelle] == '%') {
      tx_ziel[p_ziel] = (HexChar_to_NumChar( tx_quelle[p_quelle + 1]) << 4) + HexChar_to_NumChar(tx_quelle[p_quelle + 2]);
      p_quelle += 2;
    } else if (tx_quelle[p_quelle] == '+') {
      tx_ziel[p_ziel] = ' ';
    }
    else {
      tx_ziel[p_ziel] = tx_quelle[p_quelle];
    }
    p_ziel++;
    p_quelle++;
  }

  tx_ziel[p_ziel] = 0;
}
//---------------------------------------------------------------------
char HexChar_to_NumChar( char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 55;
  return 0;
}
