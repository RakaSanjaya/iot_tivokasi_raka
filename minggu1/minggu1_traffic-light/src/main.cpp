#include <Arduino.h>

int ledMerah = 25;
int ledKuning = 26;
int ledHijau = 27;
int buzzer = 14; // Tambahkan buzzer di pin 14

void setup() {
    Serial.begin(115200);
    Serial.println("Traffic Light System dengan Fitur Unik");

    pinMode(ledMerah, OUTPUT);
    pinMode(ledKuning, OUTPUT);
    pinMode(ledHijau, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

void countdown(int waktu) {
    for (int i = waktu; i > 0; i--) {
        Serial.print("Pergantian dalam: ");
        Serial.print(i);
        Serial.println(" detik");
        delay(1000);
    }
}

void loop() {
    // Merah - Berhenti (Durasi lebih lama)
    digitalWrite(ledMerah, HIGH);
    Serial.println("🔴 Merah ON - Berhenti!");
    countdown(5);
    digitalWrite(ledMerah, LOW);

    // Kuning - Bersiap Jalan (Kedip-kedip dan suara buzzer)
    for (int i = 0; i < 3; i++) {
        digitalWrite(ledKuning, HIGH);
        tone(buzzer, 1000); // Suara buzzer
        delay(500);
        digitalWrite(ledKuning, LOW);
        noTone(buzzer);
        delay(500);
    }
    Serial.println("🟡 Kuning ON - Bersiap Jalan!");

    // Hijau - Jalan
    digitalWrite(ledHijau, HIGH);
    Serial.println("🟢 Hijau ON - Silakan Jalan!");
    countdown(4);
    digitalWrite(ledHijau, LOW);

    // Kuning - Bersiap Berhenti (Kedip lagi)
    for (int i = 0; i < 3; i++) {
        digitalWrite(ledKuning, HIGH);
        tone(buzzer, 1000);
        delay(500);
        digitalWrite(ledKuning, LOW);
        noTone(buzzer);
        delay(500);
    }
    Serial.println("🟡 Kuning ON - Bersiap Berhenti!");
}
