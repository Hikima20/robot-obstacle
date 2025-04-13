#include <Servo.h> 

// === Moteurs ===
#define ENA 9
#define IN1 3
#define IN2 4
#define ENB 10
#define IN3 5
#define IN4 6

// === Capteur ultrason ===
#define TRIG 7
#define ECHO 8

// === Servo moteur ===
#define SERVO_PIN 11
Servo monServo;

// === LED ===
#define LED_PIN 2

void setup() {
  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Éteint la LED au départ

  // Moteurs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Capteur
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo
  monServo.attach(SERVO_PIN);
  monServo.write(90);  // Position centrale

  // Serial
  Serial.begin(9600);
}

long lireDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duree = pulseIn(ECHO, HIGH);
  return duree * 0.034 / 2;
}

void loop() {
  long distance = lireDistance();
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 15) {
    digitalWrite(LED_PIN, LOW); // Pas d'obstacle, LED éteinte
    avancer();
  } else {
    digitalWrite(LED_PIN, HIGH); // Obstacle détecté, LED allumée
    reculer();
    delay(1000);
    arreter();

    // Scanner à droite
    monServo.write(30);
    delay(500);
    long droite = lireDistance();

    // Scanner à gauche
    monServo.write(150);
    delay(500);
    long gauche = lireDistance();

    // Revenir au centre
    monServo.write(90);
    delay(300);

    // Décider la direction
    if (droite > gauche) {
      tournerDroite();
    } else {
      tournerGauche();
    }

    delay(1000);
    arreter();
  }

  delay(200);
}

// === Fonctions de mouvement ===

void avancer() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 150);
}

void reculer() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 150);
}

void tournerDroite() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 150);
}

void tournerGauche() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 150);
}

void arreter() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}