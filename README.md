# iot-temp [![Travis][travis-img]][travis-url]

ESP8266 with temperature & humidity wireless sensor.

I use a huzzah ESP8266 and a HDC1008 from adafruit.

![prototyping board](photo.jpg)

## Requirement

This project use PlatformIO, an open source ecosystem for IoT development
written in python. You can install it through pip :
```
pip install platformio
```

You need to setup a MQTT server too.

## Settings

The settings of the wifi ssid and password and the mqtt parameters are defined
in src/settings.h :
```
#define wifi_ssid "WIFI_SSID"
#define wifi_password "WIFI_PASSWORD"

#define mqtt_server "MQTT_IP"
#define mqtt_user "MQTT_USERNAME"
#define mqtt_password "MQTT_PASSWORD"

#define humidity_topic "MQTT_HUMIDITY_TOPIC"
#define temperature_topic "MQTT_TEMPERATURE_TOPIC"
```

## Compile

Compile the program with the following command :
```
platformio run
```

## Upload

On every upload, you need to put the ESP8266 in upload mode by pressing the
GPIO0 button and the reset button. The LED should be red.
To upload the compiled program to the ESP8266, use the following command :
```
platformio run --target upload
```

## Debug

To debug the program, you can get the serial output with the following
command :
```
platformio serialports monitor
```

[travis-img]: https://travis-ci.org/Damoun/iot-temp.svg
[travis-url]: https://travis-ci.org/Damoun/iot-temp/
