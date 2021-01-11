#ifndef CONNECTION_H
#define CONNECTION_H
#include "secret.h"   
#include "ota.h"  

class Connection { 
  public:
    Connection(){ 
      
    } 

    static void setHostName(const char *hostname){ 
      wifi_station_set_hostname(hostname);
    }

     static void connectWifi(const char *hostname=""){  
      wifi_station_set_hostname(hostname);
                
      if (WiFi.status() != WL_CONNECTED){
        Connection::WiFiOn();        
        while (WiFi.status() != WL_CONNECTED) { 
          delay(500); 
        }    
        Serial.println("Wifi connected OK");

          Serial.println("IP address: ");
          Serial.println(WiFi.localIP());
      }else{
        Serial.println("Wifi OK");
      }

      Ota::init(hostname);
    }

    
    static void WiFiOff() {
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.forceSleepBegin();
    }
    
    static void WiFiOn() {
      WiFi.forceSleepWake();
      WiFi.mode(WIFI_STA);
      wifi_station_connect();
      WiFi.begin (WIFI_NAME, WIFI_PASSWORD);
    }


};

#endif
