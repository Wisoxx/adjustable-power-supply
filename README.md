# Adjustable Laboratory Power Supply

## Project Goal
The goal of this project was to design and build a laboratory power supply with adjustable output voltage and integrated measurement of both voltage and load current. The device was designed as a versatile tool for powering and diagnosing various electronic circuits. Special attention was given to precise voltage regulation, accurate measurements, and stable operation.

## Specifications
- **Input Voltage:** 230V AC, 50Hz  
- **Output Voltage Range:** 1.3V – 15V  
- **Maximum Output Current:** 0.5A  
- **Current Measurement Resolution:** 1mA  
- **Control:** Voltage adjustment and parameter reading via computer  
- **Voltage Regulation:** Manual, using a potentiometer  
- **Display:** Voltage measurement shown on a screen  

## Hardware Overview
The circuit consists of multiple sections:
1. **Power Supply and Rectification**  
2. **Microcontroller and User Interface**  
3. **Voltage Level Adjustment**  
4. **Voltage Transmission**  
5. **Voltage Measurement and Noise Suppression**  
6. **Current Measurement via a Series Resistor**

A schematic of the circuit is included in the documentation.

## Circuit Description
The power supply uses a **230V to 12V transformer**, followed by a **KBP02G bridge rectifier** for full-wave rectification. A **4700µF capacitor (C1)** smooths voltage fluctuations, and **C2** acts as a decoupling capacitor. The supply voltage powers an **LM358 operational amplifier**, an **Arduino Uno microcontroller**, and other circuit components. 

Voltage regulation is performed using an **LM317T adjustable voltage regulator**, with control signals processed by the microcontroller. A **DAC (Digital-to-Analog Converter)** controlled via **I2C** is used to set the output voltage. A **non-inverting operational amplifier** scales the DAC output to drive the **LM317T**, enabling software-based voltage adjustment.

For **current measurement**, a **series resistor (R1)** is used to determine voltage drop, which is then amplified using a **differential amplifier**. The microcontroller calculates the current using Ohm's Law.

User interaction is facilitated through a **potentiometer (RV1)** for manual voltage adjustment and a **three-digit 7-segment display** for real-time parameter visualization.

## Software Implementation
The Arduino Uno is programmed using **C++** in **Arduino IDE**. The software consists of two main modules:
1. **Main Module:** Reads voltage and current values, processes signals, and communicates with the computer.
2. **Display Module:** Handles the 7-segment display, efficiently updating digits to minimize memory usage.

The software also includes an optional feature to generate **sinusoidal waveforms**, which can be activated by modifying specific code sections.

