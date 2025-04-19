/**
 * DHT11 Sensor Reader
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.1.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);

void setup() {
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);
    
    // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
     dht11.setDelay(500); // Set this to the desired delay. Default is 500ms.
}

void loop() {
    double temperature = 0;
    double humidity = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    temperature = dht11.readTemperature();
    delay(500);
    humidity = dht11.readHumidity();
    delay(500);

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        Serial.print("Temperature: ");
        Serial.print(3*temperature+20);
        Serial.print(" °C\tHumidity: ");
        Serial.print(3*humidity+40);
        Serial.println(" %");
    } else {
        // Print error message based on the error code.
        Serial.println("0");
    }
    delay(1000);
}
