# Slotscreen (esp32 version)
This is the esp32 version of the arduino slot machine, complete with just-about working wifi, firebase and money system. Although this project is intended for the Grove kit on the Arduino Uno WiFi, development ended up being based on a Wokwi-platformIO workflow. Due to a lack of WiFi-based Arduino boards on Wokwi, this version is built around the esp32, however the code works on the Uno with a few tweaks.
To connect this with your own firebase, create a secrets.h file defining "WIFI_SSID", "WIFI_PASSWORD", "REFERENCE_URL", and "AUTH_TOKEN"
