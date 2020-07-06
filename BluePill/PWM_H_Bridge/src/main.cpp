// Purpose: Output PWM from two pins to drive a motor in either direction
// by interfacing with an H-bridge

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define THRESHOLD 2048
#define DUTY_CYCLE 0.5
#define DUTY_CYCLE_CONVERSION 1024 // Accepted duty cycle values are 0-1024

#define PWM_PIN_1 PB_8
#define PWM_PIN_2 PB_9

// #define IR_SENSOR_PIN PA0
// #define P_VALUE_PIN PA1
// #define D_VALUE_PIN PA3

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET -1 // This display does not have a reset pin accessible

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // pinMode(IR_SENSOR_PIN, INPUT_ANALOG);
  // pinMode(P_VALUE_PIN, INPUT_ANALOG);
  pinMode(PWM_PIN_1, OUTPUT);
  pinMode(PWM_PIN_2, OUTPUT);

  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.setTextColor(SSD1306_WHITE);
  // display.setTextSize(2);
  pwm_start(PWM_PIN_2, 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(PWM_PIN_2, 512, floor(DUTY_CYCLE*DUTY_CYCLE_CONVERSION), RESOLUTION_10B_COMPARE_FORMAT);
 
  // display.display();
}

void loop() {
  // int i = analogRead(IR_SENSOR_PIN);
  // int j = analogRead(P_VALUE_PIN);
  // display.clearDisplay();
  // display.setCursor(0,0);
  // display.println(i);
  // display.println(j);
  // display.display();

  // pwm_start(PWM_PIN_2, 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
  // pwm_start(PWM_PIN_1, 512, floor(DUTY_CYCLE*DUTY_CYCLE_CONVERSION), RESOLUTION_10B_COMPARE_FORMAT);

  // delay(5000);
  
  // pwm_start(PWM_PIN_1, 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
  // pwm_start(PWM_PIN_2, 512, floor(DUTY_CYCLE*DUTY_CYCLE_CONVERSION), RESOLUTION_10B_COMPARE_FORMAT);
  
  // delay(5000);
}
