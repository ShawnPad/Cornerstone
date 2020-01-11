int rB = 2;
int gB = 3;
int r = 9;
int g = 10;
int b = 11;
int pm = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(rB, INPUT_PULLUP);
  pinMode(gB, INPUT_PULLUP);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pm = analogRead(A0);
  if (digitalRead(rB) == LOW) {
    if (digitalRead(gB) == LOW) {
      white();
    } else {
      red();
    }
  } else if (digitalRead(gB) == LOW) {
    green();
  } else {
    off();
  }
}
void red () {

  //set the LED pins to values that make red
  analogWrite(r, (pm+20)/6);
  analogWrite(g, 0);
  analogWrite(b, 0);
}
void green () {

  //set the LED pins to values that make green
  analogWrite(r, 0);
  analogWrite(g, (pm+20)/6);
  analogWrite(b, 0);
}
void white () {

  //set the LED pins to values that make green
  analogWrite(r, (pm+20)/6);
  analogWrite(g, (pm+20)/6);
  analogWrite(b, (pm+20)/6);
}
void off () {

  //set all three LED pins to 0 or OFF
  analogWrite(r, 0);
  analogWrite(g, 0);
  analogWrite(b, 0);
}
