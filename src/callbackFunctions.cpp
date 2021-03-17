namespace CallbackFunctions{
void onTelnetRecieved(String str)
{
    telnet.print("recieved: ");
    telnet.println(str);
    telnet.println("");

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

static void onTelnetConnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" connected");
    telnet.println("\nWelcome " + telnet.getIP());
    telnet.println("(Use ^] + q  to disconnect.)");
}

void onTelnetDisconnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" disconnected");
}

void onTelnetReconnect(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" reconnected");
}

void onTelnetConnectionAttempt(String ip)
{
    Serial.print("- Telnet: ");
    Serial.print(ip);
    Serial.println(" tried to connected");
}




}