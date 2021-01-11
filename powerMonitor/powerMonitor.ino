#include "secret.h" 
#include "Mqtt.h" 
#include "power.h"



#define HOSTNAME "ESP-PowerMonitor-OTA"
    
Mqtt m_mqtt;
Power m_power;

void setup(){ 
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  
  Connection::connectWifi(HOSTNAME);
}   

 


void printMeasure( float valueA,float valueW )
{
 Serial.print("Irms: ");
 Serial.print(valueA, 3);
 Serial.print(" A");
 Serial.print("Potencia: ");
 Serial.print(valueW, 3);
 Serial.println(" W");
}

void publishPower(){     
    //Mido el sensor de consumo total
    float currentRMS ;
    float currentRMS2;
    
    m_power.getCorrienteSensores(&currentRMS,&currentRMS2);
    
    float power = 230.0 * currentRMS;   
    float power2 = 230.0 * currentRMS2;   
     
    printMeasure(currentRMS,  power);
    printMeasure(currentRMS2,  power2);
    
    m_mqtt.publish(TOPIC_POWER_TOTAL_A, currentRMS);
    m_mqtt.publish(TOPIC_POWER_TOTAL_W, power); 
    
    
    m_mqtt.publish(TOPIC_POWER_CLIMA_A, currentRMS2);
    m_mqtt.publish(TOPIC_POWER_CLIMA_W, power2);
    
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
    

  }else if (millis() % 400 == 0){//Serial.println("Cada 400ms");
    
  }
  
  ArduinoOTA.handle();
  publishPower();    
  m_mqtt.handleMQTT();
  
}
