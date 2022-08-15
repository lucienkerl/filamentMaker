#include <Arduino.h>
#include <AccelStepper.h>
#include "Network.h"
#include "Caliper.h"
#include "Temperature.h"

#define dirPin D4
#define stepPin D3
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup()
{
    Serial.begin(115200);
    Caliper::setup();
    Network::setup();

    Serial.print("Ready:");
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(20);
    delay(100);
}

void loop()
{
    Network::loop();
    Caliper::loop();
    Temperature::loop();
    stepper.runSpeed();
}