#include <EEPROM.h>
#include "GravityTDS.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(22,21,5,18,23,19);

#define TdsSensorPin 32
GravityTDS gravityTds;

float temperature = 25,tdsValue = 0;
 
void setup()
{
    Serial.begin(115200);
    lcd.begin(16,2);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(3.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}
 
void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    lcd.setCursor(0, 0);
    lcd.print("TDS Value:");
    lcd.setCursor(0, 1);
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
    delay(1000);
    lcd.clear();
}
