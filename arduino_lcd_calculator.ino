#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD Pins
const int rs = 2, en = 3, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 9, 10};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables
String input = "";
float currentResult = 0;
char lastOperator = 0;
bool firstInput = true;
bool justEvaluated = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Calc Ready");
  delay(1500);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    // Reset calculator
    if (key == 'C') {
      resetCalc();
    }

    // If number is pressed
    else if ((key >= '0' && key <= '9') || key == '.') {
      if (justEvaluated) {
        resetCalc();
      }
      input += key;
      lcd.print(key);
    }

    // If operator is pressed
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (input != "") {
        float num = input.toFloat();
        if (firstInput) {
          currentResult = num;
          firstInput = false;
        } else {
          currentResult = calculate(currentResult, num, lastOperator);
        }
        lastOperator = key;
        input = "";
        lcd.print(key);
        justEvaluated = false;
      }
    }

    // When "=" is pressed
    else if (key == '=') {
      if (input != "") {
        float num = input.toFloat();
        currentResult = calculate(currentResult, num, lastOperator);
        lcd.print('=');
        lcd.setCursor(0, 1);
        lcd.print(currentResult);
        input = "";
        justEvaluated = true;
      }
    }
  }
}

float calculate(float a, float b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return (b != 0) ? a / b : NAN;
    default: return b;
  }
}

void resetCalc() {
  lcd.clear();
  input = "";
  currentResult = 0;
  lastOperator = 0;
  firstInput = true;
  justEvaluated = false;
}
