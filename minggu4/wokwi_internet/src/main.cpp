#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 27    
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WiFiClientSecure client;
HTTPClient http;

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Terhubung!");
  
  delay(2000); // Tambahan delay agar koneksi lebih stabil
  
  dht.begin();
  delay(1000);

  client.setInsecure();  // Menonaktifkan SSL verification (untuk ngrok)
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float h = round(dht.readHumidity());
    float t = round(dht.readTemperature());

    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    float hic = dht.computeHeatIndex(t, h, false);

    String url = "https://d674-175-45-191-254.ngrok-free.app:443/api/posts/";

    Serial.print("Menghubungkan ke: ");
    Serial.println(url);

    http.begin(client, url);
    http.useHTTP10(true);  // Gunakan HTTP 1.0 agar lebih stabil
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"nama_sensor\":\"Sensor GD\", \"nilai1\":" + String(h) + ", \"nilai2\":" + String(t) + "}";

    Serial.println("Mengirim data:");
    Serial.println(payload);

    int httpResponseCode = http.POST(payload);

    Serial.print("Kode respons HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respons dari server:");
      Serial.println(response);
    } else {
      Serial.println("Gagal mengirim data");
    }

    http.end();
  }
}
