#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED pins
#define OLED_DC 6
#define OLED_CS 5
#define OLED_RESET 7

// SPI pins
#define OLED_SCK 2
#define OLED_MOSI 4

// DHT22
#define DHTPIN 3
#define DHTTYPE DHT22

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &SPI,
  OLED_DC,
  OLED_RESET,
  OLED_CS
);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Start SPI
  SPI.begin(OLED_SCK, -1, OLED_MOSI, OLED_CS);

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("SSD1306 allocation failed");
    for (;;) {
    }
  }

  // Start DHT22
  dht.begin();

  // Initial OLED screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();

  delay(2000);
}

void loop() {
  // Read DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("DHT22 Error!");
    display.display();

    delay(2000);
    return;
  }

  // Serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C    Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // OLED
  display.clearDisplay();

  display.setTextSize(2);

  display.setCursor(0, 0);
  display.print("Temp:");
  display.setCursor(0, 20);
  display.print(temperature, 1);
  display.print(" C");

  display.setCursor(0, 43);
  display.print("Hum:");
  display.print(humidity, 1);
  display.print("%");

  display.display();

  delay(2000);
}