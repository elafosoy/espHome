#include "secret.h"
#include "PantallaMatrix.h"
#include "Mqtt.h"
#include "Temperature.h" 
   
PantallaMatrix m_pantalla; 
Temperature m_temperature;
Mqtt m_mqtt;

void setup(){ 
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   
}

void showTemp(){  
  char* temp = m_temperature.getTemp();
  m_pantalla.write(temp);    
}

void showHumidity(){
  char* humi = m_temperature.getHumidity();
  m_pantalla.write(humi); 
}

void publishTemperature(){
    float humidity = m_temperature.humidity();
    float temperature = m_temperature.temperature();
    String topicTemp = TOPIC_TEMP; 
    String topicHumidity = TOPIC_HUMIDITY; 
    
    m_mqtt.publish(topicTemp, temperature);
    m_mqtt.publish(topicHumidity, humidity); 
}


void loop(){ 
 
  if ( millis() > 86400000){
      ESP.restart();
  }else if (millis() % 1800000 == 0){
  }else if (millis() % 900000 == 0){//Serial.println("Cada 15m"); 
    publishTemperature();
  }else if (millis() % 300000 == 0){//Serial.println("Cada 5m");
    
  } else if (millis() % 60000 == 0){//Serial.println("Cada 1m");
     publishTemperature();
     m_mqtt.subscribe(SUBSRICBE_PANTALLA);
  } else if (millis() % 10000 == 0){//Serial.println("Cada 10s");
    showHumidity();
  } else if (millis() % 5000 == 0){//Serial.println("Cada 5s"); 
    showTemp();         
  } else if (millis() % 1000 == 0){//Serial.println("Cada 1s");
     m_pantalla.scrollBar();
     
  }else if (millis() % 400 == 0){//Serial.println("Cada 400ms");
    
  }
  m_mqtt.handleMQTT();
}
