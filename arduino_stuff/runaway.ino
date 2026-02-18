/**
   Mini piano for Arduino.

   You can control the colorful buttons with your keyboard:
   After starting the simulation, click anywhere in the diagram to focus it.
   Then press any key between 1 and 8 to play the piano (1 is the lowest note,
   8 is the highest).

   Copyright (C) 2021, Uri Shaked. Released under the MIT License.
*/

#include "pitches.h"

#define SPEAKER_PIN 8

const uint8_t buttonPins[] = { 12, 11, 10, 9, 7, 6, 5, 4 };
const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const int numTones = sizeof(buttonPins) / sizeof(buttonPins[0]);

void setup() {
  for (uint8_t i = 0; i < numTones; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  int pitch = NOTE_E6;
  int ourdelay = 300;
  tone(SPEAKER_PIN, pitch);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);
  
  tone(SPEAKER_PIN, pitch);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);
  
  tone(SPEAKER_PIN, pitch);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, pitch);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_E5);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_DS6);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_DS6);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_DS6);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_DS5);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_CS6);
  delay(ourdelay);
  noTone(SPEAKER_PIN);
  delay(ourdelay);

  tone(SPEAKER_PIN, NOTE_CS6);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay);


tone(SPEAKER_PIN, NOTE_CS6);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay);  

tone(SPEAKER_PIN, NOTE_CS5);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay); 

tone(SPEAKER_PIN, NOTE_A6);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay); 
tone(SPEAKER_PIN, NOTE_A6);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay); 
tone(SPEAKER_PIN, NOTE_GS6);
delay(ourdelay);
noTone(SPEAKER_PIN);
delay(ourdelay); 


}
  
