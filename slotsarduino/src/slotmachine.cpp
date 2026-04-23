#include <WiFiS3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Firebase.h>
#include <ArduinoJson.h>
#include "secrets.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

Firebase fb(REFERENCE_URL, AUTH_TOKEN);

const int buttonPin = 2;

const int DEBOUNCE_DELAY = 10;
int lastSteadyState = LOW;          // the previous steady state from the input pin
int lastFlickerableState = LOW;     // the previous flickerable state from the input pin
int currentState;                   // the current reading from the input pin
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long timeSinceNote = 0;
int slotVals[3] = {-1, -1, -1};
int money = 0;
String outputBuffer[6];
int outputBufferIndex = 0;

unsigned int thisNote = 0;
#define NOTE_CS5 554
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_CS6 1109
#define NOTE_DS6 1245
#define NOTE_E6 1319

int melody[] = {
    NOTE_E6,
    NOTE_E6,
    NOTE_E6,
    NOTE_E5,
    NOTE_DS6,
    NOTE_DS6,
    NOTE_DS6,
    NOTE_DS5,
    NOTE_CS6,
    NOTE_CS6,
    NOTE_CS6,
    NOTE_CS5,
    NOTE_A5,
    NOTE_A5,
    NOTE_GS5,
    NOTE_E6,
};

JsonDocument docOutput;

void playNote()
{

  // uncomment top line for actual hardware, bottom line for emulator
  // if (millis() - timeSinceNote >= 1300)
  if (millis() - timeSinceNote >= 520)
  {
    timeSinceNote = millis();
    tone(5, melody[thisNote % 16], 200);
    thisNote++;
  }
}
int GetRandom(int position)
{
  int ranNum;
  ranNum = random(0, 10);
  lcd.setCursor(position, 0);
  lcd.print(ranNum);

  return ranNum;
}

void PrintMoney()
{
  lcd.setCursor(5, 0);
  lcd.print("$: ");
  lcd.print(money);
}

void setup()
{
  // rng (dont touch a0 pin)
  randomSeed(analogRead(0));
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  lcd.print("Connecting...");
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  lcd.clear();
  lcd.print("Calculating debt..");
  int responseCode = fb.getInt("money", money);
  if (responseCode != 200)
  {
    lcd.clear();
    lcd.print("Cannot connect, starting fresh");
    delay(2000);
    money = 0;
  }

  lcd.clear();
}

void loop()
{
  // music
  playNote();

  // animation
  // do this in a for loop
  if (slotVals[0] == -1)
  {
    GetRandom(0);
    PrintMoney();
  }
  if (slotVals[1] == -1)
  {
    GetRandom(1);
  }
  if (slotVals[2] == -1)
  {
    GetRandom(2);
  }

  currentState = digitalRead(buttonPin);
  if (currentState != lastFlickerableState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button has been pressed
    if (lastSteadyState == HIGH && currentState == LOW)
    {
      // do this in a for loop
      if (slotVals[0] == -1)
      {
        slotVals[0] = GetRandom(0);
        money -= 50;
        PrintMoney();
      }
      else if (slotVals[1] == -1)
      {
        slotVals[1] = GetRandom(1);
      }
      else if (slotVals[2] == -1)
      {
        slotVals[2] = GetRandom(2);

        // the moneycounter 3000
        int counter = 0;
        for (int i = 0; i < 3; i++)
        {
          if (slotVals[i] == 7)
          {
            counter++;
          }
        }
        lcd.setCursor(0, 1);

        if (counter == 0)
        {
          lcd.print("You lose. Sad.");
          docOutput["win"] = false;
          docOutput["winAmt"] = 0;
          docOutput["money"] = money;

          // Firebase.setInt(firebaseData, "/"+String(postId)+"/slotResults", 0);
        }
        else if (counter == 1)
        {
          lcd.print("You won 50 euro!!");
          money += 50;
          PrintMoney();
          docOutput["win"] = true;
          docOutput["winAmt"] = 50;
          docOutput["money"] = money;
          // Firebase.setInt(firebaseData, "/"+String(postId)+"/slotResults", 1);
        }
        else if (counter == 2)
        {
          lcd.print("100 EURO!!!!!!!!!!");
          money += 100;
          PrintMoney();
          docOutput["win"] = true;
          docOutput["winAmt"] = 100;
          docOutput["money"] = money;
          // Firebase.setInt(firebaseData, "/"+String(postId)+"/slotResults", 2);
        }
        else
        {
          lcd.print("JACKPOT JACKPOT!");
          money += 200;
          PrintMoney();
          docOutput["win"] = true;
          docOutput["winAmt"] = 200;
          docOutput["money"] = money;
          // Firebase.setInt(firebaseData, "/"+String(postId)+"/slotResults", 3);
        }
      }
      else
      {
        docOutput.shrinkToFit();
        String output;
        serializeJson(docOutput, output);
        if (outputBufferIndex < 6)
        {
          outputBuffer[outputBufferIndex] = output;
          outputBufferIndex++;
        }
        else
        {
          // buffer is full, upload all data and reset buffer
          lcd.setCursor(0, 1);
          lcd.print("Take a break!");
          for (int i = 0; i < 6; i++)
          {
            fb.setInt("money", money);
            fb.pushJson("SlotsProd", outputBuffer[i]);
          }
          outputBufferIndex = 0;
        }
        // reset vals
        slotVals[0] = -1;
        slotVals[1] = -1;
        slotVals[2] = -1;
        lcd.clear();
      }
    }
    // save the the last steady state for button press
    lastSteadyState = currentState;
  }
}
