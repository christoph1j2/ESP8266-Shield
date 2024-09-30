#include "LeschkaShield.h"

void buttonPress(bool& inMenu, int& menuIndex){
    Serial.println("Button pressed");
    inMenu = !inMenu;
    lcd.clear();
    if (inMenu) {
      clearLEDStrip();
    }
}

void displayMenu(int menuIndex) {
  int encoderValue = readEncoder();
  Serial.print("Encoder value: ");
  Serial.println(encoderValue);
  clearLEDStrip();
  setStatusLEDs(true, false);

  if (encoderValue != -1) {
    menuIndex = encoderValue % 2;

    if (menuIndex == 0) {
      lcd.setCursor(0, 0);
      lcd.print(">Measure Light");
      lcd.setCursor(0, 1);
      lcd.print(" Measure Temp ");
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" Measure Light ");
      lcd.setCursor(0, 1);
      lcd.print(">Measure Temp");
    }
  }
}

void menuSelection(int menuIndex){
    int encoderValue = readEncoder();
    if (encoderValue != -1) {
      menuIndex = encoderValue % 2;
    }
    setStatusLEDs(true, true);
    if (menuIndex == 0) {
      measureLight();
    } else {
      measureTemp();
    }
}

void measureLight(){
      int lightValue = readLDR();
      lcd.setCursor(0, 0);
      lcd.print("Light: ");
      lcd.print(lightValue);
      lcd.print("   ");
      setLEDsForLight(lightValue);
      Serial.print("Light value: ");
      Serial.println(lightValue);
}

void measureTemp(){
      float tempValue = readTemperature();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(tempValue);
      lcd.print((char)223);
      lcd.print("C");
      lcd.print("   ");
      setLEDsForTemperature(tempValue);
      Serial.print("Temp value: ");
      Serial.println(tempValue);
}

void setup() {
  Serial.begin(115200);

  // zavolá setup metody z knihovny LeschkaShield.h
  setupStatusLEDs();
  setupLCD();
  setupButton();
  setupLEDStrip();
  setupTemperatureSensor();
}

void loop() {
  static int menuIndex = 0;
  static bool inMenu = true;

  if (readButton()) {
    buttonPress(inMenu,menuIndex);
  }

  if (inMenu) {
    displayMenu(menuIndex);
  } else {
    menuSelection(menuIndex);
  }
}
