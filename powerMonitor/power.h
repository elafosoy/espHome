#ifndef POWER_H
#define POWER_H 
/*
 https://www.luisllamas.es/arduino-sensor-corriente-sct-013/
*/
#include <Wire.h>
#include <Adafruit_ADS1015.h>

class Power {

Adafruit_ADS1115 ads; 
const float FACTOR = 50; //50A/1V 
const float MULTIPLIER = 0.0625F;

public: 
 Power(){
    ads.setGain(GAIN_TWO);        // ±2.048V  1 bit = 0.0625mV
    ads.begin();
 }

  float getCorrienteSensor1()
  {
   float voltage; 
   float corriente;
   float sum = 0;
   long tiempo = millis();
   int counter = 0;
   
   while (millis() - tiempo < 1000)
   {
     voltage = ads.readADC_Differential_0_1() * MULTIPLIER;   
   
     corriente = voltage * FACTOR;
     corriente /= 1000.0;
   
     sum += sq(corriente);
     counter = counter + 1;
    }
   
   corriente = sqrt(sum / counter);
   return(corriente);
  }

  float getCorrienteSensor2()
  {
   float voltage; 
   float corriente;
   float sum = 0;
   long tiempo = millis();
   int counter = 0;
   
   while (millis() - tiempo < 1000)
   {
     voltage = ads.readADC_Differential_2_3() * MULTIPLIER;   
   
     corriente = voltage * FACTOR;
     corriente /= 1000.0;
   
     sum += sq(corriente);
     counter = counter + 1;
    }
   
   corriente = sqrt(sum / counter);
   return(corriente);
  }
};

#endif
