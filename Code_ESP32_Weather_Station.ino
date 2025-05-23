#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL31s_s9O87" 
#define BLYNK_TEMPLATE_NAME "ESP 32 WEATHER STATION" 

#include <WiFi.h> // importing all the required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Arduino.h"
#include "DHT.h"
// #include "SI114X.h"
#include "BMP085.h"
#include <Wire.h>

float temperature; // parameters
float humidity;
float pressure;
float mbar;
// float uv;
// float visible;
// float ir;

// SI114X SI1145 = SI114X(); // initialise sunlight sensor
// BMP085 myBarometer; // initialise pressure sensor

char auth[] = "46hn_AQnq0X8alAUNZLka8O8DfblSRhd"; // replace this with your auth token
char ssid[] = "one Plus"; // replace this with your wifi name (SSID)
char pass[] = "rishabh1"; // replace this with your wifi password

#define DHTPIN 13 // dht sensor is connected to D5
#define DHTTYPE DHT11     // DHT 11
// #define DHTTYPE DHT11   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE); // initialise dht sensor
BlynkTimer timer;

void sendSensor() // function to read sensor values and send them to Blynk
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); // read pressure value in pascals
  // m/bar = pressure / 100; // convert millibar to pascals
  // visible = SI1145.ReadVisible(); // visible radiation
  // ir = SI1145.ReadIR(); // IR radiation
  // uv = SI1145.ReadUV(); // UV index
  Serial.println(temperature);
  Serial.println(humidity);
  Blynk.virtualWrite(V0, temperature); // send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, humidity);
  // Blynk.virtualWrite(V2, mbar);
  // Blynk.virtualWrite(V3, visible);
  // Blynk.virtualWrite(V4, ir);
  // Blynk.virtualWrite(V5, uv);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Beginning Si1145!");
  // while (!SI1145.Begin())
  // {
    // Serial.println("Si1145 is not ready!");
    // delay(1000);
  // }
  // Serial.println("Si1145 is ready!");
  // myBarometer.init();
  Serial.println("Beginning Si1145!");
  dht.begin();
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  timer.setInterval(1000L, sendSensor); // sendSensor function will run every 1000 milliseconds
}

void loop()
{
  Blynk.run();
  timer.run();
}
