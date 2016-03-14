#include <gfxfont.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13



#define ZERO_LVDT 0
#define SLOPE_LVDT 6


Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int CAP_DISCHARGE = 4;
const int SENSOR_OUT = A0;

int zero = 124;     //initially hardcoded
float slope = 4.7;     //initially hardcoded

void setup() {
  pinMode(CAP_DISCHARGE, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
  pinMode(ZERO_LVDT, INPUT_PULLUP);
  pinMode(SLOPE_LVDT, INPUT_PULLUP);
  
  //display setup
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

//use for displaying values
void displayLoop(int val, int zero_val, int slope_val) {
  display.clearDisplay();
  
  display.setCursor(0,0);
  display.println("LVDT SENSOR!!!!1!!");
  
  display.setCursor(0,10);
  display.print("Dist (mm): ");
  
  display.setCursor(63,10);
  display.print((val - zero_val) / slope); 
  
  display.setCursor(0, 20);
  display.println("Raw Reading:");
  display.setCursor(70,20);
  display.println(val);
  display.display();
  
}

void loop() {
  
  if (digitalRead(ZERO_LVDT) == LOW){
    delay(500);
    zero = analogRead(SENSOR_OUT);
  }
    

  if (digitalRead(SLOPE_LVDT) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("READING FROM 50mm!!!!!1!");
    delay(500);
    slope = (analogRead(SENSOR_OUT) * 1.0 - zero) / 50.0;
  }
  
  displayLoop(analogRead(SENSOR_OUT), zero, slope);  //read value and display
  //clear capacitor
  digitalWrite(CAP_DISCHARGE, HIGH);
  delay(50);
  digitalWrite(CAP_DISCHARGE, LOW);
  delay(500);

}
