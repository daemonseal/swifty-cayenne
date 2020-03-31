#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// Connected to RELAY INPUT 1 (Pink outlet)
#define AIR_CHANNEL 4
#define AIR_PIN 4
#define AUTO_AIR_CHANNEL 8

// Connected to RELAY INPUT 2 (Green outlet)
#define FOG_CHANNEL 5
#define FOG_PIN 5
#define AUTO_FOG_CHANNEL 10

// WiFi network info.
char ssid[] = "IoT-dragino";
char wifiPassword[] = "IoT12345";

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
  // Write uptime in seconds to Cayenne
  unsigned long seconds = millis();
  Cayenne.virtualWrite(0, seconds);
}


CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  getValue.setError("Error occured!");
}

CAYENNE_IN(AIR_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  Serial.println("MANUAL EXHAUST FAN");
  int value = getValue.asInt();
  digitalWrite(AIR_PIN, value);
}

CAYENNE_IN(FOG_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
   Serial.println("MANUAL HUMIDIFIER");
  int value = getValue.asInt();
  digitalWrite(FOG_PIN, value);
}

CAYENNE_IN(AUTO_AIR_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  Serial.println("AUTO EXHAUST FAN");
  int value = getValue.asInt();
  if(value == 1){
    digitalWrite(FOG_PIN, LOW);
    digitalWrite(AIR_PIN, HIGH);
    delay(12500);
  }
  digitalWrite(AIR_PIN, LOW);
}

CAYENNE_IN(AUTO_FOG_CHANNEL)
{
  Serial.println("Incoming from Cayenne");
  Serial.println("AUTO HUMIDIFIER");
  int value = getValue.asInt();
  if(value == 1){
    digitalWrite(AIR_PIN, LOW);
    digitalWrite(FOG_PIN, HIGH);
    delay(12500);
  }
  digitalWrite(FOG_PIN, LOW);
}
