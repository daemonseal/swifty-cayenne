#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

#define AIR_CHANNEL 4
#define AIR_PIN 4

#define FOG_CHANNEL 5
#define FOG_PIN 5

// WiFi network info.
char ssid[] = "sabaiheart";
char wifiPassword[] = "ok0boVu1";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "9a837da0-47db-11ea-b73d-1be39589c6b2";
char password[] = "27aa25d313921d02945b9dacda3ddb6d2a516053";
char clientID[] = "4105f260-5543-11ea-a38a-d57172a4b4d4";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  pinMode(AIR_PIN, OUTPUT);
  pinMode(FOG_PIN, OUTPUT);
}

void loop() {
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(0, millis());
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
//  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}

// This function is called when data is sent from Cayenne.
CAYENNE_IN(AIR_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  // Write value to turn the relay switch on or off. This code assumes you wire your relay as normally open.
  int value = getValue.asInt();
  digitalWrite(AIR_PIN, value);
}

CAYENNE_IN(FOG_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  // Write value to turn the relay switch on or off. This code assumes you wire your relay as normally open.
  int value = getValue.asInt();
  digitalWrite(FOG_PIN, value);
}
