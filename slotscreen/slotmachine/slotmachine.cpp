// LCD1602 Arduino Uno slot machine

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const int buttonPin = 2;

const int DEBOUNCE_DELAY = 50;
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
int slotVals[3] = {-1, -1, -1};


void setup() {
  // rng (dont touch a0 pin)
  randomSeed(analogRead(0));
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
}

void loop() {
  // animation
  // do this in a for loop
  if (slotVals[0] == -1){
    GetRandom(0);
  }
  if (slotVals[1] == -1){
    GetRandom(1);
  }
  if (slotVals[2] == -1){
    GetRandom(2);
  }

  currentState = digitalRead(buttonPin);
    if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button has been pressed
    if (lastSteadyState == HIGH && currentState == LOW)
    {
        // do this in a for loop
        if (slotVals[0] == -1){
          slotVals[0] = GetRandom(0);

        }
        else if (slotVals[1] == -1){
          slotVals[1] = GetRandom(1);

        }
        else if (slotVals[2] == -1){
          slotVals[2] = GetRandom(2);

          // the moneycounter 3000
          int counter = 0;
          for (int i = 0; i < 3; i++){
            if (slotVals[i] == 7)
            {
              counter++;
            }
          }
          lcd.setCursor(0, 1);

          if (counter == 0) {
            lcd.print("You lose. Sad.");
          }
          else if (counter == 1){
            lcd.print("You won a euro!!");
          }
          else if (counter == 2){
            lcd.print("2 EURO!!!!!!!!!!");
          }
          else if (counter == 3){
            lcd.print("JACKPOT JACKPOT!");
          }



        }
        else {
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

int GetRandom(int position){
  int ranNum;
    ranNum = random(0, 10);
    lcd.setCursor(position, 0);
    lcd.print(ranNum);

  return ranNum;
}
