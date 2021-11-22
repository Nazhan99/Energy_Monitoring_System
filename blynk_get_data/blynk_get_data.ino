#define BLYNK_AUTH_TOKEN            "znHYkCo2-8omKYhTFxKrLsgWmMvtxih9"

#define BLYNK_PRINT SwSerial


#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

char auth[] = BLYNK_AUTH_TOKEN;
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  //SwSerial.print("V1 Slider value is: ");
  //SwSerial.println(pinValue);
//  digitalWrite(2,pinValue);
//  digitalWrite(3,pinValue);
}

void setup()
{
  // Debug console
  SwSerial.begin(115200);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop()
{
  Blynk.run();
}
