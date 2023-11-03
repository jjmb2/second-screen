#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
String in;

//TODO: display logo at start and when the script is not running
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
    display.clearDisplay();
    display_temp();
  } else if (in == "g") {
    display.clearDisplay();
    graph_temp();
  }
}

void display_temp() {
  display.setRotation(3);
  while (true) {
    while (!Serial.available());
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(in + "C");
    display.display();
    Serial.write("0");
  }
}

//TODO: change the range of temperatures displayed (currently 0-64)
//TODO: display the current position on the graph (currently gets confusing when it loops and the current temp is the same as it was in this position last loop)
void graph_temp() {
  int pos = 0;
  display.setRotation(0);
  while (true) {
    while (!Serial.available());
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    display.fillRect(pos, 0, 2, SCREEN_HEIGHT, SSD1306_BLACK);
    display.fillRect(pos, 64 - in.toInt(), 2, 2, 1);
    display.display();

    pos += 2;
    pos = pos % SCREEN_WIDTH;

    Serial.write("0");
  }
}
