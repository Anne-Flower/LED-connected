#define LED_PIN   2  
// Creer une variable, sans utiliser define
// bool state = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.printf("started");

  // Afficher la variable dans port

  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  // Allume la lumiere, en passant par la variable 
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    // digitalWrite(LED_PIN, state ? HIGH : LOW);
    // delay(500);

  // Recupere une nouvelle valeur dans le port serie (true, false)
  // affiche la variable 
  // modifie l'etat de la led en foncition


}
