// Bibliotheque pour l'ecran oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include "TomThumb.h"

// Bibliotheque pour la sonde DHT
#include "DHT.h"

// Define pour l'oled
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

// Define pour la sonde DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
  Serial.begin(115200);
  Serial.print("Lecture de la sonde:");

  dht.begin();
}

void loop() {
  // Attente avant mesure
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  // test lecture dht11
  if (isnan(h) || isnan(t)) {
    Serial.println("Impossible de lire la sonde DHT!");
    return;
  }

  // Affichage sur le port série
  Serial.print("Humidity: ");Serial.print(h);Serial.print(" %  ");
  Serial.print("Temperature: ");Serial.print(t);Serial.println("°");
  
  // Effacer l'écran
  display.clearDisplay();
  
  // Affichage avec la police d'origine
  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print(t);display.print("\xA7");display.print(" ");display.print(h);display.print("%");
  
  // Affichage avec la police TomThumb
  display.setFont(&TomThumb);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,47);
  display.print(t);display.print("\xB0");display.print(" ");display.print(h);display.print("%");
  display.display();
}
