#include <Arduino.h>
#include "DHTesp.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

DHTesp dht;

const int buttonPin = D3;

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  dht.setup(D4, DHTesp::DHT11); // Connect DHT sensor to GPIO 17

    // Configure button port
  pinMode(buttonPin,  INPUT_PULLUP);
//  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature() * 0.9;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("T = ");
  display.print(temperature,0);
  display.println(" C");
  display.setCursor(0,10);
  display.print("H = ");
  display.print(humidity,0);
  display.println(" %");
  display.display();

  int reading = digitalRead(buttonPin);
  if (reading == LOW) {
    Serial.println("PUSH!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  delay(2000);
}
