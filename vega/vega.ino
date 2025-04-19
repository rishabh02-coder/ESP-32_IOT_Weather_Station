#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL31s_s9O87" 
#define BLYNK_TEMPLATE_NAME "VEGA WEATHER STATION" 

// Import necessary libraries for Vega Processor
#include <WiFiNINA.h>

//#include <BlynkSimpleWiFiLink.h>// Hypothetical WiFi library for Vega (replace with actual)
#include <Wire.h>
#include "Arduino.h"
#include "DHT.h"
#include "BMP085.h"  // Replace with Vega equivalent if needed

// Define sensor and Wi-Fi parameters
float temperature;
float humidity;
float pressure;
float mbar;

char auth[] = "46hn_AQnq0X8alAUNZLka8O8DfblSRhd"; // Blynk auth token
char ssid[] = "one Plus"; // WiFi SSID
char pass[] = "rishabh1"; // WiFi password

#define DHTPIN 13       // Define the pin for DHT sensor (adjust based on Vega)
#define DHTTYPE DHT11   // DHT sensor type

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor
Adafruit_BMP085 bmp;      // Initialize BMP180 sensor

BlynkTimer timer;

void sendSensor() // Function to read sensor values and send to Blynk
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Check if sensor reading was successful
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println(temperature);
  Serial.println(humidity);
  
  // Send sensor data to Blynk app
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void setup()
{
  Serial.begin(9600);
  
  // Initialize Wi-Fi for Vega Processor (adapt with actual library)
  WiFiNINA_h.begin(ssid, pass);
  
  // Blynk authentication
  Blynk.config(auth);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  // Setup timer to read sensor data every few seconds
  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();  // Run Blynk functions
  timer.run();  // Run timer to send sensor data
}
