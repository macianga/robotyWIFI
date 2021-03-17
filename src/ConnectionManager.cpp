#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    this->setupConnection();
}


void ConnectionManager::setupConnection()
{
    telnet.onConnect(this->onTelnetConnect);
    telnet.onConnectionAttempt(this->onTelnetConnectionAttempt);
    telnet.onReconnect(this->onTelnetReconnect);
    telnet.onDisconnect(this->onTelnetDisconnect);
    telnet.onInputReceived(this->onTelnetRecieved);

    Serial.print("- Telnet: ");
    if (telnet.begin())
    {
        Serial.println("running");
    }
    else
    {
        Serial.println("error.");
        //errorMsg("Will reboot...");
    }
}

bool ConnectionManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

bool ConnectionManager::connectToWiFi(const char *ssid, const char *password, int max_tries = 20, int pause = 500)
{
    int i = 0;
    WiFi.mode(WIFI_STA);
#if defined(ARDUINO_ARCH_ESP8266)
    WiFi.forceSleepWake();
    delay(200);
#endif
    WiFi.begin(ssid, password);
    do
    {
        delay(pause);
        Serial.print(".");
    } while (!isConnected() || i++ < max_tries);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    return isConnected();
}


void ConnectionManager::run(){
    telnet.loop();
    //do other shit
}


void ConnectionManager::onTelnetRecieved(String str)
{
    telnet.print("recieved: ");
    telnet.println(str);
    telnet.println("");
    //TODO make it nice
    // if (str == "lon")
    // {
    //     pcf8574.digitalWrite(LED, HIGH);
    // }
    // else if (str == "loff")
    // {
    //     pcf8574.digitalWrite(LED, LOW);
    // }
    // else if (str == "w")
    // {
    //     forward();
    // }
    // else if (str == "a")
    // {
    //     left();
    // }
    // else if (str == "d")
    // {
    //     right();
    // }
    // else if (str == "s")
    // {
    //     back();
    // }
    // else if (str == "q")
    // {
    //     stopMotors();
    // }
}

static void ConnectionManager::onTelnetConnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" connected");
    telnet.println("\nWelcome " + telnet.getIP());
    telnet.println("(Use ^] + q  to disconnect.)");
}

void ConnectionManager::onTelnetDisconnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" disconnected");
}

void ConnectionManager::onTelnetReconnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" reconnected");
}

void ConnectionManager::onTelnetConnectionAttempt(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" tried to connected");
}



