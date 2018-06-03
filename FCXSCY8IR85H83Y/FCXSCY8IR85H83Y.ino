/* Code by Yavnik Sharma */
#include <ESP8266WiFi.h>


const char WiFiAPPSK[] = "password";// you can keep any password you want for connectiong to ESP module.

const int LED1 = 2;
const int LED2 = 0;

WiFiServer server(80);

void setup() 
{
  initHardware();
  setupWiFi();
  server.begin();
}

void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
if (req.indexOf("/?pin=OFF1"))
{
  digitalWrite(LED1, LOW);
}
else if (req.indexOf("/?pin=ON1"))
{
  digitalWrite(LED2, HIGH);
}
else if (req.indexOf("/?pin=OFF2"))
{
  digitalWrite(LED2, LOW);
}
else if (req.indexOf("/?pin=ON2"))
{
  digitalWrite(LED2, HIGH);
}
  client.flush();
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX);
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 WIFI";

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void initHardware()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
    pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
}

