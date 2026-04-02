/**
 * @file RobotPerception.ino
 * @author Dylan Bassinga (ISM Dakar)
 * @brief Système de perception autonome utilisant la POO et le multitâche simulé.
 * Architecture logicielle pour robotique de service.
 */

#include <Arduino.h>

// --- CLASSE DE GESTION DES CAPTEURS (ABSTRACTION) ---
class SensorFusion {
  private:
    int trig, echo, irPin;
    float lastFusedDistance;
    unsigned long lastUpdate;
    const unsigned long interval = 50; // Mise à jour à 20Hz (50ms)

  public:
    SensorFusion(int t, int e, int ir) : trig(t), echo(e), irPin(ir) {}

    void begin() {
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
      analogReadResolution(12); // Spécifique ESP32 : 0-4095
    }

    float getDistance() {
      // Lecture Ultrasons (Méthode non-bloquante simplifiée ici)
      digitalWrite(trig, LOW); delayMicroseconds(2);
      digitalWrite(trig, HIGH); delayMicroseconds(10);
      digitalWrite(trig, LOW);
      float dsUS = pulseIn(echo, HIGH, 30000) * 0.034 / 2; // Timeout à 30ms

      // Lecture Infrarouge + Linéarisation
      float voltage = analogRead(irPin) * (3.3 / 4095.0);
      float dsIR = 27.86 * pow(voltage, -1.15);

      // ALGORITHME DE FUSION PONDÉRÉE
      // Confiance élevée en l'IR à courte portée, US à longue portée
      float weight = (dsIR < 25.0) ? 0.8 : 0.2;
      lastFusedDistance = (dsIR * weight) + (dsUS * (1.0 - weight));
      
      return lastFusedDistance;
    }
};

// --- CLASSE DE CONTRÔLE DES MOTEURS ---
class DriveTrain {
  private:
    int in1, in2, enA;
  public:
    DriveTrain(int i1, int i2, int e) : in1(i1), in2(i2), enA(e) {}

    void init() {
      pinMode(in1, OUTPUT); pinMode(in2, OUTPUT); pinMode(enA, OUTPUT);
    }

    void drive(int speed) {
      digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
      analogWrite(enA, speed);
    }

    void emergencyStop() {
      digitalWrite(in1, LOW); digitalWrite(in2, LOW);
      analogWrite(enA, 0);
    }
};

// --- INSTANCIATION DES OBJETS ---
SensorFusion perception(5, 18, 34);
DriveTrain motors(27, 26, 14);

unsigned long previousMillis = 0;
const long sensorInterval = 100; // Lecture toutes les 100ms

void setup() {
  Serial.begin(115200);
  perception.begin();
  motors.init();
  Serial.println("SYSTEM READY: L3 ETSE ARCHITECTURE");
}

void loop() {
  unsigned long currentMillis = millis();

  // BOUCLE DE CONTRÔLE TEMPS RÉEL (Non-Blocking)
  if (currentMillis - previousMillis >= sensorInterval) {
    previousMillis = currentMillis;

    float distance = perception.getDistance();
    Serial.printf("Distance Fused: %.2f cm\n", distance);

    if (distance < 20.0 && distance > 1.0) {
      Serial.println("STATE: OBSTACLE_DETECTED - EMERGENCY_STOP");
      motors.emergencyStop();
    } else {
      motors.drive(180); // Vitesse constante
    }
  }

  // Ici, le processeur est libre pour d'autres tâches (ex: WiFi, Bluetooth)
}
