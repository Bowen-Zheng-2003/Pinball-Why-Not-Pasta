#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#include <LiquidCrystal.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9
// CS pin is used for software or hardware SPI
#define CAP1188_CS  10
// These are defined for software SPI, for hardware SPI, check your 
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13
#define CAP1188_SENSITIVITY 0x1F

// Use I2C, no reset pin!
Adafruit_CAP1188 cap = Adafruit_CAP1188();

long points = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("YOUR SCORE IS:");
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");

  // Handles the sensitivity of the touch sensors
  cap.writeRegister(CAP1188_SENSITIVITY, 0x4F);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  boolean wait = false; // this is needed to keep scoring consistent
  // that way, if the ball stays too long on pressure plate, it won't keep adding points
  
  uint8_t touched = cap.touched();

  Serial.println(touched);

  if (touched == 0) {
    // No touch detected
    return;
  }
  
  for (uint8_t i=0; i<8; i++) {
    // if the red wire is touched, start over
    if(touched == 1){

      // need this to clear the whole second row or else lcd looks ugly
      for(int i = 0; i < 16; i++){
          lcd.setCursor(i, 1);
          lcd.print(" ");
      }
      lcd.setCursor(0, 1);
      points = 0;
      lcd.print(points);
    }
    
    // if the green wire is touched, increment by 10 points (this is C3)
    else if(touched == 4){
      lcd.setCursor(0, 1);
      points += 10;
      lcd.print(points);
      wait = true;
      break;
    }
    
    // if the black wire is touched, increment by 20 points
    else if(touched == 16){
      lcd.setCursor(0, 1);
      points += 20;
      lcd.print(points);
      wait = true;
      break;
    }
    
    // if the blue wire is touched, increment by 30 points
    else if(touched == 64){
      lcd.setCursor(0, 1);
      points += 30;
      lcd.print(points);
      wait = true;
      break;
    }
    
  }

  if(wait){ // stops the game for 5 seconds
    delay(5000);
  }
  
}
