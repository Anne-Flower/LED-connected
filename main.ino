#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>

// === LED Setup ===
#define LED_PIN     5
#define NUM_LEDS    256
#define BRIGHTNESS  100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// === Wi-Fi Config ===
const char* ssid = "TON_SSID";
const char* password = "TON_MOT_DE_PASSE";

// === Web Server ===
AsyncWebServer server(80);

// === HTML Page ===
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head><meta charset="UTF-8"><title>LED On/Off</title></head>
  <body>
    <h2>LED Control</h2>
    <button onclick="setLED(1)">On</button>
    <button onclick="setLED(0)">Off</button>
    <script>
      function setLED(state) {
        fetch("/setState", {
          method: "POST",
          headers: { "Content-Type": "application/octet-stream" },
          body: new Uint8Array([state])
        });
      }
    </script>
  </body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // LED init
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // Wi-Fi connect
  Serial.printf("Connecting to %s...\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  // Route pour la page web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Route POST /setState
  server.on("/setState", HTTP_POST, [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t* data, size_t len, size_t index, size_t total){
      if (len >= 1) {
        if (data[0] == 1) {
          fill_solid(leds, NUM_LEDS, CRGB::White);
        } else {
          fill_solid(leds, NUM_LEDS, CRGB::Black);
        }
        FastLED.show();
      }
      request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
 

}
