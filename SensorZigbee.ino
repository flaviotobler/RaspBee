#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
int sensorValue;
int sensorValueOld;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup(){  lcd.begin(16, 2);
 Serial.begin(38400);// sets the serial port to 38400
 Serial.println("setup..");
 Serial.println("MCP9808 demo");

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
 }
void loop(){sensorValue = analogRead(0);       // read analog input pin 0
if (sensorValue != sensorValueOld)
{
  float c = tempsensor.readTempC();
  Serial.print("AirQua=");
  Serial.print(sensorValue, DEC);               // prints the value read
  Serial.println(" PPM");
  Serial.print("Temp: "); Serial.print(c); Serial.println("*C\t"); 
  sensorValueOld = sensorValue;
}
else{Serial.println("");}

delay(4000);                                   // wait 600000ms for next reading
}
