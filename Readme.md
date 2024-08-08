AQI and Climate Monitoring System
Overview
This project features an AQI and climate monitoring system built using an ESP32 microcontroller, MQ135 air quality sensor, DHT11 temperature and humidity sensor, and a 128x64 OLED display. The system reads environmental data, displays it on the OLED screen, and uploads it to ThingSpeak for remote monitoring and analysis. Calibration ensures accurate readings, adhering to basic standards.

Features
Real-time temperature, humidity, and AQI monitoring
OLED display for local data visualization
WiFi connectivity for data upload to ThingSpeak
Calibration for accurate sensor readings
Components
ESP32
MQ135 air quality sensor
DHT11 temperature and humidity sensor
128x64 OLED display (SSD1306 driver)
Breadboard and jumper wires
Wiring
DHT11 Sensor
VCC to 3.3V
GND to GND
Data to GPIO 4
MQ135 Sensor
VCC to 5V
GND to GND
AOUT to GPIO 34 (ADC)
OLED Display
VCC to 3.3V
GND to GND
SDA to GPIO 21
SCL to GPIO 22
Libraries
The following libraries are required for this project:

WiFi.h (for ESP32 WiFi)
HTTPClient.h (for ThingSpeak integration)
DHT.h (for DHT11 sensor)
Adafruit_Sensor.h (required for DHT library)
Adafruit_GFX.h (for OLED display)
Adafruit_SSD1306.h (for OLED display)
Setup
Clone the repository:

bash
Copy code
git clone https://github.com/yourusername/aqi-climate-monitoring-system.git
Open the project in your Arduino IDE.

Install the required libraries via the Arduino Library Manager or the Library Manager in PlatformIO.

Replace the placeholders in the code with your WiFi credentials and ThingSpeak API key.

Upload the code to your ESP32.
