#include <Servo.h>

// Pin tanımlamaları
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 10;

Servo myservo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin);
  
  myservo.write(0); // Başlangıçta kapak kapalı (0 derece)
  Serial.begin(9600);
}

void loop() {
  long duration, distance;

  // Mesafe ölçümü yapıyoruz
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Mesafeyi cm cinsinden hesapla

  if (distance > 0 && distance <= 5) {
    // Engel 5 cm veya daha yakınsa
    myservo.write(180); // Kapağı aç
    delay(3500);        // 3.5 saniye bekle
    
    // 3.5 saniye sonra tekrar ölçüm yapıyoruz
    // Eğer hala elin oradaysa döngü başa döner ve kapak açık kalır.
  } else {
    myservo.write(0);   // Engel yoksa kapağı kapat
  }

  delay(100); // Sensörün sapıtmaması için kısa bir bekleme
}

