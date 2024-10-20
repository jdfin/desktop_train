#include <Arduino.h>

const int led_blink = LED_BUILTIN;

void setup()
{
  pinMode(led_blink, OUTPUT);
  digitalWrite(led_blink, 0);
}

void loop()
{
  digitalWrite(led_blink, 1);
  delay(100);
  digitalWrite(led_blink, 0);
  delay(900);
}
