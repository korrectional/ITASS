#include <Arduino.h>

void setup() {
    // Initialize serial communication at 115200 baud
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for serial port to connect (needed for some boards)
    }
    
    Serial.println("Hello, World!");
}

void loop() {
    // Print a repeating message every 2 seconds
    Serial.println("Hello, World! From loop.");
    delay(2000);
}
