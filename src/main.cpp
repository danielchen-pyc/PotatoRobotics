#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <sstream>
#include <cmath>

using namespace std;

void runmotor(int g);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTOR_A PA_0
#define MOTOR_B PA_3
#define LIGHT_SENSOR PA5
#define SETCONTROL PB10
#define PWMFREQ 2000 
#define P_CONTROL PA4
#define D_CONTROL PB0
#define GAIN 5

#define SET_POINT 270
#define SLOPEINT 15
#define MIN_ADJUST 24

int kp, kd, slope;
int lasterror = SET_POINT;
int errorlist[SLOPEINT], error;
int p, d, g;

// Record PD: 738, 18


void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(2000);

  // Set up Pins Here
  pinMode(P_CONTROL, INPUT);
  pinMode(D_CONTROL, INPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(SETCONTROL, INPUT_PULLDOWN);

  pinMode(PA0, OUTPUT);
  pinMode(PA3, OUTPUT);

  pwm_stop(MOTOR_A);
  pwm_stop(MOTOR_B);

  // Displays "Hello world!" on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Setup Successful!");
  display.display();
  delay(100);
  // attachInterrupt(digitalPinToInterrupt(PA0), handle_interrupt, RISING);
}

void loop()
{
  int light_volt = analogRead(PA5);
  if (light_volt > 500) {
    light_volt = 500;
  }
  display.clearDisplay();
  display.setCursor(0, 0);

  error = SET_POINT - light_volt;
  errorlist[0] = error - lasterror;
  slope = 0;
  for (int k = SLOPEINT - 1; k >= 1; k--) {
    errorlist[k] = errorlist[k-1];
    slope += errorlist[k] / SLOPEINT;
  }
  p = error * kp;
  d = slope * kd;
  g = (p + d) / 1000;
  lasterror = error;

  if (g >= 0) {
    g += MIN_ADJUST;
  }
  if (g < 0) {
    g -= MIN_ADJUST;
  }

  if (g > 80) {
    g = 80;
  }
  if (g < -80) {
    g = -80;
  }

  runmotor(g);
  
  // else {
  //   pwm_stop(MOTOR_A);
  //   pwm_stop(aMOTOR_B);
  // }
  
  display.setCursor(0, 0);
  display.println(light_volt);
  display.setCursor(0, 10);
  display.println(g);
  display.setCursor(0, 20);
  display.print("Slope: ");
  display.print(slope);
  display.setCursor(80, 20);
  display.print("D: ");
  display.println(d);
  display.setCursor(0, 30);
  display.print("P: ");
  display.println(p);
  display.display();
  // delay(500);

  while ((int) digitalRead(SETCONTROL)){
    runmotor(0);
    display.clearDisplay();
    kp = (int) GAIN * analogRead(P_CONTROL)/10.0;
    kd = (int) GAIN * analogRead(D_CONTROL)/10.0;
    display.setCursor(0, 0);
    display.print("KP: ");
    display.println(kp);
    display.setCursor(0, 10);
    display.print("KD: ");
    display.println(kd);
    display.setCursor(0, 20);
    display.print("G: ");
    display.println(g);
    display.setCursor(0, 30);
    display.print("Error: ");
    display.println(error);
    display.display();
  }
}

void runmotor(int g) {
  if (g < 0) {
    pwm_start(MOTOR_B, PWMFREQ, 0, PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_A, PWMFREQ, abs(g), PERCENT_COMPARE_FORMAT);
  } else if (g >= 0) {
    pwm_start(MOTOR_A, PWMFREQ, 0, PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_B, PWMFREQ, abs(g), PERCENT_COMPARE_FORMAT);
  }
  if (g == 0) {
    pwm_start(MOTOR_A, PWMFREQ, 0, PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_B, PWMFREQ, 0, PERCENT_COMPARE_FORMAT);
  }
}