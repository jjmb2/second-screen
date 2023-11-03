#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64);
String in;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(1);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.setRotation(3);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.clearDisplay();

}

void loop() {
  // wait for input from script
  while (!Serial.available());
  in = Serial.readString();
  if (in == "t") {
    display_temp();
  }
}

void display_temp() {
  while (true) {
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(in + "C");
    display.display();
    delay(2000);
    Serial.write("0");
  }
}
