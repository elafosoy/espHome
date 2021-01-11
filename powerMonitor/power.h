#ifndef POWER_H
#define POWER_H 
/*
 https://www.luisllamas.es/arduino-sensor-corriente-sct-013/
*/
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define NUM_MUESTRAS 3000

class Power {

Adafruit_ADS1115 ads; 
const float FACTOR = 50; //50A/1V 
const float MULTIPLIER = 0.0625F;

public: 
 Power(){
    ads.setGain(GAIN_TWO);        // ±2.048V  1 bit = 0.0625mV
    ads.begin();
 }

  void getCorrienteSensores(float *sens1, float *sens2)
  {
   float voltage;
   float voltage1; 
   float corriente;
   float corriente1;
   float sum = 0;
   float sum1 = 0;
   int counter = 0;
   
   while (counter < NUM_MUESTRAS)
   {
     voltage = ads.readADC_Differential_0_1() * MULTIPLIER;   
     voltage1 = ads.readADC_Differential_2_3() * MULTIPLIER;  
     
     corriente = voltage * FACTOR;
     corriente /= 1000.0;

     corriente1 = voltage1 * FACTOR;
     corriente1 /= 1000.0;
   
     sum += sq(corriente);
     sum1 += sq(corriente1);
     counter = counter + 1;

     ArduinoOTA.handle();
    }
   
   *sens1 = sqrt(sum / NUM_MUESTRAS);
   *sens2 = sqrt(sum1 / NUM_MUESTRAS);
   
  }

  float getCorrienteSensor1()
  {
   float voltage; 
   float corriente;
   float sum = 0;
   int counter = 0;
   
   while (counter < NUM_MUESTRAS)
   {
     voltage = ads.readADC_Differential_0_1() * MULTIPLIER;   
   
     corriente = voltage * FACTOR;
     corriente /= 1000.0;
   
     sum += sq(corriente);
     counter = counter + 1;
    }
   
   corriente = sqrt(sum / NUM_MUESTRAS);
   return(corriente);
  }

  float getCorrienteSensor2()
  {
   float voltage; 
   float corriente;
   float sum = 0;
   int counter = 0;
   
   while (counter < NUM_MUESTRAS)
   {
     voltage = ads.readADC_Differential_2_3() * MULTIPLIER;   
   
     corriente = voltage * FACTOR;
     corriente /= 1000.0;
   
     sum += sq(corriente);
     counter = counter + 1;
    }
   
   corriente = sqrt(sum / NUM_MUESTRAS);
   return(corriente);
  }
};

#endif
