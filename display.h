#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

extern const int a;
extern const int b;
extern const int c;
extern const int d;
extern const int e;
extern const int f;
extern const int g;
extern const int dp;

extern const int digit1;
extern const int digit2;
extern const int digit3;

extern const int segments[];
extern const int digits[];

extern const byte numbers[10][8];

extern int displayedNumbers[3];
extern bool displayedDots[3];

extern unsigned long lastDisplayUpdate;
extern const int displayUpdateInterval;
extern int currentDigit;

void setupDisplay();
void loopDisplay();
void multiplexDisplay();
void setDigitActive(int digitIndex);
void setDigitInactive(int digitIndex);
void setDigit(int number, bool dot);
void displayFloat(float value);

#endif