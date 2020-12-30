/* Trigger an MP3 to play when someone is detected at a certain range by a VL53L0X sensor
*/

#include <Wire.h>
#include <VL53L0X.h>
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

int trigger_distance = 500; // the distance in mm at which the mp3 is triggered
int player_volume = 15; // lower numbers == louder volume
int state = 0; // states -      0: distance sensing       1: playing mp3
int i = 1; // holds track number 
int num_tracks = 3; // how many tracks do we have?
String filename = "/track001.mp3";

VL53L0X sensor;

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();

  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }


  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(player_volume, player_volume);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

}

void loop()
{
  int sensorReading = sensor.readRangeContinuousMillimeters();
  Serial.print(sensorReading);
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }

  Serial.println();
  delay(100);

  if (state == 1) {

    int n = filename.length();
 
    // declaring character array
    char char_array[n + 1];
 
    // copying the contents of the
    // string to char array
   char new_filename = strcpy(char_array, filename.c_str());

    musicPlayer.playFullFile(new_filename); // go to the next track - these are sequential
  
    if (i < num_tracks){
      i++; // go to the next track
    }
    else{
      i = 1; // return to track 1
    }
    filename = "track00" + String(i) + ".mp3";
    Serial.println(filename);
    
    state = 0; // once mp3 is done playing, go back to searching for human detections
}

else if (state == 0) {
    int sensorReading = sensor.readRangeContinuousMillimeters();
    Serial.print(sensorReading);
    Serial.println();
    
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT");
    }

    else if (sensorReading < trigger_distance) {
      Serial.println("human detected");
      state = 1;
    }
  }

  else {
    Serial.println("something is wrong.");
    Serial.println(state);
  }

}
