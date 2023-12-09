#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 5
#define DHTTYPE DHT11

Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
String in;

DHT dht(DHTPIN, DHTTYPE);

// 'thinkchad-logo', 128x64px
const unsigned char epd_bitmap_thinkchad_logo [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x1f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0x0f, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xfc, 0x3f, 0xff, 0xff,
  0xff, 0xff, 0xe0, 0x47, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xf8, 0x07, 0xff, 0xff,
  0xff, 0xff, 0x83, 0xe7, 0xff, 0x9f, 0xc0, 0x00, 0x00, 0x01, 0xfc, 0xff, 0xf9, 0xc0, 0xff, 0xff,
  0xff, 0xff, 0x1f, 0xe3, 0xff, 0x98, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xff, 0xf3, 0xf8, 0x7f, 0xff,
  0xff, 0xfe, 0x3f, 0xf3, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xf3, 0xfe, 0x3f, 0xff,
  0xff, 0xfc, 0x7f, 0xf3, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xe3, 0xff, 0x1f, 0xff,
  0xff, 0xf9, 0xff, 0x73, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xe7, 0xff, 0x8f, 0xff,
  0xff, 0xf1, 0xc0, 0x03, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xf3, 0x03, 0xc7, 0xff,
  0xff, 0xe3, 0x80, 0x07, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xf0, 0x00, 0xe3, 0xff,
  0xff, 0xc7, 0x1f, 0xff, 0xff, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xf8, 0x40, 0x71, 0xff,
  0xff, 0x8f, 0x3f, 0xff, 0xff, 0x99, 0x03, 0x3d, 0xc5, 0xfe, 0x4c, 0xff, 0xff, 0xfe, 0x78, 0xff,
  0xff, 0x9f, 0x3f, 0xff, 0xff, 0x99, 0x93, 0xfd, 0xd5, 0xfe, 0x4c, 0xff, 0xff, 0xfe, 0x3c, 0xff,
  0xff, 0x1f, 0x3f, 0xff, 0xff, 0x99, 0x91, 0x45, 0x54, 0x44, 0x4c, 0xff, 0xff, 0xff, 0x3c, 0x7f,
  0xff, 0x3f, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x55, 0x55, 0x50, 0x4c, 0xff, 0xff, 0xff, 0x3e, 0x7f,
  0xfe, 0x3f, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x54, 0x5d, 0x40, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0x3f,
  0xfe, 0x7f, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x54, 0xdd, 0x40, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0x3f,
  0xfc, 0x7f, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x54, 0x55, 0x50, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0x9f,
  0xfc, 0xff, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x54, 0x55, 0x50, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0x9f,
  0xf8, 0xff, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x55, 0x55, 0x50, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0xcf,
  0xf9, 0xfe, 0x3f, 0xff, 0xff, 0x99, 0x90, 0x55, 0x45, 0x54, 0x4c, 0xff, 0xff, 0xff, 0x3f, 0xcf,
  0xf1, 0xfe, 0x3f, 0xf8, 0x1f, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xff, 0xff, 0x3f, 0xe7,
  0xf3, 0xfe, 0x00, 0xe0, 0x07, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xfc, 0x03, 0xe1, 0x3f, 0xe7,
  0xf3, 0xfe, 0x00, 0x07, 0xe1, 0x99, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xe0, 0x01, 0x80, 0x3f, 0xf3,
  0xe7, 0xfe, 0x3e, 0x1f, 0xf0, 0x19, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xc3, 0xf8, 0x1c, 0x1f, 0xf3,
  0xe7, 0xfe, 0xff, 0x8f, 0xf8, 0x19, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x07, 0xfc, 0x3f, 0x1f, 0xf1,
  0xc7, 0xff, 0xff, 0xcf, 0xfc, 0x19, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x0f, 0xfc, 0xff, 0xff, 0xf9,
  0xcf, 0xff, 0xff, 0xff, 0xfe, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xf9, 0xff, 0xff, 0xf9,
  0xc7, 0xff, 0xff, 0xff, 0xfe, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xff, 0xff, 0xff, 0xf9,
  0xe7, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xf9,
  0xe3, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xf3,
  0xf1, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xe3,
  0xf8, 0x7d, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc7,
  0xfe, 0x38, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xcf, 0x0f,
  0xff, 0x1c, 0x3f, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0x0e, 0x3f,
  0xff, 0x87, 0x03, 0x3f, 0xfc, 0x30, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1f, 0xff, 0xfe, 0x18, 0x7f,
  0xff, 0xe1, 0x80, 0x3f, 0xfc, 0x70, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0xfe, 0x00, 0x70, 0xff,
  0xff, 0xf0, 0x78, 0xff, 0xf8, 0x77, 0xf9, 0xff, 0x3f, 0xcf, 0xf3, 0x0f, 0xfe, 0x01, 0xc3, 0xff,
  0xff, 0xfc, 0x00, 0xff, 0xe0, 0x67, 0xf9, 0xff, 0x3f, 0xcf, 0xf3, 0x07, 0xff, 0xfe, 0x0f, 0xff,
  0xff, 0xff, 0x80, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x3f, 0xff,
  0xff, 0xff, 0xfe, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0x00, 0xef, 0xf3, 0xff, 0x3f, 0xe7, 0xf9, 0x80, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x01, 0xcf, 0xf3, 0xff, 0x3f, 0xe7, 0xf9, 0xc0, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe1, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xfe, 0x7f, 0xff, 0x3f, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xfe, 0x7f, 0xff, 0x3f, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xfc, 0xff, 0xff, 0x9f, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xfc, 0xff, 0xff, 0x9f, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(1);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  dht.begin();
}

void loop() {
  // display thinkchad logo
  display.clearDisplay();
  display.setRotation(0);
  display.drawBitmap(0, 0, epd_bitmap_thinkchad_logo, 128, 64, WHITE);
  display.display();

  // read from dht
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // compute heat index (isFahrenheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // wait for input from script
  while (!Serial.available());
  in = Serial.readString();
  if (in == "t") {
    display.clearDisplay();
    display_temp();
  } else if (in == "g") {
    display.clearDisplay();
    graph_temp();
  } else if (in == "c") {
    display.clearDisplay();
    display_clock();
  } else if (in == "a") {
    display_all(t, h, hic);
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
void graph_temp() {
  int pos = 0;
  while (true) {
    while (!Serial.available());
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    display.fillRect(pos, 0, 4, SCREEN_HEIGHT, SSD1306_BLACK);
    display.fillRect(pos, 64 - in.toInt(), 2, 2, 1);
    display.display();

    pos += 2;
    pos = pos % SCREEN_WIDTH;

    Serial.write("0");
  }
}

void display_clock() {
  display.setRotation(3);
  while (true) {
    while (!Serial.available());
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(in);
    display.display();
  }
}

void display_all(float t, float h, float hic) {
  display.clearDisplay();
  int pos = 0;
  display.setRotation(3);

  while (true) {
    while (!Serial.available());
    in = Serial.readString();

    if (in == "q") {
      break;
    }

    // clear previous time & temp
    display.fillRect(0, 0, 64, 64, SSD1306_BLACK);
    display.fillRect(0, 100, 64, 20, SSD1306_BLACK);

    // parse string
    int splitIdx = in.indexOf('\n', 0);
    String temp = in.substring(0, splitIdx);
    String time = in.substring(splitIdx + 1, in.length());

/*
    // print temp
    display.setCursor(0, 0);
    display.print(temp + "C");
*/

    // print dht11 temp, humidity, heat index
    display.setCursor(0, 0);
    display.print(t, 1);
    display.print("C\n");
    display.print(h, 1);
    display.print("%\n");
//    display.print(hic);
//    display.print("C");

    // print cpu temp
    display.print(temp + "C");

    // graph temp (from y pos 64-96)
    display.fillRect(pos, 64, 4, 64, SSD1306_BLACK);
    display.fillRect(pos, 96 - temp.toInt() / 2, 2, 2, 1);

    pos = (pos + 2) % SCREEN_HEIGHT;

    // display time
    display.setCursor(0, 100);
    display.print(time);

    display.display();
  }
}
