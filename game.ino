
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Declare the input pin
int inPin = A1;
int val = 0;     // variable for reading the pin status
int buttonState = 0;         // current state of the button


byte rightArrow[8] = {
  B10000,
  B11000,
  B01100,
  B00110,
  B00011,
  B00110,
  B01100,
  B01000
};
byte leftArrow[8] = {
  B00001,
  B00011,
  B00110,
  B01100,
  B11000,
  B01100,
  B00110,
  B00011
};
byte man[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte hammerHead[8] = {
  B00011,
  B00111,
  B01111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00000
};
byte hammerBody[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, man);
  lcd.createChar(1, rightArrow);
  lcd.createChar(2, leftArrow);
  lcd.createChar(3, hammerHead);
  lcd.createChar(4, hammerBody);

  // set the cursor to the top left
  lcd.setCursor(0, 0);

  // Print a message to the lcd.
  lcd.write(byte(1));
  lcd.print("   Dr. ");
  lcd.write("Doom   "); // when calling lcd.write() '0' must be cast as a byte
  lcd.write(byte(2));
}

int start = 0;
int manPos = 0;
int prevPos = 1;

void loop() {

  displayGameStats();
  scrollEnemies();
  readButtonState();
}
void scrollEnemies() {
  //Scroll from pos 12to pos 0
  if (start == 1) {
    for (int i = 12 ; i >= 0 ; i--) {
      if (i == 0 ) {
        lcd.setCursor(0, 0);
        lcd.print(" ");
        //lcd.write(byte(3));// hammer head
      } else {
        lcd.setCursor(i - 1, 0);
        lcd.write(byte(3));// hammer head
      }
      lcd.setCursor(i, 0); // hammer body
      lcd.write(byte(4));

      if (i <= 10) {
        lcd.setCursor(i + 2, 0);
        lcd.print(" ");
        if (i == 1) {
          lcd.setCursor(i + 1, 0);
          lcd.print(" ");

        }
        if (i == 0) {
          lcd.setCursor(i + 1, 0);
          lcd.print(" ");
          lcd.setCursor(i, 0);
          lcd.print(" ");
        }
      }
      delay(400);
      readButtonState();
    }
  }
}
void displayGameStats() {
  if (start == 1) {
    //displayScore
    lcd.setCursor(13, 0);
    lcd.print("000");

    //displayLevel
    lcd.setCursor(13, 1);
    lcd.print("Lv1");
  }
}
void readButtonState() {
  buttonState = analogRead(inPin);

  if (buttonState == 1023 && start == 0) {
    lcd.clear();
    start = 1;
  }

  if (buttonState == 1023 && start == 1 && manPos != prevPos ) {

    if (manPos == 0) {
      //clear prev pos
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
      manPos = 1;
      prevPos = 0;
    } else {
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      manPos = 0;
      prevPos = 1;
    }
    delay(300);
  }
}
