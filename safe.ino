#include <Servo.h>
#include <Wire.h>
Servo servoD;
int servoPin = 10;
int opened = 170;
int closed = 20;
int s = 6;
int p = A0;
//int code[3][4] = {{7, 3, 9, 1}, {9, 1, 4, 5}, {5, 8, 1, 7}};
int code[3][4] = {{7, 3, 9, 1}, {7, 3, 9, 1}, {7, 3, 9, 1}};
//int t[] = {1000, 3000, 3500};
int t[] = {3500, 3500, 3500};
int guess[4];
int len;
int last;
int count = 0;
int buttonPin = 0;
bool win = false;
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  len = 4;
  pinMode(s, OUTPUT);
  int a = analogRead(p);
  last = map(a, 0, 1023, 0, 10);
  pinMode(buttonPin, INPUT);
  reset();
}

void loop() {
  //Serial.println(digitalRead(buttonPin));
  // put your main code here, to run repeatedly:
  //tone(s, 3322, 8);
  if (win) {
    if (counter == 1) {
      counter++;
      delay(500);
      tone(s, 4000, 100);
      delay(500);
      tone(s, 2000, 100);;
      delay(1000);
      o();
    }
  } else if (guess[len - 1] != -1) {
    tone(s, 1000, 100);
    delay(500);
    tone(s, 1000, 100);
    delay(500);
    tone(s, 1000, 100);
    delay(500);
    tone(s, 1000, 100);
    delay(500);
    reset();
  } else {
    if (counter == 0) {
      c();
      counter++;
    }
  }
  int x = analogRead(p);
  int y = map(x, 0, 1023, 0, 10);
  for (int i = 0 ; i < len; i++) {
    if (y != last && y == code[i][count]) {
      tone(s, t[i], 100);
      delay(20);
    }
  }
  last = y;

  if (digitalRead(buttonPin) == LOW) {
    guess[count] = y;
    delay(1000);
    count++;
  }

  for (int i = 0; i < 4; i++) {
    if (guess[i] != code[0][i]) {
      win = false;
      break;
    } else {
      win = true;
    }
  }
}
void reset() {
  for (int i = 0; i < len; i++) {
    guess[i] = -1;
  }
  count = 0;
}
void c() {
  delay(1000);
  servoD.attach(servoPin);
  delay(1000);
  servoD.write(closed);
  delay(1000);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write('1');              // sends x
  Wire.endTransmission();
  delay(2000);
  servoD.detach();
}
void o() {
  delay(1000);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write('0');              // sends x
  Wire.endTransmission();
  delay(2000);
  servoD.attach(servoPin);
  delay(1000);
  servoD.write(opened);
  delay(1000);
  servoD.detach();
}
