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
       m_humidity = dht.getHumidity();
       m_temperature = dht.getTemperature();
    }  
  }

};

#endif
