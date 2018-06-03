#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);
const int DELAY = 3000;
String response;

void setup() {
  Serial.begin(9600);
  delay(1000);
  esp.begin(9600);
  delay(1000);

  Serial.println("Started");

  do {
    esp.println("AT+CWMODE=1");
    response = getResponse();
  }while(response != "no change");

  do{
    esp.println("AT+CWJAP=\"integer9711\",\"ChinFamilyUnifi227!\"");
    response=getResponse();
  }while (response == "ERROR");

  do{
    esp.println("AT+CIFSR");
    response=getResponse();
  }while(response != "OK");
}

void loop() {
  sendMessage();
  delay(8000);
}

void sendMessage(){
  do {
    esp.println("AT+RST");
    response = getResponse();
  }while(response != "OK");

  do {
    esp.println("AT+CIPSTART=\"TCP\",\"192.168.1.3\",3000");
    response = getResponse();
  }while(response == "no ip");

  String getStr="GET / HTTP/1.1\r\n\r\n";
  //esp.println("AT+CIPSEND=" + String(getStr.length()));
  do{
    esp.println("AT+CIPSEND=18");
    response = getResponse();
  }while(response != ">");

  
  esp.print(getStr);
  do {
    response = getResponse();
  }while(response == "busy");
   
  esp.flush();
  response = getResponse();

 
  esp.println("AT+CIPCLOSE");
  response = getResponse();
}

String getResponse(){
  delay(DELAY);
  if (esp.available()) {
    String tmp = esp.readStringUntil("\n");
    Serial.println(tmp);
    if(tmp.indexOf("OK") > 0) {
      Serial.println("----OK----");
      return "OK";
    }else if (tmp.indexOf("no change") > 0){
      Serial.println("----no change----");
      return "no change";
    }else if (tmp.indexOf("SEND OK") > 0) {
      Serial.println("----SEND OK----");
      return "SEND OK";
    }else if (tmp.indexOf(">") > 0 ) {
      Serial.println("---- > ----");
      return ">";
    }else if (tmp.indexOf("busy") > 0 ) {
      Serial.println("---- busy ----");
      return "busy";
    }else if (tmp.indexOf("ERROR") > 0) {
      return "ERROR";
    }else if (tmp.indexOf("no ip") > 0) {
      return "no ip";
    }
  }
  delay(DELAY);
}

