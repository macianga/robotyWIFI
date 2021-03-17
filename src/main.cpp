/* ------------------------------------------------- */
#include "ConnectionManager.h"
#include "PCF8574.h"

#include <Wire.h>
/* ------------------------------------------------- */


/* ------------------------------------------------- */


/* ------------------------------------------------- */

PCF8574 pcf8574(0x20, 0, 2);


#define MOTOR_A_PIN1 P1
#define MOTOR_A_PIN2 P2
#define MOTOR_B_PIN1 P5
#define MOTOR_B_PIN2 P6

#define LED P0



/* ------------------------------------------------- */

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

  // if (isConnected()) {
  //   ip = WiFi.localIP();
  //   Serial.print(" ");
  //   Serial.println(ip);
  //   setupTelnet();
  // } else {
  //   Serial.println();
  //   errorMsg("Error connecting to WiFi");
  // }

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