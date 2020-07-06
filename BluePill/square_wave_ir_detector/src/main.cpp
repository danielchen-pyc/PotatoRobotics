// Purpose: Detect the presence of a particular frequency of IR light
// by reading an analog voltage from a phototransistor and using frequency
// analysis methods

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define THRESHOLD 0.05 * 1023 / 3.3
#define SENSOR PA0
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int i;
double prev, curr, freq;
int time0, deltaTime;

void setup() {
  pinMode(SENSOR, INPUT_ANALOG);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();

  curr = analogRead(SENSOR);
  i = 0;
  time0 = getCurrentMillis();
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);

  // Read new value from sensor
  prev = curr;
  curr = analogRead(SENSOR);

  // Count zero crossings
  if (curr > THRESHOLD && prev < THRESHOLD) {
    i++;
  }
  
  deltaTime = getCurrentMillis() - time0;
  if (deltaTime % 1000 == 0) {
    freq = i;
    i = 0;
    display.println("Freq: ");
    display.println(freq);
    display.display();
  }

  // display.println(i);
  // display.setCursor(0,15);
}
