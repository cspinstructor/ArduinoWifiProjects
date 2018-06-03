void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  String url="This is a very longOKs string";
  boolean ok = url.indexOf("OK") > 0;
  //Serial.println(ok);
  String a = "apples";
  String b = "ball";
  String c = "apples";
  Serial.println ( strcmp(a,b) );
  Serial.println ( strcmp(a,c) );
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
