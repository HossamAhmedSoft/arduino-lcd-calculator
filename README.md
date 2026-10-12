# Arduino LCD & Keypad Calculator

![Platform](https://img.shields.io/badge/Platform-Arduino%20Uno-00979C?logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B%20Embedded-00599C?logo=c%2B%2B&logoColor=white)
![Display](https://img.shields.io/badge/Display-HD44780%2016x2%20LCD-blue)
![License](https://img.shields.io/badge/License-MIT-green)

An embedded hardware arithmetic calculator built on the **Arduino Uno** platform utilizing a **Hitachi HD44780 16x2 Liquid Crystal Display** and a **4x4 Matrix Keypad**. Supports real-time numerical input, floating-point arithmetic (+, -, *, /), calculation chaining, and zero-division protection.

---

## Hardware Specifications & Bill of Materials (BOM)

| Component | Quantity | Description / Pinout Connection |
| :--- | :---: | :--- |
| **Arduino Uno R3 / Nano** | 1 | ATmega328P 8-bit MCU @ 16 MHz |
| **16x2 Character LCD** | 1 | Parallel interface (RS=2, EN=3, D4=5, D5=6, D6=7, D7=8) |
| **4x4 Membrane Keypad** | 1 | Matrix scanning (Rows: A0-A3, Cols: A4, A5, 9, 10) |
| **10kΩ Potentiometer** | 1 | Contrast adjustment for LCD Pin 3 (V0) |
| **220Ω Resistor** | 1 | Current limiting for LCD Backlight Anode (Pin 15) |

---

## Circuit Schematic & Pin Mapping

### 1. 16x2 LCD Interface (4-Bit Parallel Mode)
```
  Arduino Pin      LCD Module Pin (HD44780)
  -----------------------------------------
  5V         --->  Pin 2 (VDD) & Pin 15 (Backlight Anode via 220Ω)
  GND        --->  Pin 1 (VSS), Pin 5 (R/W), Pin 16 (Backlight Cathode)
  Pot Center --->  Pin 3 (V0 - Contrast Adjust)
  Digital 2  --->  Pin 4 (RS - Register Select)
  Digital 3  --->  Pin 6 (EN - Enable)
  Digital 5  --->  Pin 11 (D4 - Data Bit 4)
  Digital 6  --->  Pin 12 (D5 - Data Bit 5)
  Digital 7  --->  Pin 13 (D6 - Data Bit 6)
  Digital 8  --->  Pin 14 (D7 - Data Bit 7)
```

### 2. 4x4 Matrix Keypad Interface
```
  Keypad Matrix:
  [1] [2] [3] [+]   ---> Row 0 (Arduino A0)
  [4] [5] [6] [-]   ---> Row 1 (Arduino A1)
  [7] [8] [9] [*]   ---> Row 2 (Arduino A2)
  [C] [0] [=] [/]   ---> Row 3 (Arduino A3)
   |   |   |   |
  Col0 Col1 Col2 Col3
  (A4) (A5) (D9) (D10)
```

---

## Firmware Architecture

The firmware utilizes an event-driven loop structure:
- **`Keypad.h`**: Scans the 4x4 matrix using row output pulling and column input reading with hardware debouncing.
- **`LiquidCrystal.h`**: Sends 4-bit nibble commands and characters to the LCD controller.
- **Calculator State Machine**:
  - `input`: Accumulates user numeric keystrokes as a string buffer.
  - `currentResult`: Holds the running floating-point accumulator value.
  - `lastOperator`: Tracks active operator (`+`, `-`, `*`, `/`) for algebraic evaluation order.
  - `calculate(a, b, op)`: Evaluates floating-point expressions and returns `NAN` on zero division.
  - `resetCalc()`: Clears the display and restores accumulator state upon pressing `C`.

---

## Installation & Deployment

1. Install the official Arduino IDE or Arduino CLI.
2. Install the required libraries via the Arduino Library Manager:
   - `LiquidCrystal` (by Arduino)
   - `Keypad` (by Mark Stanley, Alexander Brevig)
3. Connect the Arduino Uno via USB.
4. Select board **Arduino Uno** and your active COM port.
5. Open `arduino_lcd_calculator.ino` and click **Upload** (or `Ctrl+U`).

---

## Author & License

- **Developer:** Hossam Ahmed ([@HossamAhmedSoft](https://github.com/HossamAhmedSoft))
- **License:** MIT
