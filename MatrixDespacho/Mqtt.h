#ifndef MQTT_H
#define MQTT_H 
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "PantallaMatrix.h"

class Mqtt{

  WiFiClient m_espClient;
  PubSubClient *m_client;
  PantallaMatrix *m_pantalla; 

public:
    Mqtt(){
      m_pantalla = new PantallaMatrix();
      WiFi.mode(WIFI_STA);
      m_client = new PubSubClient(m_espClient); 
      m_client->setServer(MQTT_SERVER, MQTT_PORT);
      m_client->setCallback(callback); 
 
    }
    ~Mqtt(){
      delete m_pantalla;
      delete m_client;
      }

    void connectWifi(){        
      if (WiFi.status() != WL_CONNECTED){
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
      
        while (WiFi.status() != WL_CONNECTED) { 
          delay(500); 
        }    
        Serial.println("Wifi connected OK");

          Serial.println("IP address: ");
          Serial.println(WiFi.localIP());
      }else{
        Serial.println("Wifi OK");
      }
    }

    void handleMQTT(){
      m_client->loop();
    }

    void subscribe(const char* topic){
      reconnect();
      m_client->subscribe(topic);
    }

    void publish(String topic, String msg){
      reconnect();
      m_client->publish(topic.c_str(),msg.c_str());
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

      PantallaMatrix pantalla;
      pantalla.write(text,true);       
     }

  void reconnect() { 
    connectWifi();
    
    if (!m_client->connected()) {            
      int retrys = 0;
      // Loop until we're reconnected
      while (!m_client->connected() && retrys<2) {
        Serial.println("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "Wemos D1-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (m_client->connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) { 
              m_pantalla->write("MQTT"); 
              delay(800); 
              Serial.println("MQTT connection OK");
        } else { 
          // Wait 5 seconds before retrying
          Serial.println("MQTT KO Connect");
          delay(1000);
        }

        retrys++;
        m_pantalla->scrollBar();
      }
    } 
  }

};
#endif // MQTT_H
