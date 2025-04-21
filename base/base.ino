#define LED_PIN 2
// // Creer une variable, sans utiliser define
bool state = true;

void setup() {
//   // put your setup code here, to run once:
  Serial.begin(115200); //communication entre ESP32 et ordi
  Serial.printf("started");

//   // Afficher la variable dans port

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
//   // Allume la lumiere, en passant par la variable
//   // digitalWrite(LED_PIN, HIGH);
//   // delay(1000);
//   // digitalWrite(LED_PIN, LOW);
//   // delay(1000);
  digitalWrite(LED_PIN, state ? HIGH : LOW);
  delay(1000);
  state = !state;
}


