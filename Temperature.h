#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "DHTesp.h" 

class Temperature{

  DHTesp dht;
  float m_humidity;
  float m_temperature;

  String m_status;

public:

  Temperature(){
    m_humidity = 0.0;
    m_temperature = 0.0;
    dht.setup(D4, DHTesp::DHT11);
  }

  Temperature(int pin){
    m_humidity = 0.0;
    m_temperature = 0.0;
    dht.setup(pin, DHTesp::DHT11);
  }

  ~Temperature(){
  } 

  char* getTemp(){
      read();
      char lcdBuffer[4] = {};
      sprintf(lcdBuffer, "T%d", (int)m_temperature);

      return lcdBuffer;
  }

    char* getHumidity(){
      read();
      char lcdBuffer[4] = {};
      sprintf(lcdBuffer, "H%d",  (int)m_humidity);

      return lcdBuffer;
  }
  
  float humidity(){
    read();
    return m_humidity;
  }
  float temperature(){
    read();
    return m_temperature;
  }

private:

  void read(){
    m_status = dht.getStatusString();

    if (m_status == "OK"){
      float mediaHum;
      float mediaTemp;
      int numMuestras = 100;
      
      for(int i=0;i<numMuestras;i++){ 
        mediaHum += dht.getHumidity();
        mediaTemp += dht.getTemperature(); 
        ArduinoOTA.handle();
      }

      m_humidity = mediaHum/numMuestras;
      m_temperature = mediaTemp/numMuestras;
    }  



    ArduinoOTA.handle();
  }

};

#endif
