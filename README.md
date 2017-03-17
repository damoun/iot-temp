# iot\-temp

ESP8266 with temperature & humidity wireless sensor.

This project is compatible with 2 boards:
- huzzah ESP8266 and a HDC1008 from adafruit
- d1 mini ESP8266 and a DHT11 from wemos

## Requirements

This project use PlatformIO, an open source ecosystem for IoT development
written in python. You can install it through pip:
```
pip install platformio
```

You need to setup a MQTT server too.

## Settings

On the first boot, the sensor will start a wireless to be configured.
You can follow the procedure from the [homie-esp8266 lib][homie-esp8266-doc-url].

## Compile

Compile the program with the following command:
```
platformio run
```

## Upload

On every upload, you need to put the ESP8266 in upload mode:
- On huzzah, you have to press the GPIO0 button and the reset button.
The LED should be red.
- On wemos, you have to press the RESET button and power on the board.
The LED should blink.

To upload the compiled program to the ESP8266, use the following command:
```
platformio run --target upload -e wemos|huzzah
```

## Debug

To debug the program, you can get the serial output with the following
command:
```
platformio serialports monitor -b 115200
```

[travis-img]: https://travis-ci.org/Damoun/iot-temp.svg
[travis-url]: https://travis-ci.org/Damoun/iot-temp/
[homie-esp8266-doc-url]: https://homie-esp8266.readme.io/docs/json-configuration-file
