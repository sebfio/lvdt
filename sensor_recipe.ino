#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int CAP_DISCHARGE = 4;
const int SENSOR_OUT = A0;

void setup() {
  pinMode(CAP_DISCHARGE, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);

  //display setup
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

//use for displaying values
void displayLoop(int val) {
  display.clearDisplay();
  
  display.setCursor(0,0);
  display.println("LVDT Sensor");
  display.setCursor(0,20);
//  display.print("Dist (mm):");
  display.println("Voltage:");
  display.setCursor(70,20);
  display.println(val);
  display.display();
  
}

void loop() {
  
  displayLoop(analogRead(SENSOR_OUT));  //read value and display
  //clear capacitor
  digitalWrite(CAP_DISCHARGE, HIGH);
  delay(50);
  digitalWrite(CAP_DISCHARGE, LOW);
  delay(500);

}
