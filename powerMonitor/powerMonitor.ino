#include "secret.h" 
#include "Mqtt.h" 
    
Mqtt m_mqtt;

void setup(){ 
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 
 
}   


void loop(){ 
 
  if ( millis() > 86400000){
      ESP.restart();
  }else if (millis() % 1800000 == 0){
  }else if (millis() % 900000 == 0){//Serial.println("Cada 15m"); 
 
  }else if (millis() % 300000 == 0){//Serial.println("Cada 5m");
    
  } else if (millis() % 60000 == 0){//Serial.println("Cada 1m");
 
  } else if (millis() % 10000 == 0){//Serial.println("Cada 10s");
 
  } else if (millis() % 5000 == 0){//Serial.println("Cada 5s"); 
         
  } else if (millis() % 1000 == 0){//Serial.println("Cada 1s");
 
     m_mqtt.handleMQTT();
  }else if (millis() % 400 == 0){//Serial.println("Cada 400ms");
    
  }

}
