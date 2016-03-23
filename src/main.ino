#include <Wire.h>
#include <Adafruit_HDC1000.h>
#include <Homie.h>

const int INTERVAL = 300;

unsigned long lastTemperatureSent = 0;
unsigned long lastHumiditySent = 0;

HomieNode temperatureNode("temperature", "temperature");
HomieNode humidityNode("humidity", "humidity");
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

void sendTemperature() {
  if (millis() - lastTemperatureSent >= INTERVAL * 1000UL
  || lastTemperatureSent == 0) {
    float temperature = hdc.readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    if (Homie.setNodeProperty(temperatureNode, "temperature", String(temperature), true)) {
      lastTemperatureSent = millis();
    } else {
      Serial.println("Sending temperature failed");
    }
  }
}

void sendHumidity() {
  if (millis() - lastHumiditySent >= INTERVAL * 1000UL
  || lastHumiditySent == 0) {
    float humidity = hdc.readHumidity();
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    if (Homie.setNodeProperty(humidityNode, "humidity", String(humidity), true)) {
      lastHumiditySent = millis();
    } else {
      Serial.println("Sending humidity failed");
    }
  }
}

void loopHandler() {
  sendTemperature();
  sendHumidity();
}

void setupHandler() {
  Homie.setNodeProperty(temperatureNode, "unit", "c", true);
  Homie.setNodeProperty(humidityNode, "unit", "%", true);
  // Set SDA and SDL ports
  Wire.begin(2, 14);
  // Start sensor
  hdc.begin();
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
