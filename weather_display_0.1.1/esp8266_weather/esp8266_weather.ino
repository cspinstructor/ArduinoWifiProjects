/*
  
  Simple ESP8266 Weather Display
  
  Based on the source code from: http://www.seeedstudio.com/wiki/WiFi_Serial_Transceiver_Module
  
  For more information: 
    
    de: http://zeflo.com/2014/esp8266-wetteranzeige/
    en: http://zeflo.com/2014/esp8266-weather-display/
*/

#include <SoftwareSerial.h>


#define cs   10  // Pins for the display
#define dc   9
#define rst  8 


#include <SPI.h>

#define SSID "integer9711" // insert your SSID
#define PASS "ChinFamilyUnifi227!" // insert your password
#define LOCATIONID "2925533" // location id
#define DST_IP "192.168.1.3" //api.openweathermap.org
SoftwareSerial dbgSerial(2, 3); // RX, TX for debugging

   
void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);
  dbgSerial.begin(9600); // for debuging
  dbgSerial.println("Init");
 
  Serial.println("AT+RST"); // restet and test if module is redy
  delay(1000);
  if(Serial.find("ready")) {
    dbgSerial.println("WiFi - Module is ready");
    
  }else{
    dbgSerial.println("Module dosn't respond.");
   
    while(1);
  }
  delay(1000);
  // try to connect to wifi
  boolean connected=false;
  for(int i=0;i<5;i++){
    if(connectWiFi()){
      connected = true;
      
      break;
    }
  }
  if (!connected){
   
    while(1);
  }
  delay(5000);
  Serial.println("AT+CIPMUX=0"); // set to single connection mode
}
void loop()
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",3000";
  Serial.println(cmd);
  dbgSerial.println(cmd);
  if(Serial.find("Error")) return;
  cmd = "GET /";
  cmd += LOCATIONID;
  cmd += " HTTP/1.0\r\nHost: 192.168.1.3\r\n\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")){
    dbgSerial.print(">");
  }else{
    Serial.println("AT+CIPCLOSE");
    dbgSerial.println("connection timeout");
   
    delay(1000);
    return;
  }
  Serial.print(cmd);
  unsigned int i = 0; //timeout counter
  int n = 1; // char counter
  char json[100]="{";
  //while (!Serial.find("\"main\":{")){} // find the part we are interested in.
  while (i<60000) {
    if(Serial.available()) {
      char c = Serial.read();
      json[n]=c;
      if(c=='}') break;
      n++;
      i=0;
    }
    i++;
  }
  dbgSerial.println(json);
 
 
  delay(5000);
}
     
boolean connectWiFi()
{
  Serial.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  dbgSerial.println(cmd);
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("OK")){
    dbgSerial.println("OK, Connected to WiFi.");
    return true;
  }else{
    dbgSerial.println("Can not connect to the WiFi.");
    return false;
  }
}
