
//This code is Written by Abhinav verma.
//contact @ abhikumar134@gmail.com
//This software is only for education purpose for Students, hobbyist.
// don't use for commercial.
// here we are controlling on board led using web api integration of 
// thingspeak.com using internet.
//
//
#include <SoftwareSerial.h>
#include <stdlib.h>
// change esp8266 default bude rate to 57600 bps before loading this software
// LED 
int ledPin = 13;
// replace with your channel's thingspeak API key
String apiKey = "your api key";
String ssid="your wifi ssid";
String pswd="your wifi password";
String wifi;
// connect 10 to TX of Serial USB
// connect 11 to RX of serial USB
SoftwareSerial ser(3, 2); // RX, TX using software serial for esp8266

// this runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);    

  // enable debug serial
  Serial.begin(115200); 
  // enable software serial
  ser.begin(57600);
  
  wifi="AT+CWJAP_DEF=";
  wifi+='"';
  wifi+=ssid;
  wifi+='"';
  wifi+=',';
  wifi+='"';
  wifi+=pswd;
  wifi+='"';
  wifi+="\r\n";
  ser.println(wifi);
  delay(2000);
  // reset ESP8266
  ser.println("AT+RST\r\n");
  delay(5000);
}


// the loop 
void loop() {
    int i=0;
    char c[100]; // returned data storage
  
   // TCP connection to thingspeak.com api server;
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "api.thingspeak.com"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  if(ser.find("ERROR")){
    Serial.println("AT+CIPSTART error");
    ser.println("AT+CIPCLOSE\r\n");
    ser.println(cmd);
    return;
  }
  else if(ser.find("OK"))
  {
    Serial.println("connected to Thing speak API");
  }
  else if(ser.find("ALREA"))
  {
    Serial.println("Already connected");
  }
  
  // prepare GET string
  String getStr = "GET /channels/your channel/fields/1.json?results=1";
  getStr += "\r\n";


  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
 
  if(ser.find(">")){
    ser.print(getStr);
    delay(1000);
    if(ser.find("+IPD"))
    {
      Serial.println("+IPD found");
      while(ser.available())
      {
        if(ser.find("feeds"))
        { Serial.println("found feeds:");
          while(ser.available())  
         {
      c[i]=ser.read();
      i++;
         }
        }
      }
      if(c[i-13]=='H')
      {
      digitalWrite(ledPin,HIGH);
      }
      
      else if(c[i-13]=='L')
      {
        digitalWrite(ledPin,LOW);
      }
      Serial.println(i);
      Serial.println(c);
      c[i-13]='/0';
      ser.flush();
    }
    else
    {
      Serial.println("+IPD not found");
      ser.flush();
    }
  }
  else{
    ser.println("AT+CIPCLOSE\r\n");
    // alert user
    Serial.println("AT+CIPCLOSE");
    ser.flush();
  }
  delay(5000);
}
