/* ------------------------------------------------- */

#include "ESPTelnet.h"
#include "PCF8574.h"

#include <Wire.h>
/* ------------------------------------------------- */

#define SERIAL_SPEED    9600
#define WIFI_SSID       "SKAR"

#define WIFI_PASSWORD   "kristalA152-+0"

/* ------------------------------------------------- */

ESPTelnet telnet;
IPAddress ip;

/* ------------------------------------------------- */

PCF8574 pcf8574(0x20, 0, 2);
#define MOTOR_A_PIN1 P1
#define MOTOR_A_PIN2 P2
#define MOTOR_B_PIN1 P5
#define MOTOR_B_PIN2 P6

#define LED P0



/* ------------------------------------------------- */

void setupSerial(long speed, String msg = "") {
  Serial.begin(speed);
  while (!Serial) {
  }
  delay(200);
  Serial.println();
  Serial.println();
  if (msg != "") Serial.println(msg);
}

/* ------------------------------------------------- */

bool isConnected() {
  return (WiFi.status() == WL_CONNECTED);
}

/* ------------------------------------------------- */

bool connectToWiFi(const char* ssid, const char* password, int max_tries = 20, int pause = 500) {
  int i = 0;
  WiFi.mode(WIFI_STA);
#if defined(ARDUINO_ARCH_ESP8266)
  WiFi.forceSleepWake();
  delay(200);
#endif
  WiFi.begin(ssid, password);
  do {
    delay(pause);
    Serial.print(".");
  } while (!isConnected() || i++ < max_tries);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  return isConnected();
}

/* ------------------------------------------------- */

void errorMsg(String error, bool restart = true) {
  Serial.println(error);
  if (restart) {
    Serial.println("Rebooting now...");
    delay(2000);
    ESP.restart();
    delay(2000);
  }
}

/* ------------------------------------------------- */
void forward() {
  pcf8574.digitalWrite(MOTOR_A_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_A_PIN2, HIGH);
  pcf8574.digitalWrite(MOTOR_B_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN2, HIGH);
}
void left() {
  pcf8574.digitalWrite(MOTOR_A_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_A_PIN2, HIGH);
  pcf8574.digitalWrite(MOTOR_B_PIN1, HIGH);
  pcf8574.digitalWrite(MOTOR_B_PIN2, LOW);
}
void right() {
  pcf8574.digitalWrite(MOTOR_A_PIN1, HIGH);
  pcf8574.digitalWrite(MOTOR_A_PIN2, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN2, HIGH);
}
void back() {
  pcf8574.digitalWrite(MOTOR_A_PIN1, HIGH);
  pcf8574.digitalWrite(MOTOR_A_PIN2, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN1, HIGH);
  pcf8574.digitalWrite(MOTOR_B_PIN2, LOW);
}

void stopMotors() {
  pcf8574.digitalWrite(MOTOR_A_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_A_PIN2, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN1, LOW);
  pcf8574.digitalWrite(MOTOR_B_PIN2, LOW);
}



String going = "stop";
void onTelnetRecieved(String str) {
  telnet.print("recieved: ");
  telnet.println(str);
  telnet.println("");

  if (str == "lon") {
    pcf8574.digitalWrite(LED, HIGH);
  } else if (str == "loff") {
    pcf8574.digitalWrite(LED, LOW);
  } else if (str == "w") {
    forward();
  }
  else if (str == "a") {
    left();
  }
  else if (str == "d") {
    right();

  } else if (str == "s") {
    back();
  } else if (str == "q") {
    stopMotors();
  }

}



void onTelnetConnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" connected");
  telnet.println("\nWelcome " + telnet.getIP());
  telnet.println("(Use ^] + q  to disconnect.)");
}

void onTelnetDisconnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" disconnected");
}

void onTelnetReconnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" reconnected");
}

void onTelnetConnectionAttempt(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" tried to connected");
}



void setupTelnet() {
  // passing onfunctions for various telnet events
  telnet.onConnect(onTelnetConnect);
  telnet.onConnectionAttempt(onTelnetConnectionAttempt);
  telnet.onReconnect(onTelnetReconnect);
  telnet.onDisconnect(onTelnetDisconnect);
  telnet.onInputReceived(onTelnetRecieved);


  Serial.print("- Telnet: ");
  if (telnet.begin()) {
    Serial.println("running");
  } else {
    Serial.println("error.");
    errorMsg("Will reboot...");
  }
}

/* ------------------------------------------------- */

// (optional) callback functions for telnet events


/* ------------------------------------------------- */

int i2cPins[2] = {0, 2};

void setup() {
  pcf8574.pinMode(MOTOR_A_PIN1, OUTPUT);
  pcf8574.pinMode(MOTOR_A_PIN2, OUTPUT);
  pcf8574.pinMode(MOTOR_B_PIN1, OUTPUT);
  pcf8574.pinMode(MOTOR_B_PIN2, OUTPUT);
  pcf8574.pinMode(LED, OUTPUT);


  //Wire.begin(i2cPins[0], i2cPins[1]);

  setupSerial(SERIAL_SPEED, "Telnet Test");

  Serial.print("- Wifi: ");
  connectToWiFi(WIFI_SSID, WIFI_PASSWORD);

  if (isConnected()) {
    ip = WiFi.localIP();
    Serial.print(" ");
    Serial.println(ip);
    setupTelnet();
  } else {
    Serial.println();
    errorMsg("Error connecting to WiFi");
  }

  if (pcf8574.begin()) {
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }
}

/* ------------------------------------------------- */
unsigned long previousMillis = 0;
bool stan = 0;
void loop() {
  telnet.loop();

  // send serial input to telnet as output
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= 2000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    //telnet.print("siema");
    //jakas zmiana kodu
  }
}

//* ------------------------------------------------- */