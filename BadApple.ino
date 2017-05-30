#include "SD.h"
#include "U8glib.h"

#define LCD_WIDTH 128
#define LCD_HEIGHT 64
#define WIDTH_COUNT 9
#define HEIGHT 54
#define SIZE (WIDTH_COUNT*HEIGHT)
#define top (LCD_HEIGHT - HEIGHT) / 2
#define left (LCD_WIDTH - WIDTH_COUNT * 8) / 2

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI

char buf[SIZE];

File root;
File myFile;

void draw() {
  u8g.drawBitmap(left, top, WIDTH_COUNT, HEIGHT, (const uint8_t*)buf);
}

void setup(){
  Serial.begin(38400);
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("Initialization Failed");
    return;
  }
  Serial.println("Initialization OK");
  myFile = SD.open("bad.BIN");
}

void loop(){
  u8g.firstPage();
  do {
    draw();
  } while(u8g.nextPage());

  if  (myFile && myFile.available()) {
    myFile.read(buf, SIZE);
  } else {
    myFile.close();
    myFile = SD.open("bad.BIN");
    Serial.println("Replay.");
    delay(5000);
  }
}
