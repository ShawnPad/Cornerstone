#include <LiquidCrystal.h>          //the liquid crystal libarry contains commands for printing to the display
#include "pitches.h"

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);   // tell the RedBoard what pins are connected to the display
int r = 1;
int g = 0;
int b = 2;
int s = 13;
int melody[] = {
  DS4, G3, C4, G3, DS4, G3, C4, G3, F4, G3, C4, G3, F4, G3, C4, G3, DS4, G3,
  AS3, G3, DS4, G3, AS3, G3, F4, G3, AS3, G3, F4, G3, AS3, G4, C5, AS4, C4, AS4,
  AS4, AS4, G4, AS4, AS4, AS4, F4, F4, G4, DS4, G3, DS4, G3, F4, G3, F4, G3, F4,
  G3, F4, G4, G4, C5, AS4, C5, AS4, AS4, G4, AS4, G4, AS4, AS4, AS4, F4, F4, G4,
  DS4, G3, DS4, G3, F4, G3, F4, G3, F4, G3, F4, G4, C5, AS4, C5, AS4, C5, DS5,
  C5, AS4, C5, AS4, C5, DS5, DS5, AS4, F5, 0, G4, C5, AS4, C5, AS4, C5,
  DS5, C5, AS4, C5, AS4, C5, DS5, DS5, 0, AS4, AS4, F5, DS5, DS5, AS5, AS5, DS5,
  DS5, C5, DS5, C5, C5, 0, C5, AS5, AS5, AS5, DS5, DS5, DS5, AS5, AS5, DS5,
  DS5, C5, DS5, C5, 0, C5, AS5, AS5, 0, D5, 0, 0, D5, 0,
  DS5
};
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 4, 4, 8, 8, 8, 4, 8, 4, 8, 8, 8, 8,
  8
};
int hey[] = {
  CS4, B3, B3, B4, GS4, FS4, E4, 0, B4, 0, B4, GS4,
  GS4, FS4, E4, E4, FS4, GS4, E4, E4, 0, GS4, E4, E4, 0, GS4, FS4, 0, FS4, FS4,
  FS4, FS4, CS4, E4, B4, GS4, FS4, E4, 0, B4, 0, B4, GS4, GS4, FS4, E4, E4,
  FS4, GS4, CS4, E4, FS4, 0, B3, E4, 0, DS4, E4
};
int noteDurationsHey[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
int elementCount = 0;
int heyCount = 0;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
  pinMode(s, OUTPUT);
  pinMode(r, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  elementCount = sizeof(melody) / sizeof(int);
  heyCount = sizeof(hey) / sizeof(int);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(b) == LOW) {
    apologize();
  }
  else if (digitalRead(r) == LOW) {
    heys();
  }
  else {
    lcd.clear();
    noTone(s);                        //if no key is pressed turn the buzzer off
  }
}
void apologize() {
  lcd.clear();
  lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Apologize");       //print hello, world! starting at that position
  lcd.setCursor(0, 1);              //mvoe the cursor to the first space of the bottom row
  lcd.print("One Republic");       //print the number of seconds that have passed since the last reset
  for (int thisNote = 0; thisNote < elementCount; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(s, melody[thisNote], noteDuration);
    //delay(508);
    delay(300);
    noTone(s);
    if (digitalRead(g) == LOW) { //if the third key is pressed
      lcd.clear();
      break;
    }
    if (digitalRead(r) == LOW) { //if the third key is pressed
      lcd.clear();
      heys();
      break;
    }
  }
}
void heys() {
  lcd.clear();
  lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Hey, Soul Sister");       //print hello, world! starting at that position
  lcd.setCursor(0, 1);              //mvoe the cursor to the first space of the bottom row
  lcd.print("Train");       //print the number of seconds that have passed since the last reset
  for (int thisNote = 0; thisNote < heyCount; thisNote++) {
    int noteDuration = 1000 / noteDurationsHey[thisNote];
    tone(s, hey[thisNote], noteDuration);
    delay(400);
    noTone(s);
    if (digitalRead(g) == LOW) { //if the third key is pressed
      lcd.clear();
      break;
    }
    if (digitalRead(b) == LOW) { //if the third key is pressed
      lcd.clear();
      apologize();
      break;
    }
  }
}
