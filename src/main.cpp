#include <Arduino.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFi.h>
char *ssid = "ISI_WiFi";
const char* password = "Exam@ISI2025";
unsigned long channelID = 3332477;
const char* writeAPIKey = "SHP16TVRRPFY3WX7";
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient Client;
void setup() {
    Serial.begin(115200);
    dht.begin();
    WiFi.begin(ssid, password);
    Serial.println(WiFi.localIP());
    ThingSpeak.begin(Client);
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    Serial.print("Température: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidité: ");
    Serial.print(humidity);
    Serial.println(" %");
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    int x = ThingSpeak.writeFields(channelID, writeAPIKey);
    delay(10000);
}
