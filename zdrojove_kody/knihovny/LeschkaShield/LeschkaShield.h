#ifndef LESCHKASHIELD_H
#define LESCHKASHIELD_H

// Knihovny
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Konstanty
#define STATUS_LED_PIN1 D8
#define STATUS_LED_PIN2 D3
#define ENCODER_PIN1 D6
#define ENCODER_PIN2 D7
#define LED_PIN D4
#define NUMPIXELS 16
#define ONE_WIRE_BUS D0
#define BUTTON_PIN D5
#define LDR_PIN A0

// Inicializace objektů
extern LiquidCrystal_I2C lcd;
extern Adafruit_NeoPixel strip;
extern OneWire oneWire;
extern DallasTemperature sensors;

// deklarace funkcí
void setupStatusLEDs();
void setStatusLEDs(bool led1State, bool led2State);
void setupLCD();
int readEncoder();
void setupLEDStrip();
void clearLEDStrip();
void setLEDsForLight(int value);
void setLEDsForTemperature(float temp);
void setupTemperatureSensor();
float readTemperature();
void setupButton();
bool readButton();
int readLDR();

#endif

