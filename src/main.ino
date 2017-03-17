#if defined (HDC_SENSOR)
  #include <Wire.h>
  #include <Adafruit_HDC1000.h>
#elif defined (DHT_SENSOR)
  #include <DHT.h>
#endif
#include <Homie.h>

unsigned long lastTimeSent = 0;

HomieNode temperatureNode("temperature", "temperature");
HomieNode humidityNode("humidity", "humidity");

#define INTERVAL 300
#if defined (HDC_SENSOR)
  #define SDA 2
  #define SDL 14
  Adafruit_HDC1000 sensor = Adafruit_HDC1000();
#elif defined (DHT_SENSOR)
  #define DHTPIN D4
  #define DHTTYPE DHT11
  DHT sensor(DHTPIN, DHTTYPE);
#endif

void sendTemperature() {
    float temperature = sensor.readTemperature();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    if (!Homie.setNodeProperty(temperatureNode, "temperature", String(temperature), true)) {
      Serial.println("Sending temperature failed");
    }
}

void sendHumidity() {
  float humidity = sensor.readHumidity();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (!Homie.setNodeProperty(humidityNode, "humidity", String(humidity), true)) {
    Serial.println("Sending humidity failed");
  }
}

void loopHandler() {
  if (millis() - lastTimeSent >= INTERVAL * 1000UL || lastTimeSent == 0) {
    sendHumidity();
    sendTemperature();
    lastTimeSent = millis();
  }
}

void setupHandler() {
  Homie.setNodeProperty(temperatureNode, "unit", "c", true);
  Homie.setNodeProperty(humidityNode, "unit", "%", true);
  #if defined (HDC_SENSOR)
  Wire.begin(SDA, SDL);
  #endif
  sensor.begin();
  Serial.begin(115200);
}

void setup() {
  Homie.setFirmware("iot-temp", "1.0.0");

  Homie.registerNode(temperatureNode);
  Homie.registerNode(humidityNode);

  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
