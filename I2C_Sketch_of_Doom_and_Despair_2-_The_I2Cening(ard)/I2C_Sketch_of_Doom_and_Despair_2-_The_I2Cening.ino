#include <Wire.h>
int i=0;
void setup(){
   Wire.begin(84);
   Wire.onRequest(requestEvent);
   Wire.onReceive(receiveEvent);
   Serial.begin(9600);
   Serial.println("Initialized");
}

void loop(){
  delay(100);
}

void requestEvent(){
  Serial.print("Sending ");
  Serial.println(i);
  Wire.write(i);
  i++;
}

void receiveEvent(int bytesReceived){
  Serial.print("Received ");
  while(Wire.available())
  {
    int c = Wire.read();
    Serial.println(c);
  }
}
