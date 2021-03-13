/* ------------------------------------------------- */

// TODO: add timestamp
// TODO: add pipe operator >
// TODO: ip & mac addr. an die event handler übergeben

/* ------------------------------------------------- */

#pragma once

#ifndef ESPTelnet_h
#define ESPTelnet_h

/* ------------------------------------------------- */

#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
#else if defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#endif

/* ------------------------------------------------- */

class ESPTelnet {
  typedef void (*CallbackFunction) (String ip);

  public:
    ESPTelnet();

    bool begin();
    void loop();
    void stop();

    void print(String str);
    void print(char c);
    void println(String str);
    void println(char c);
    void println();

//    void attachToSerial();
//    void removeFromSerial(bool dumpRemain /* = true */);

    String getIP() const;
    String getLastAttemptIP() const;
    
    void onConnect(CallbackFunction f);
    void onConnectionAttempt(CallbackFunction f);
    void onReconnect(CallbackFunction f);
    void onDisconnect(CallbackFunction f);
    void onInputReceived(CallbackFunction f);
    
  protected:
    WiFiServer server = WiFiServer(23);
    WiFiClient client;
    String ip;
    String attemptIp;
    boolean isConnected = false;
    String input = "";
//    bool serial_attached = false;

    CallbackFunction on_connect = NULL;
    CallbackFunction on_reconnect  = NULL;
    CallbackFunction on_disconnect = NULL;
    CallbackFunction on_connection_attempt = NULL;
    CallbackFunction on_input  = NULL;
};

/* ------------------------------------------------- */

  // << operator
  template<class T> inline ESPTelnet &operator <<(ESPTelnet &obj, T arg) { obj.print(arg); return obj; } 

/* ------------------------------------------------- */
#endif
/* ------------------------------------------------- */