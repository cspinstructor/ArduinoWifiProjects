#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);
const int DELAY = 3000;

void setup() {
  Serial.begin(9600);
  delay(1000);
  esp.begin(9600);
  delay(1000);

  Serial.println("Started");
  
  esp.println("AT+CWMODE=1");
  getResponse();

  esp.println("AT+CWJAP=\"integer9711\",\"ChinFamilyUnifi227!\"");
  getResponse();

  esp.println("AT+CIFSR");
  getResponse();
}

void loop() {
  sendMessage();
  delay(8000);
}

void sendMessage(){
  esp.println("AT+RST");
  getResponse();

  esp.println("AT+CIPSTART=\"TCP\",\"192.168.1.3\",3000");
  getResponse();
  
  String getStr="GET / HTTP/1.1\r\n\r\n";
  //esp.println("AT+CIPSEND=" + String(getStr.length()));
  esp.println("AT+CIPSEND=20");
  getResponse();

  esp.print(getStr);
  getResponse();
  esp.flush();
  getResponse();
 
}

void getResponse(){
  delay(DELAY);
  if (esp.available()) {
    Serial.println( esp.readStringUntil("\n") );
  }
  delay(DELAY);
}

