#include <Wire.h>
#include <Adafruit_HDC1000.h>

#include "ESP8266WiFi.h"
#include "PubSubClient.h"

#include "settings.h"

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Set SDA and SDL ports
  Wire.begin(2, 14);

  // Start sensor
  if (!hdc.begin()) {
    while (1);
  }
}

void setup_wifi() {
  delay(10);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (!client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      delay(5000);
    }
  }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return newValue < prevValue - maxDiff || newValue > prevValue + maxDiff;
}

long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 1.0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;

    float newTemp = hdc.readTemperature();
    float newHum = hdc.readHumidity();

    if (checkBound(newTemp, temp, diff)) {
      temp = newTemp;
      client.publish(temperature_topic, String(temp).c_str(), true);
    }

    if (checkBound(newHum, hum, diff)) {
      hum = newHum;
      client.publish(humidity_topic, String(hum).c_str(), true);
    }
  }
}
