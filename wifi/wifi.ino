#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"
#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 2
#define BRIGHTNESS 55
bool isOn = true;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;


// Adresse IP fixe
IPAddress local_IP(192, 168, 0, 200);      // Adresse IP fixe 
IPAddress gateway(192, 168, 0, 1);         // IP de la box
IPAddress subnet(255, 255, 255, 0);        // Masque de sous-réseau
IPAddress primaryDNS(8, 8, 8, 8);          // DNS (optionnel)
IPAddress secondaryDNS(8, 8, 4, 4);        // DNS (optionnel)

const int LedBleuPin = 2;
WebServer server(80);

void connectToWiFi() {
  // Configuration IP statique
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Erreur config IP statique !");
  }

  Serial.print("Connexion à ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void handleLedOn() {
  digitalWrite(LedBleuPin, HIGH);
  isOn = true;
  server.send(200, "text/plain", "LED BLEUE ON");
}

void handleLedOff() {
  digitalWrite(LedBleuPin, LOW);
  isOn = false;
  FastLED.clear();      // éteint les LEDs RGB
  FastLED.show();
  server.send(200, "text/plain", "LED BLEUE OFF");
}

void handleNotFound() {
  server.send(404, "text/plain", "Commande inconnue");
}

void setup() {
  Serial.begin(115200);
  pinMode(LedBleuPin, OUTPUT);
  digitalWrite(LedBleuPin, LOW);

  connectToWiFi();

  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Serveur HTTP lancé !");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  server.handleClient();
    if (isOn) {
      for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(gHue + i * 30, 255, 255);
      FastLED.show();
      delay(150);
      leds[i] = CRGB::Black;
    }
    gHue += 10;
  }
}

