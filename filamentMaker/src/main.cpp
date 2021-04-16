#include <Arduino.h>

// Pin Declarations
int dataIn = 11;
int clockIn = 12;

// Variables
int clockVar = 1;
int lastClock = 1;
unsigned long timeVar = 0;
unsigned long timeVarStart = 0;
int out = 0;

void setup()
{
  // Pin Set Up
  pinMode(dataIn, INPUT);
  pinMode(clockIn, INPUT);

  Serial.begin(115200);
  Serial.println("Ready: ");
}

int analogReadToDigital()
{
  return analogRead(dataIn) < 820 ? 0 : 1; // If analog read is below 4V = Digital Low
}

void loop()
{
  return;
  lastClock = clockVar;
  if (analogRead(clockIn) < 820) // If analog read is below 4V = Digital Low
  {
    clockVar = 0;
  }
  else
  {
    clockVar = 1;
  }

  if (lastClock == 1 && clockVar == 0)
  {
    out = analogReadToDigital() + analogReadToDigital() + analogReadToDigital(); // Tripple sampling to remove glitches
    if ((micros() - timeVar) > 800)
    {
      Serial.println(" ");
    }
    else if ((micros() - timeVar) > 400)
    {
      Serial.print("  ");
    }

    if (out > 1)
    {
      Serial.print("1");
    }
    else
    {
      Serial.print("0");
    }
    Serial.print(",");
    timeVar = micros();
  }
}
