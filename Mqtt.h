#ifndef MQTT_H
#define MQTT_H 
#include <PubSubClient.h>
#include <ESP8266WiFi.h> 
#include "Connection.h"

class Mqtt{

  WiFiClient m_espClient;
  PubSubClient *m_client; 

public:
    Mqtt(){ 
      m_client = new PubSubClient(m_espClient); 
      m_client->setServer(MQTT_SERVER, MQTT_PORT);
      m_client->setCallback(callback);  
    }
    
    ~Mqtt(){ 
      delete m_client;
      }

    void handleMQTT(){
      m_client->loop();
    }

    void subscribe(const char* topic){
      reconnect();
      m_client->subscribe(topic);
      //Connection::WiFiOff();
    }

    void publish(String topic, String msg){
      reconnect();
      m_client->publish(topic.c_str(),msg.c_str());
      //Connection::WiFiOff();
    }

    void publish(String topic, float val){
      String msg = String(val);
      //sprintf(msg, "%f", val);
      publish(topic,msg);
    }

    static void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");
      char text[length +1 ];
      memcpy(text, payload,length);
      Serial.println(text);  

         
     }

  void reconnect() { 
    Connection::connectWifi();
    
    if (!m_client->connected()) {            
      int retrys = 0;
      // Loop until we're reconnected
      while (!m_client->connected() && retrys<2) {
        Serial.println("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "Wemos D1-";
        clientId += String(random(0xffff), HEX);
        ArduinoOTA.handle();
        handleMQTT();
        
        // Attempt to connect
        if (m_client->connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) { 
              Serial.println("MQTT connection OK");
        } else { 
          // Wait 5 seconds before retrying
          Serial.println("MQTT KO Connect");
          delay(1000);
        }

        retrys++; 
      }
    } 
  }

};
#endif // MQTT_H
