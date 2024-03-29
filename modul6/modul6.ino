#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// #define BLYNK_TEMPLATE_ID "TMPL6bPzNulqR"
// #define BLYNK_TEMPLATE_NAME "modul 4"
// #define BLYNK_AUTH_TOKEN "qJ1ANBKW6PckESzu6kzK-nnmLwo5iBMk"

#define BLYNK_TEMPLATE_ID "TMPL6rldSRB1s"
#define BLYNK_TEMPLATE_NAME "Prak Modul 3"
#define BLYNK_AUTH_TOKEN "R-kTK-cR-C4ZTDg2XfEjvKXci71_RLco"

#define BLYNK_PRINT Serial

BlynkTimer timer;
const int LDR_pin = 32; // pin ADC untuk membaca data dari LDR
const int relay_pin = 25; // pin output untuk mengontrol module relay
const int buzzer_pin = 2;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Halal";
char pass[] = "indonesia";

String status = "MATI";
String statusMode = "MANUAL";
String nyala ="Lampu Hidup";
String mati = "Lampu Mati";

BLYNK_WRITE(V1) // terima data dari widget tombol pada pin virtual V1
{
  int relay_state = param.asInt();

  if (relay_state == 1) {
    status = "NYALA";  // menghidupkan lampu
  } else {
    status = "MATI" ; // mematikan lampu
  }
}

BLYNK_WRITE(V2) // terima data dari widget tombol pada pin virtual V2
{
  int relay_state = param.asInt();

  if (relay_state == 1) {
    statusMode = "AUTO";  // menghidupkan MODE
  } else {
    statusMode = "MANUAL" ; // mematikan MODE
  }
}

BLYNK_WRITE(V3) // terima data dari widget tombol pada pin virtual V3
{
  int relay_state = param.asInt();

  if (relay_state == 1) {
    digitalWrite(buzzer_pin, HIGH); // menghidupkan BUZZER
  } else {
    digitalWrite(buzzer_pin, LOW); // mematikan BUZZER
  }
}

void setup() {
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW); // relay default off
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW); //default off buzzer
  Serial.begin(9600);

   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Koneksi ke Blynk Cloud
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
}

void loop() {
  Blynk.run();
  timer.run();
  int LDR_value = analogRead(LDR_pin);
  Serial.print("LDR value: ");
  Serial.println(LDR_value);
  Blynk.virtualWrite(V0, LDR_value);

  
  if (LDR_value == 0) {
    Blynk.virtualWrite(V4, "MALAM");
  } else if(LDR_value > 130) {
    Blynk.virtualWrite(V4, "PAGI");
  }else if (LDR_value < 130 && LDR_value > 0) {
    Blynk.virtualWrite(V4, "SORE");
  }


  if(statusMode == "AUTO") {
    Serial.print("AUTO");
    if (LDR_value < 120) {
      digitalWrite(relay_pin, LOW); // menghidupkan lampu
      Blynk.virtualWrite(V5,nyala);
    } else if (LDR_value >= 120 && LDR_value <= 330){
      digitalWrite(relay_pin, LOW); // mematikan lampu
      Blynk.virtualWrite(V5, mati);
    } else if(LDR_value > 330) {
      digitalWrite(relay_pin, HIGH); 
      Blynk.virtualWrite(V5, mati);
    }
  }else{
    Serial.print("MANUAL");
    if (status == "NYALA") {
      digitalWrite(relay_pin, LOW); // menghidupkan lampu
      Blynk.virtualWrite(V5,nyala);
    } else if(status == "MATI") {
      digitalWrite(relay_pin, HIGH); // mematikan lampu
      Blynk.virtualWrite(V5, mati);

    }
  }

  
  delay(1000); // delay 1 detik
}