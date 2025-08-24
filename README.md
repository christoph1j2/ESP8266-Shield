# ESP8266 Environmental Monitoring Shield

A comprehensive IoT shield for ESP8266 (Wemos D1 R1/R2) that provides environmental monitoring capabilities with multiple sensors, visual indicators, and MQTT connectivity for remote data collection and monitoring.

## 🔋 Features

- **Environmental Sensing**: Temperature monitoring with DS18B20 sensor and light level detection with photoresistor
- **Visual Feedback**: 16-pixel WS2812 LED strip for data visualization and dual status LEDs
- **User Interface**: 16x2 I2C LCD display with rotary encoder navigation and tactile button control
- **Connectivity**: WiFi connectivity with MQTT protocol support for IoT integration
- **Modular Design**: Clean, modular codebase with custom shield library for easy integration and maintenance

## 🛠️ Hardware Components

| Component | Description | Pin Assignment |
|-----------|-------------|----------------|
| **DS18B20** | Waterproof temperature sensor | D0 (ONE_WIRE_BUS) |
| **WS2812** | 16-pixel addressable LED strip | D4 (LED_PIN) |
| **LCD 1602** | I2C 16x2 character display | I2C (SDA/SCL) |
| **Rotary Encoder** | Navigation input device | D6, D7 (ENCODER_PIN1/2) |
| **Push Button** | Menu toggle control | D5 (BUTTON_PIN) |
| **Photoresistor** | Light level sensor | A0 (LDR_PIN) |
| **Status LEDs** | System status indicators | D8, D3 (STATUS_LED_PIN1/2) |

## 📋 Technical Specifications

- **Microcontroller**: ESP8266 (Wemos D1 R1/R2)
- **Operating Voltage**: 3.3V
- **Temperature Range**: -55°C to +125°C (DS18B20)
- **Light Sensing**: 0-1023 ADC range
- **Display**: 16x2 LCD with I2C interface (0x27)
- **LEDs**: 16 individually addressable WS2812 RGB LEDs
- **Communication**: MQTT over WiFi

## 🚀 Quick Start

### Prerequisites

- Arduino IDE with ESP8266 board package
- Required libraries (included in `/shield/knihovny/`):
  - LiquidCrystal_I2C
  - Adafruit_NeoPixel
  - OneWire
  - DallasTemperature
  - ESP8266WiFi
  - PubSubClient

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/christoph1j2/ESP8266-Shield.git
   cd ESP8266-Shield
   ```

2. **Hardware Setup**:
   - Connect components according to the pin assignments above
   - Refer to `/dokumentace/schema/` for detailed wiring diagrams

3. **Software Configuration**:
   - Open `/shield/shield.ino` in Arduino IDE
   - Update WiFi credentials in the main sketch:
     ```cpp
     const char* ssid = "your_wifi_ssid";
     const char* password = "your_wifi_password";
     const char* mqtt_server = "your_mqtt_broker_ip";
     ```

4. **Upload to ESP8266**:
   - Select your ESP8266 board in Arduino IDE
   - Compile and upload the sketch

## 💡 Usage

### Menu Navigation

The shield features an intuitive menu system:

- **Button Press**: Toggle between menu and measurement mode
- **Encoder**: Navigate between menu options
- **Menu Options**:
  - Measure Light: Display light levels with LED visualization
  - Measure Temperature: Show temperature readings with color-coded LEDs

### LED Visualization

- **Light Measurement**: LED strip displays light intensity (0-8 LEDs per side)
- **Temperature Measurement**: Color-coded temperature indication
- **Status LEDs**: System status and menu state indicators

### MQTT Integration

The shield automatically publishes sensor data to configured MQTT topics for integration with home automation systems, IoT platforms, or data logging services.

## 📁 Project Structure

```
ESP8266-Shield/
├── shield/                    # Main Arduino project
│   ├── shield.ino            # Main sketch file
│   └── knihovny/             # Required libraries
│       └── LeschkaShield/    # Custom shield library
├── dokumentace/              # Documentation
│   ├── fotky/               # Project photos
│   ├── schema/              # Wiring diagrams
│   ├── design/              # Design files
│   └── video/               # Demo videos
└── soubory/                 # Component reference images
```

## 🔧 API Reference

The `LeschkaShield` library provides a clean interface for all shield functionality:

### Core Functions
- `setupStatusLEDs()` - Initialize status LEDs
- `setupLCD()` - Initialize LCD display
- `setupLEDStrip()` - Initialize WS2812 LED strip
- `setupTemperatureSensor()` - Initialize DS18B20 sensor
- `setupButton()` - Initialize push button

### Sensor Reading
- `readTemperature()` - Get temperature in Celsius
- `readLDR()` - Get light level (0-1023)
- `readEncoder()` - Get encoder state
- `readButton()` - Get button state

### Output Control
- `setStatusLEDs(led1, led2)` - Control status LEDs
- `setLEDsForLight(value)` - Visualize light data
- `setLEDsForTemperature(temp)` - Visualize temperature data

## 🤝 Contributing

This project demonstrates professional IoT development practices and modular code architecture. Contributions are welcome for:

- Additional sensor integrations
- Enhanced data visualization
- Protocol extensions (CoAP, HTTP)
- Mobile app integration
- Web dashboard development

## 📄 License

This project is available for educational and commercial use. Please refer to individual library licenses for third-party components.

## 📸 Gallery

### Completed Project
- [Assembly Photo 1](dokumentace/fotky/20240805_180028.jpg) - Detailed view of the completed shield
- [Assembly Photo 2](dokumentace/fotky/20240805_180036.jpg) - Alternative angle showing component placement
- [Project Overview](dokumentace/fotky/Snapchat-1074486183.jpg) - Full system demonstration

### Component References
The `/soubory/` directory contains reference images for all major components including wiring diagrams for the I2C LCD display, DS18B20 temperature sensor, and component specifications for the encoder, WS2812 LED strip, and shield options.

---

*Developed with focus on clean architecture, modularity, and professional IoT development practices.*
