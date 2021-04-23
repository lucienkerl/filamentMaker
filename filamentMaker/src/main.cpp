#include <Arduino.h>
/*
  (c)2018 Pawel A. Hernik
  YouTube video:
  https://youtu.be/RIt08GJH2IA
*/

/*
   Cheap digital caliper pinout (from top left):
   #1 - GND (black)
   #2 - DAT (green)
   #3 - CLK (blue)
   #4 - VCC 1.5-1.8V (red)
 */
#define CLOCK_PIN D1
#define DATA_PIN D2

unsigned long tempmicros = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(CLOCK_PIN, INPUT_PULLDOWN_16);
  pinMode(DATA_PIN, INPUT_PULLDOWN_16);
  Serial.print("Ready:");
  delay(100);
}

float decode()
{
  int sign = 1;
  long value = 0;

  for (int i = 0; i < 23; i++)
  {
    //wait until clock returns to LOW - the first bit is not needed
    while (digitalRead(CLOCK_PIN) == HIGH)
    {
    }

    //wait until clock returns to HIGH
    while (digitalRead(CLOCK_PIN) == LOW)
    {
    }

    if (digitalRead(DATA_PIN) == LOW)
    {
      if (i < 20)
      {
        value |= 1 << i;
      }
      if (i == 20)
      {
        sign = -1;
      }
    }
  }
  return (value * sign) / 100.00;
}

void loop()
{
  //wait until clock turns to LOW
  while (digitalRead(CLOCK_PIN) == HIGH)
  {
    delay(0);
  }

  tempmicros = micros();

  //wait for the end of the LOW pulse
  while (digitalRead(CLOCK_PIN) == LOW)
  {
    delay(0);
  }

  //if the LOW pulse was longer than 500 micros we are at the start of a new bit sequence
  if ((micros() - tempmicros) > 500)
  {
    float result = decode();

    //print measurments
    Serial.print("Lenght: ");
    Serial.println(result, 3);
  }
}