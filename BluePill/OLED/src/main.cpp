#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define INTERRUPT_PIN PB9
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int i = 0;

void handle_interrupt() {
  i++;
}

void handle_interrupt_schmitt();

void setup() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handle_interrupt, RISING);
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
  display.println(i);
  display.display();
  delay(10);
};