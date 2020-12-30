# Adafruit_MP3_Shield_VL53L0X_Time_of_Flight
This Arduino sketch combines the VL53L0X or VL53L1X or VL53LXX and the Adafruit MP3 shield to trigger a MP3 file to play when someone is within a certain distance. Feel free to use and improve upon!

Hardware:
VL53L1X Time of Flight Sensor
https://www.amazon.com/VL53L1X-Ranging-Distance-Measurement-Extension/dp/B08J1K9T5P/ref=sr_1_21?dchild=1&keywords=time+of+flight+sensor&qid=1609325983&sr=8-21
*note this should also work with the Adafruit VL53L0X or similar

Adafruit MP3 Shield w/ Onboard Amplifier
https://learn.adafruit.com/adafruit-music-maker-shield-vs1053-mp3-wav-wave-ogg-vorbis-player/overview
*note: this should work with the unamplified version of this shield as well. It will not work with the SparkFun MP3 shield without making changes to that library's config file.

Pinouts:
Time of Flight - Arduino
VIN - 5V
GND - GND
SCL - A5
SDA - A4
GPIO - unused
XSHUT - unused

Libraries / Dependencies:
Adafruit VS1053 Library: https://learn.adafruit.com/adafruit-music-maker-shield-vs1053-mp3-wav-wave-ogg-vorbis-player/library-reference
Polulu VL53L0X Library: https://github.com/pololu/vl53l0x-arduino
Note: DO NOT try to use the Adafruit VL53L0X - this library has a conflict with the shield. Use Polulu instead.

