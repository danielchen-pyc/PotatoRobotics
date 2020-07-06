// Purpose: Control a servo motor using an analog input

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // This display does not have a reset pin accessible
#define SERVO_PIN PA8     // Pin that servo attaches to on BluePill
#define TRIG_PIN PB3
#define ECHO_PIN PB4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servo;
double dist;

void setup() {
  servo.attach(SERVO_PIN);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
 
  display.display();
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  dist = pulseIn(ECHO_PIN, HIGH) / 2 * 0.0330;
  
  // if (dist < 9) {
  //   servo.write(0);
  //   delay(1000);
  // } else {
  //   servo.write(180);
  // }

  display.clearDisplay();
  display.setCursor(0,0);
  display.println(dist);
  display.display();
}
