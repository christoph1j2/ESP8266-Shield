#include "LeschkaShield.h"

// objekty
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupStatusLEDs() {
  pinMode(STATUS_LED_PIN1, OUTPUT);
  pinMode(STATUS_LED_PIN2, OUTPUT);
}

void setStatusLEDs(bool led1State, bool led2State) {
  digitalWrite(STATUS_LED_PIN1, led1State ? HIGH : LOW);
  digitalWrite(STATUS_LED_PIN2, led2State ? HIGH : LOW);
}

void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.print("...");
  delay(2000);
  lcd.clear();
}

int readEncoder() {
  // čteme jen encoderpin1, jelikož nepotřebujeme jinou hodnotu než 1 nebo 0
  return digitalRead(ENCODER_PIN1);
}

void setupLEDStrip() {
  strip.begin();
  strip.show();
}

void clearLEDStrip() {
  strip.clear();
  strip.show();
}

void setLEDsForLight(int value) {
  // pro měření LDR namapujeme hodnotu od 0 do 1023, od nulté do osmé LED na každé pásce
  int numLEDs = map(value, 0, 1023, 0, 8);

    uint32_t color = strip.Color(64, 53, 0); // Reduced brightness

    for (int i = 0; i < 8; i++) {
        strip.setPixelColor(i, (i < numLEDs) ? color : strip.Color(0, 0, 0));
        strip.setPixelColor(i + 8, (i < numLEDs) ? color : strip.Color(0, 0, 0));
    }
    strip.show();
}

void setLEDsForTemperature(float temp) {
  // pro měření teploty napamujeme hodnotu od -10 do 70, abychom mohli vizuálně vidět nějakou změnu na páskách
  int numLEDs = map(temp, -10, 70, 0, 8);
  uint32_t color = strip.Color(0, 0, 0);

  // logika pro barvu LED
  if (numLEDs <= 2) {
    // svítí-li dvě či méně (nízká teplota), bude barva modrá
    color = strip.Color(0, 64, 64);  // modrá
  } else if (numLEDs <= 6) {
    // svítí-li šest či méně (normální teplota), bude barva zelená
    color = strip.Color(0, 64, 0);  // zelená
  } else {
    // jinak červená (vysoká teplota)
    color = strip.Color(64, 0, 0);  // červená
  }

  for (int i = 0; i < 8; i++) {
    // obě pásky nezávisle na sobě se rozsvicují podle teploty
    strip.setPixelColor(i, (i < numLEDs) ? color : strip.Color(0, 0, 0));
    strip.setPixelColor(i + 8, (i < numLEDs) ? color : strip.Color(0, 0, 0));
  }
  strip.show();
}

void setupTemperatureSensor() {
  sensors.begin();
}

float readTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void setupButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// https://docs.arduino.cc/built-in-examples/digital/Debounce/
bool readButton() {
  static bool buttonPressed = false;
  static bool buttonLastState = HIGH;
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;

  // načti status tlačítka do lokální proměnné
  bool reading = digitalRead(BUTTON_PIN);

  // Pokud se tlačítko změnilo kvůli noise nebo stlačení:
  if (reading != buttonLastState) {
    // Resetuj debounce timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // na jakékoliv hodnotě je proměnná reading, byla tam déle než debounce delay
    // takže brát toto jako reálný aktuální stav

    // pokud se status tlačítka změnil:
    if (reading != buttonPressed) {
      buttonPressed = reading;

      // pošli true jen když nový status tlačítka je LOW
      if (buttonPressed == LOW) {
        buttonLastState = reading;
        return true;
      }
    }
  }

  // uložit hodnotu, příště se využije jako poslední status tlačítka
  buttonLastState = reading;
  return false;
}

int readLDR() {
  return analogRead(LDR_PIN);
}

// MQTT

/* ssid = "3301-IoT";
password = "mikrobus";
mqtt_server = "10.202.31.211"; */

void setup_wifi(){
  delay(10);

  // Připojení k WiFi
  Serial.println();
  Serial.print("Připojování k ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // loop než se znovupřipojení zdaří
  while(!client.connected()){
    Serial.print("Pokus o MQTT připojení...");
    //náhodný clientID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xfff), HEX);
    //pokus o připojení
    if(client.connect(clientId.c_str())){
      Serial.println("connected");
      //po připojení vydat announcement
      client.publish("4hs2/laces/ESP", "hello world");
      //...a znovu subscribnout
      //???
      client.subscribe("4hs2/laces/ESP/LED");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" zkus to znova za 5 vterin");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Zpráva přišla [");
  Serial.print(topic);
  Serial.print("] ");
  for(int i = 0; i<length;i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if((char)payload[0]=='1'){
    digitalWrite(BUILTIN_LED,LOW);
  }
  else {
    digitalWrite(BUILTIN_LED,HIGH);
  }
}