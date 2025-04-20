#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"



// Adresse IP fixe
IPAddress local_IP(192, 168, 0, 200);      // Adresse IP fixe désirée
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
  server.send(200, "text/plain", "LED BLEUE ON");
}

void handleLedOff() {
  digitalWrite(LedBleuPin, LOW);
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
}

void loop() {
  server.handleClient();
}
