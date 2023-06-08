#define LIGHT_SENSOR_PIN 13
#define LED 15
#define BUZZER 4
#include <MPU6050_tockn.h>
#include <Wire.h>

const int sensorLDR = A0;
MPU6050 mpu6050(Wire);
float X;
float Y;
int BUZZER_PIN = 4;
int BUZZER_CHANNEL = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  
}

void loop() {
  mpu6050.update();
  //X = 20.00;
  //Y = 20.00;
  X = mpu6050.getAngleX();
  Y = mpu6050.getAngleY();
  //int analogValue = 40;
  int analogValue = analogRead(sensorLDR);
  Serial.print("\nNilai Sensor : ");
  Serial.print(analogValue);
  Serial.print(" Kondisi : ");
  
  if(analogValue <= 50){
    Serial.print("Keadaan gelap");
    digitalWrite(LED, HIGH);
    delay(1000);

  }
  else if(analogValue < 500 ){
    Serial.print("Keadaan Redup");
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
  }
  else if(analogValue < 2000) {
    Serial.print("Cahaya Terang");
    digitalWrite(LED, HIGH);
    
  }
  else{
    Serial.print("Secerah Masa Depan");
    digitalWrite(LED, LOW);
    delay(1000);
  }
  delay(200);
  Serial.println();
  Serial.print("Kemiringan Sumbu X : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\nKondisi : ");
  if(X > 10){
    Serial.print("Miring Kiri");
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_D, 8);
    delay(200);
  }
  else if(X < -10){
    Serial.print("Miring Kanan");
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_A, 8);
    delay(200);
  }
  else{
    Serial.print("Center");
    delay(200);
  }
  delay(200);
  Serial.print("\nKemiringan Sumbu Y : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\nKondisi : ");
  if(Y > 10) {
    Serial.print("Miring Depan");
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_E, 8);
    delay(200);
  }
  else if(Y < -10) {
    Serial.print("Miring Belakang");
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_C, 8);
    delay(200);
  }
  else{
    Serial.print("Center");
    
  }
  delay(200);



}
