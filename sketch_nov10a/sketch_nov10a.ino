#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL31s_s9O87" 
#define BLYNK_TEMPLATE_NAME "ESP8266 WEATHER STATION" 

#include <ESP8266WiFi.h> // Use ESP8266 WiFi library instead of WiFi.h
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"
#include "DHT.h"

float temperature; // parameters
float humidity;

char auth[] = "46hn_AQnq0X8alAUNZLka8O8DfblSRhd"; // replace this with your auth token
char ssid[] = "one Plus"; // replace this with your WiFi name (SSID)
char pass[] = "rishabh1"; // replace this with your WiFi password

#define DHTPIN 14 // DHT sensor is connected to GPIO14 (D5 on NodeMCU)
#define DHTTYPE DHT11 // Specify DHT11 type

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor
BlynkTimer timer;

void sendSensor() // Function to read sensor values and send them to Blynk
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.println(humidity);
  Serial.println(temperature);
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  Serial.println(temperature);
  Serial.println(humidity);
  Blynk.virtualWrite(V0, temperature); // Send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, humidity);
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  delay(1000);
  Blynk.begin(auth, ssid, pass); // Connect to Blynk server
  delay(1000);
  timer.setInterval(1000L, sendSensor); // Call sendSensor every 1000 milliseconds
}

void loop()
{
  Blynk.run();
  timer.run();
}
