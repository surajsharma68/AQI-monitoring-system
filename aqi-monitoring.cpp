#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define pins
#define DHTPIN 4        // DHT11 data pin
#define DHTTYPE DHT11
#define MQ135PIN 34     // MQ135 analog pin

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// WiFi credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";

// ThingSpeak settings
String apiKey = "THINGSPEAK_API_KEY";
const char* server = "api.thingspeak.com";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    delay(10);

    dht.begin();
    pinMode(MQ135PIN, INPUT);

    // Initialize OLED display
    if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi.");
}

void loop() {
    // Read humidity and temperature from DHT11
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Read MQ135 value
    int mq135Value = analogRead(MQ135PIN);


    float voltage = mq135Value * (5.0 / 4095.0);
    float aqi = voltage * 100;

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("Air Quality (AQI): ");
    Serial.print(aqi);
    Serial.println();

    // Display data on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(t);
    display.println(" *C");
    display.print("Humidity: ");
    display.print(h);
    display.println(" %");
    display.print("Air Quality: ");
    display.print(aqi);
    display.println(" AQI");
    display.display();

    // Send data to ThingSpeak
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String url = String("http://") + server + "/update?api_key=" + apiKey + "&field1=" + String(t) + "&field2=" + String(h) + "&field3=" + String(aqi);
        http.begin(url.c_str());

        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.println("Error in HTTP request");
        }
        http.end();
    } else {
        Serial.println("WiFi not connected");
    }

    delay(20000); // ThingSpeak rate limit (every 15 seconds)
}
