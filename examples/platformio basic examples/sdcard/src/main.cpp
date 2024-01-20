#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/** The clock select pin for the SD card module */
//4 for 2020 badge, 14 for 2024 badge
#define CS_PIN 14

void setup() {

  // Initialize the Serial (it'll tell us if the program runned correctly)
  Serial.begin(115200);

  delay(1000);
  Serial.println("init SPI...");
  //don't init for 2020 badge, keep SPI default pins:
  SPI.begin(7, 8, 6);

  Serial.println("SD test started...");
  delay(1000);

  // Check the module is connected
  if (!SD.begin(CS_PIN, SPI, 20000000)) {
    Serial.println("Error, SD Initialization Failed");
    return;
  }

  File testFile = SD.open("/SDTest.txt", FILE_WRITE);
  if (testFile) {
    testFile.println("Hello ESP32 SD");
    testFile.close();
    Serial.println("Success, data written to SDTest.txt");
  } else {
    Serial.println("Error, couldn't write SDTest.txt");
  }

  File readFile = SD.open("/SDTest.txt", FILE_READ);
  if (readFile) {
    String l = readFile.readString();
    while (readFile.available()) {
      Serial.println(l);
      l = readFile.readString();
    }
  } else {
    Serial.println("Error, couldn't read main.cpp");
  }
}

// Do nothing, sd card operations run on setup()
void loop() {}