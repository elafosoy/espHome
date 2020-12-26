#ifndef CONNECTION_H
#define CONNECTION_H


class Connection {

  private:
  uint8_t m_attemptsConnect;
  bool m_connected = false;

    void setAP(){

      char *sid = AppDef::getApSid();
      char *pass = AppDef::getWifiPass();

      if (sid != "" && pass != ""){
        WiFi.softAP(sid,pass);
        IPAddress myIP = WiFi.softAPIP();
  
        Serial.print("AP IP address: ");
        Serial.println(myIP);
      }else{
        AppDef::saveDataDefault();
      }

    }

    void setClient(){
      WiFi.mode(WIFI_STA);
      IPAddress myIP = WiFi.softAPIP();

      Serial.print("AP IP address: ");
      Serial.println(myIP);
    }


  public:
    Connection(){ 
 
    }

    void handleConnection(){
    }

    void scanAndConnect(){
      int n = WiFi.scanNetworks();
        if (n == 0){
          Serial.println("No hay conexiones disponibles");
        }else{
          Serial.print(n);
          Serial.println(" networks found");
          for (int i = 0; i < n; ++i){
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
          }
        }
    }

    bool startConnect(){  
      Serial.println("Connectando...");
      WiFi.begin(AppDef::getClientSid(), AppDef::getWifiPass());
        if (WiFi.waitForConnectResult() != WL_CONNECTED){ 
            Serial.println("Connection Failed!  -->");
            Serial.println( AppDef::getClientSid() );
            Serial.println( AppDef::getWifiPass());
            m_connected = false;
            
            if (m_attemptsConnect == 2){
              m_attemptsConnect = 0;
              Serial.println("Ha la espera para configurar una nueva wifi");
              setServerToReconfigureWifi();
            }else{
              Serial.print(".");
              m_attemptsConnect++;
              delay(50); 
              startConnect();
            }
         }else{ 
            Serial.println("*==========  Conectado  =========*");
            Serial.print("     Sid :");
            Serial.println(WiFi.SSID() );
            Serial.print("     Ip: ");
            Serial.println(WiFi.localIP());
            Serial.println("*================================*");
            m_connected = true;
            WiFi.mode(WIFI_STA);
            WiFi.begin();

         }
       return m_connected;
    }

    bool isConnected(){
      if (WiFi.status() != WL_CONNECTED)
        m_connected = false;
      else
        m_connected = true;

      return m_connected;
    }

    String getSid(){
      return WiFi.SSID();
    }

    IPAddress getIp(){
      return WiFi.localIP();
    }

    void setServerToReconfigureWifi(){
      setAP();
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
    }



};

#endif
