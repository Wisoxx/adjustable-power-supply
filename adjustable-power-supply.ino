#include <Wire.h>//Include the Wire library to talk I2C
#include "display.h"
#include <math.h>

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
#define MCP4725_ADDR 0x60
//For devices with A0 pulled HIGH, use 0x60
const int i_pin = A0;
const int u_pin = A1;
const int x_pin = A2;
const int size = 100;

int sineWave[size];
int x;
int index = 0;
unsigned long lastSerialUpdate = 0;
const int serialUpdateInterval = 100;
int sample_idx = 0;

void generateSineWave() {
  for (int i = 0; i < size; i++) {
    float angle = (2.0 * M_PI * i) / size; // Convert index to angle
    float sineValue = (sin(angle) + 1.0) / 2.0;  // Normalize from -1..1 to 0..1
    sineWave[i] = (int)(sineValue * 4095); // Scale to 12-bit DAC range (0-4095)
  }
}

void setup()
{
  setupDisplay();
  Wire.begin();
  Serial.begin(115200);
  generateSineWave();
};

void loop()
{
  loopDisplay();
  // displayFloat(12.3);
  if (millis() - lastSerialUpdate >= serialUpdateInterval) {
      lastSerialUpdate = millis();

    // Read ADC values
    int raw_x = analogRead(x_pin);
    int raw_voltage = analogRead(u_pin);
    int raw_current = analogRead(i_pin);

    // Convert to real voltage (assuming 5V reference and 10-bit ADC)
    float u = raw_voltage * (5.0 / 1023.0) * 3.517;
    float i_scaled = raw_current * (5.0 / 1023.0);  // voltage on resistor 1.1 ohm and minus offset
    float i = 0.0347 * i_scaled * i_scaled * i_scaled - 0.227 * i_scaled * i_scaled + 0.6511 * i_scaled - 0.6063;  // aproximation
    i = i < 0 ? 0 : i;

    // float x_scaled = map(raw_x, 0, 1023, 0, 4095) * (sineWave[index] / 4095.0);
    // x = (int)x_scaled;  // Convert back to integer
    x = map(raw_x, 0, 1023, 0, 4095);

    // Ensure x is within bounds
    x = constrain(x, 0, 4095);

    Serial.print("X:");
    Serial.print(map(x, 0, 4095, 127, 1535)/100.0);
    Serial.print("V, ");

    Serial.print("U:");
    Serial.print(u, 2);
    Serial.print("V, ");
    displayFloat(u);

    Serial.print("I:");
    Serial.print(i, 3);
    Serial.println("A");


    Wire.beginTransmission(MCP4725_ADDR);
    Wire.write(64);                     // cmd to update the DAC
    Wire.write(x >> 4);        // the 8 most significant bits...
    Wire.write((x & 15) << 4); // the 4 least significant bits...
    Wire.endTransmission();
    // index = (index + 1) % size;
  }
}
