# iot-temp

ESP8266 with temperature & humidity wireless sensor.

I use a huzzah ESP8266 and a HDC1008 from adafruit.

![prototyping board](photo.jpg)

## Requirement

This project use PlatformIO, an open source ecosystem for IoT development
written in python. You can install it through pip :
```
pip install platformio
```

## Compile

Compile the program with the following command :
```
platformio run
```

## Upload

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
