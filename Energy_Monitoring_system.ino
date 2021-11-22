#include<LiquidCrystal.h> //lcd library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //assigning lcd pins (RS,En,D4,D5,D6,D7)

//#include <SoftwareSerial.h>//ESP library
//#include <ArduinoJson.h> //arduino to NodeMCU library
//SoftwareSerial nodemcu(8, 9);//8=TX & 9=RX on nodeMCU


#include "DHT.h" //library DHT11
#define dht_1 6     //pin 6 to dht11
#define DHTTYPE DHT11
DHT dht(dht_1, DHTTYPE);

double kilos = 0; //Declare energy usage
int peakPower = 0; //Declare RMS power


void setup() {
  Serial.begin(9600);
  //  nodemcu.begin(9600);
  dht.begin();
  lcd.begin(20, 4); //set lcl (row,column)
  delay(500);
}


void loop() {

  delay(2000);
  //  StaticJsonBuffer<1000> jsonBuffer;
  //  JsonObject& data = jsonBuffer.createObject();

  //Read DHT11
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  int InputVoltage  = analogRead(A1); // Read the analog  value
  double voltage = InputVoltage * (5.0 / 1024.0) ; //convert the value to volts

  int current = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;
  for (int i = 0 ; i <= 200 ; i++) //Monitors and logs the current input for 200 cycles to determine max and min current
  {
    current = analogRead(A1);    //Reads current input
    if (current >= maxCurrent)
      maxCurrent = current;
    else if (current <= minCurrent)
      minCurrent = current;
  }
  if (maxCurrent <= 517)
  {
    maxCurrent = 516;
  }
  double RMSCurrent = ((maxCurrent - 516) * 0.707) / 11.8337; //Calculates RMS current based on maximum value
  int RMSPower = 220 * RMSCurrent;  //Calculates RMS Power Voltage 220VAC
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
  kilos = kilos + (RMSPower * (2.05 / 60 / 60 / 100)); //Calculate kilowatt hours used



  //Serial monitor display
  Serial.println("====================== ");
  Serial.print("humidity= ");
  Serial.println(humid);
  Serial.print("temperature= ");
  Serial.println(temp);
  Serial.println("====================== ");


  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");


  Serial.print("Current: ");
  Serial.print(RMSCurrent);
  Serial.println(" A");

  Serial.print("Power: ");
  Serial.print(RMSPower);
  Serial.println(" W");

  Serial.print("Energy Usage: ");
  Serial.print(kilos);
  Serial.println(" kWh");
  Serial.println("====================== ");


  //LCD display
  lcd.setCursor(0, 0); //display on lcd at x=0, y-=0
  lcd.print("T= "); //display on lcd
  lcd.print(temp);

  lcd.setCursor(9, 0); //display on lcd at x=9, y-=0
  lcd.print("H= "); //display on lcd
  lcd.print(humid);

  lcd.setCursor(0, 1); //display on lcd at x=0, y-=0
  lcd.print("V= "); //display on lcd
  lcd.print(voltage);

  lcd.setCursor(9, 1); //display on lcd at x=0, y-=0
  lcd.print("A= "); //display on lcd
  lcd.print(RMSCurrent);

  lcd.setCursor(0, 2); //display on lcd at x=0, y-=3
  lcd.print("Power= "); //display on lcd
  lcd.print(RMSPower);
  lcd.print(" W");

  lcd.setCursor(0, 3); //display on lcd at x=0, y-=4
  lcd.print("EnergyUsed= "); //display on lcd
  lcd.print(kilos);
  lcd.print(" kWh");

  //Assign collected data to JSON Object
  //  data["Humidity"] = humid;
  //  data["Temperature"] = temp;
  //  data["Voltage"] = voltage;
  //  data["Current"] = RMSCurrent;
  //  data["Power"] = RMSPower;
  //  data["Energy_Usage"] = kilos;
  //
  //  //Send data to NodeMCU
  //  data.printTo(nodemcu);
  //  jsonBuffer.clear();

}
