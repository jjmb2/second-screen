#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64);
String temp;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(1);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64) // init done // Show image buffer on the display hardware.
  display.display(); //delay(2000);
  display.setRotation(3);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.clearDisplay();

}

void loop() {
  // wait for input from script
  while (!Serial.available());
  temp = Serial.readString();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(temp + "C");
  display.display();
  delay(2000);
  Serial.write("0");
}
