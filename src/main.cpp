#include <Arduino.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFi.h>
// WiFi network configuration
char *ssid = "ISI_WiFi";
const char* password = "Exam@ISI2025";

// ThingSpeak channel configuration
unsigned long channelID = 3332477;
const char* writeAPIKey = "SHP16TVRRPFY3WX7";

// DHT11 sensor configuration (GPIO 5)
#define DHTPIN 5
#define DHTTYPE DHT11

// initialize sensor and WiFi client
DHT dht(DHTPIN, DHTTYPE);
WiFiClient Client;

void setup() {
    Serial.begin(115200);        // start serial communication at 115200 baud
    dht.begin();                  // initialize DHT11 sensor
    WiFi.begin(ssid, password);   // connect to WiFi network
    Serial.println(WiFi.localIP()); // print ESP32 IP address
    ThingSpeak.begin(Client);     // initialize ThingSpeak client
}

void loop() {
    // read temperature and humidity from DHT11 sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // display values on Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Send data to thingSpeak channel
    // Field 1 = temperature, Field 2 = humidity
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.writeFields(channelID, writeAPIKey);

    delay(10000); // wait 10 seconds before next reading
}
