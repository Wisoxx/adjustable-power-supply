#include "display.h"

// Define segment pins
const int a = 6;
const int b = 2;
const int c = 9;
const int d = 11;
const int e = 12;
const int f = 5;
const int g = 8;
const int dp = 10;

// Define digit control pins (common anode)
const int digit1 = 7;
const int digit2 = 4;
const int digit3 = 3;

const int segments[] = {a, b, c, d, e, f, g, dp};
const int digits[] = {digit1, digit2, digit3};

// Segment patterns for numbers 0-9 (Common Anode: LOW = ON, HIGH = OFF)
const byte numbers[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 1}, // 2
  {0, 0, 0, 0, 1, 1, 0, 1}, // 3
  {1, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 1, 0, 0, 1, 0, 0, 1}, // 5
  {0, 1, 0, 0, 0, 0, 0, 1}, // 6
  {0, 0, 0, 1, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0, 1}, // 8
  {0, 0, 0, 0, 1, 0, 0, 1}  // 9
};

// Array to store the numbers for each digit
int displayedNumbers[3] = {-1, -1, -1}; // Default to blank
bool displayedDots[3] = {false, false, false}; // Default no dots

unsigned long lastDisplayUpdate = 0;
const int displayUpdateInterval = 2;
int currentDigit = 0;

void setupDisplay() {
  for (int i = 0; i < 8; i++) {
    pinMode(segments[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], LOW);
  }
}

void loopDisplay() {
  if (millis() - lastDisplayUpdate >= displayUpdateInterval) {
      lastDisplayUpdate = millis();
      multiplexDisplay();
  }

  // Timer loop counting up with 2 decimal places
  // static float timer = 0.00; // Initial timer value
  // static unsigned long lastMillis = 0;

  // // Update timer every 10ms
  // if (millis() - lastMillis >= 100) {
  //   lastMillis = millis(); // Reset the timer
  //   timer += 0.1;          // Increment timer by 0.01s

  //   if (timer >= 100.00) {
  //       timer = 0.00;  // Reset after 100 seconds
  //   }

  //   displayFloat(timer); // Display the updated timer
  // }
  // setDigitActive(0);
  // setDigitActive(1);
  // setDigitActive(2);
  // setDigit(0, false);
  // displayFloat(12.3);
}

void multiplexDisplay() {
  setDigitInactive(currentDigit);  // turn off previous digit
  currentDigit = (currentDigit + 1) % 3;  // switch to current digit
  setDigit(displayedNumbers[currentDigit], displayedDots[currentDigit]);
  setDigitActive(currentDigit);
}

void setDigitActive(int digitIndex){
  if (digitIndex < 0 || digitIndex > 2) return;

  digitalWrite(digits[digitIndex], HIGH);
}

void setDigitInactive(int digitIndex){
  if (digitIndex < 0 || digitIndex > 2) return;

  digitalWrite(digits[digitIndex], LOW);
}

void setDigit(int number, bool dot) {
  if (number == -1) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segments[i], HIGH);
    }
  } else {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segments[i], numbers[number][i]);
    }
  }

  digitalWrite(dp, dot ? LOW : HIGH);
}

void displayFloat(float value) {
  int firstDigit, secondDigit, thirdDigit;
  bool decimalPoints[3] = {false, false, false};

  // Cap value at 999
  if (value > 999) value = 999;

  if (value >= 100) {
    firstDigit = (int)value / 100;
    secondDigit = ((int)value / 10) % 10;
    thirdDigit = (int)value % 10;
  } 
  else if (value >= 10) {
    firstDigit = (int)value / 10;
    secondDigit = (int)value % 10;
    thirdDigit = (int)(value * 10) % 10;
    decimalPoints[1] = true;
  } 
  else if (value >= 1) {
    firstDigit = (int)value;
    secondDigit = (int)(value * 10) % 10;
    thirdDigit = (int)(value * 100) % 10;
    decimalPoints[0] = true;
  } 
  else {
    firstDigit = 0;
    secondDigit = (int)(value * 10) % 10;
    thirdDigit = (int)(value * 100) % 10;
    decimalPoints[0] = true;
  }

  displayedNumbers[0] = firstDigit;
  displayedNumbers[1] = secondDigit;
  displayedNumbers[2] = thirdDigit;

  displayedDots[0] = decimalPoints[0];
  displayedDots[1] = decimalPoints[1];
  displayedDots[2] = decimalPoints[2];
}
