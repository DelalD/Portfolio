#include "VoiceRecognitionV3.h"

VR myVR(2, 3); // RX, TX Pins für das Modul (SoftwareSerial)

#define LED_PIN 6     // LED am Pin 6
int relayPin = 7;     // Relais an Pin 7

uint8_t buf[64];

void setup() {
  Serial.begin(9600);
  myVR.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(LED_PIN, LOW);   // LED aus beim Start
  digitalWrite(relayPin, LOW);  // Relais aus beim Start (LOW = aus, je nach Modul!)

  if (myVR.load((uint8_t)0) >= 0) {
    Serial.println("Sprachbefehle geladen.");
  } else {
    Serial.println("Fehler beim Laden der Sprachbefehle!");
  }
}

void loop() {
  int ret = myVR.recognize(buf, 50); // prüfen ob etwas erkannt wurde
  if (ret > 0) {
    switch (buf[1]) {  
      case 0: 
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(relayPin, HIGH);  // Relais einschalten
        Serial.println("AN: LED + Relais");
        break;

      case 1:  
        digitalWrite(LED_PIN, LOW);
        digitalWrite(relayPin, LOW);   // Relais ausschalten
        Serial.println("AUS: LED + Relais");
        break;

      default:
        Serial.println("Unbekannter Befehl");
        break;
    }
  }
}
