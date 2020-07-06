// Purpose: Measure the intensity of infrared light falling on a phototransistor
// and interpret the value as a voltage between 0V and 3.3V

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SENSOR PA0
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float v;

void setup() {
  pinMode(SENSOR, INPUT_ANALOG);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(1000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);

  v = analogRead(SENSOR) * 3.3 / 1023;

  display.println(v);
  display.display();
  delay(10);
};