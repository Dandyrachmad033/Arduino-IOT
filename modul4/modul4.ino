#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "TMPL6bPzNulqR"
#define BLYNK_TEMPLATE_NAME "modul 4"
#define BLYNK_AUTH_TOKEN "qJ1ANBKW6PckESzu6kzK-nnmLwo5iBMk"
#define RELAY_PIN 12
#define LDR_PIN 34
BlynkTimer timer;

// Konfigurasi WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Halal";
char pass[] = "indonesia";

// Pin Relay
const int relayPin =12;

// Pin Sensor LDR
const int ldrPin = 34;

//initial value
bool btnON = false;

// bylnk button
BLYNK_WRITE(V0) 
{
  int blynkBtn = param.asInt(); 

  if (blynkBtn == 1){
    btnON = true;
  
  } else if (blynkBtn == 0) {
    btnON = false;

  }
}


void send_data() {
  delay(500);

  // light analog initial
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value = ");
  Serial.println(ldrValue);

  // other send status
  Serial.print("BTN Value = ");
  Serial.println(btnON);

  // blynk writer
  Blynk.virtualWrite(V2, ldrValue);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(500, send_data);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Matikan relay awalnya

  pinMode(ldrPin, INPUT);
}

void loop() {
  Blynk.run();
  int ldrValue = analogRead(ldrPin);


  // set using blynk reference
  if (!btnON){
      digitalWrite(relayPin, HIGH);
      if (ldrValue < 50) {
        digitalWrite(relayPin, LOW); 
        Serial.println("Lampu bohlam ON");
        Serial.println(ldrValue);
      } else {
        digitalWrite(relayPin, HIGH); 
        Serial.println("Lampu bohlam OFF");
      }
  } else {
    digitalWrite(relayPin, LOW);
    delay(500);
  }
  
  timer.run();
}