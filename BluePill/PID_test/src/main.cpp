// Purpose: Use PID to control a motor in a negative feedback loop

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define DUTY_CYCLE 0.5
#define DUTY_CYCLE_CONVERSION 1024 // Accepted duty cycle values are 0-1024

#define PWM_PIN_1 PB_8
#define PWM_PIN_2 PB_9

#define IR_SENSOR_PIN PA0
#define P_VALUE_PIN PA1
#define D_VALUE_PIN PA2
#define SET_POINT_PIN PA3

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // This display does not have a reset pin accessible

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int P = 0;
int D = 0;
int setPoint = 10;
int IR_reading = 3;
int lastError = 0;
int prp, drv, error, adjust;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT_ANALOG);
  pinMode(P_VALUE_PIN, INPUT_ANALOG);
  pinMode(D_VALUE_PIN, INPUT_ANALOG);
  pinMode(SET_POINT_PIN, INPUT_ANALOG);
  pinMode(PWM_PIN_1, OUTPUT);
  pinMode(PWM_PIN_2, OUTPUT);

  P = analogRead(P_VALUE_PIN);
  D = analogRead(D_VALUE_PIN);
  setPoint = analogRead(SET_POINT_PIN);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("P:");
  display.setCursor(60,0);
  display.println(P);
  display.setCursor(0,20);
  display.print("D:");
  display.setCursor(60,20);
  display.println(D);
  display.setCursor(0,40);
  display.print("Set:");
  display.setCursor(60,40);
  display.println(setPoint);
  display.display();
}

void loop() {
  // P = analogRead(P_VALUE_PIN) / 10;
  // D = analogRead(D_VALUE_PIN) / 10;
  // setPoint = analogRead(SET_POINT_PIN);
  IR_reading = analogRead(IR_SENSOR_PIN);

  error = setPoint - IR_reading;
  prp   = P * error;
  drv   = D * (error - lastError);
  
  adjust = prp + drv;
  lastError = error;

  // display.clearDisplay();
  // display.setCursor(0,0);
  // display.print("P:");
  // display.setCursor(60,0);
  // display.println(P);
  // display.setCursor(0,16);
  // display.print("D:");
  // display.setCursor(60,16);
  // display.println(D);
  // display.setCursor(0,32);
  // display.print("Set:");
  // display.setCursor(60,32);
  // display.println(setPoint);
  // display.setCursor(0,48);
  // display.print("IR:");
  // display.setCursor(60,48);
  // display.println(IR_reading);
  // display.display();

  if (adjust > 0) {
    pwm_start(PWM_PIN_2, 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(PWM_PIN_1, 512, floor(adjust*DUTY_CYCLE_CONVERSION), RESOLUTION_10B_COMPARE_FORMAT);
  } else {
    pwm_start(PWM_PIN_1, 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(PWM_PIN_2, 512, floor(adjust*DUTY_CYCLE_CONVERSION), RESOLUTION_10B_COMPARE_FORMAT);
  }
}
