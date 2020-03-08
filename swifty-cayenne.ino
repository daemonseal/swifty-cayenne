#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

#define AIR_CHANNEL 4
#define AIR_PIN 4

#define FOG_CHANNEL 5
#define FOG_PIN 5

// WiFi network info.
//char ssid[] = "sabaiheart";
//char wifiPassword[] = "ok0boVu1";
char ssid[] = "IoT-dragino";
char wifiPassword[] = "IoT12345";

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

CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(0, millis());
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}


CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  getValue.setError("Error occured!");
}

CAYENNE_IN(AIR_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  int value = getValue.asInt();
  digitalWrite(AIR_PIN, value);
}

CAYENNE_IN(FOG_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  int value = getValue.asInt();
  digitalWrite(FOG_PIN, value);
}
