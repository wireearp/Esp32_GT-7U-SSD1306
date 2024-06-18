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
  if (!display.begin(SSD1306_PAGEADDR, 0x3C)) {
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
