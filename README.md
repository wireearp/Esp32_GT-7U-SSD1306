# Esp32_GT-7U-SSD1306
ESP32 with GPS and .96" OLED to disply coordinates
Wiring Diagram
ESP32 to SSD1306 OLED:

VCC (OLED) to 3.3V (ESP32)
GND (OLED) to GND (ESP32)
SCL (OLED) to GPIO 22 (ESP32)
SDA (OLED) to GPIO 21 (ESP32)
ESP32 to GT-7U GPS:

VCC (GPS) to 3.3V (ESP32)
GND (GPS) to GND (ESP32)
TX (GPS) to GPIO 16 (ESP32)
RX (GPS) to GPIO 17 (ESP32)
Code
Here's the Arduino sketch for the ESP32 Dev Kit 1:

cpp
Copy code
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the I2C pins for the ESP32
#define OLED_SDA 21
#define OLED_SCL 22

// Create SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Create TinyGPS++ object
TinyGPSPlus gps;

// Define the GPS serial port
HardwareSerial ss(1);

// GPS RX/TX pins
#define RXD2 16
#define TXD2 17

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Initialize OLED display
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read data from GPS module
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Clear the display
  display.clearDisplay();

  // Check if the GPS has a valid location
  if (gps.location.isValid()) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Latitude: ");
    display.println(gps.location.lat(), 6);

    display.setCursor(0, 10);
    display.print("Longitude: ");
    display.println(gps.location.lng(), 6);

    display.setCursor(0, 20);
    display.print("Satellites: ");
    display.println(gps.satellites.value());
  } else {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Waiting for GPS signal...");
  }

  // Display the information on the OLED
  display.display();
  
  delay(1000);
}
Libraries Needed
You will need the following libraries for this code to work:

Adafruit GFX Library: For the display graphics
Adafruit SSD1306 Library: For the OLED display
TinyGPS++ Library: For parsing GPS data
You can install these libraries via the Arduino Library Manager.

Steps to Install Libraries
Go to Sketch > Include Library > Manage Libraries...
In the Library Manager, search for "Adafruit GFX Library" and install it.
Search for "Adafruit SSD1306" and install it.
Search for "TinyGPS++" and install it.
Notes
Ensure your connections are secure and check the correct pin mappings.
Ensure your OLED display's I2C address is correct; the default is 0x3C but can vary.
Make sure your ESP32 board is selected in the Arduino IDE under Tools > Board.
This setup will display the GPS coordinates and the number of satellites the GPS module is connected to on the OLED screen.






