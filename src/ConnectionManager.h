#pragma once
#include "ESPTelnet.h"
#include "config.h"
#include "callbackFuncions.h"

class ConnectionManager{
private:
    ESPTelnet telnet;
    IPAddress ip;
    void setupConnection();

    void onTelnetRecieved(String str);
    void onTelnetConnect(String ip);
    void onTelnetDisconnect(String ip);
    void onTelnetReconnect(String ip);
    void onTelnetConnectionAttempt(String ip);

public:


    bool connectToWiFi(const char* ssid, const char* password, int max_tries = 20, int pause = 500);

    ConnectionManager();

    void sendCommand(const char* command);

    void run();

    bool isConnected();

};