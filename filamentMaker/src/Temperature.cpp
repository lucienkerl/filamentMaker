//
// Created by lucienkerl on 05.08.22.
//

#include "Temperature.h"
#include <Arduino.h>

int sensorPin = A0;
int bitwertNTC = 0;
long widerstand1=100000;                   //Ohm
int bWert =3950;                           // B- Wert vom NTC
double widerstandNTC =0;
double kelvintemp = 273.15;                // 0°Celsius in Kelvin
double Tn=kelvintemp + 25;                 //Nenntemperatur in Kelvin
double TKelvin = 0;                        //Die errechnete Isttemperatur
double T = 0;                              //Die errechnete Isttemperatur
unsigned long lastTempMillis = 0;

void Temperature::loop() {
    if (millis() > lastTempMillis + 1000){
        Serial.println("Sensormessung:  ");
        bitwertNTC = analogRead(sensorPin);      // lese Analogwert an A0 aus
        widerstandNTC = widerstand1 * (((double) bitwertNTC / 1024) / (1 - ((double) bitwertNTC / 1024)));

        // berechne den Widerstandswert vom NTC
        TKelvin = 1 / ((1 / Tn) + ((double) 1 / bWert) * log((double) widerstandNTC / widerstand1));

        // ermittle die Temperatur in Kelvin
        T = TKelvin - kelvintemp;                    // ermittle die Temperatur in °C

        Serial.println("Analog: ");              //
        Serial.println(bitwertNTC);              //
        Serial.println("NTC- Widerstand: ");     //Gebe die ermittelten Werte aus

        Serial.println(widerstandNTC);           //
        Serial.println("Temperatur: ");          //Gebe die ermittelten Werte aus
        Serial.println(T);
        lastTempMillis = millis();
    }
}
