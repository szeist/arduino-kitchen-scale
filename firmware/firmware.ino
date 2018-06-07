#include <HX711_ADC.h>
#include "U8glib.h"

// #define CALIBRATE_MODE

#define STABILISING_TIME_MS 2000
#define DEFAULT_CAL_FACTOR 1005.0
#define REFRESH_TIME 250

/*
  OLED wiring (HW SPI)
  SCL = D13
  SDA = D10
  D/C = D9
  RST = D2
*/
U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(10, 9, 2);	

/*
  HX711 wiring (custom PINs)
  DT  = D3
  SCK = D4
*/
HX711_ADC LoadCell(3, 4);

float global_timer;

void setup() {
  drawInitScreen();
  LoadCell.begin();
  LoadCell.start(STABILISING_TIME_MS);
  LoadCell.setCalFactor(DEFAULT_CAL_FACTOR);

  #ifdef CALIBRATE_MODE
    calibrate_setup();
  #else
    measure_setup();
  #endif
}

void loop() {
  LoadCell.update();

  if (millis() > global_timer + REFRESH_TIME) {
    #ifdef CALIBRATE_MODE
      calibrate_loop();
    #else
      measure_loop();
    #endif
    global_timer = millis();
  }
}

void drawInitScreen() {
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);
    u8g.drawStr(0, 34, "Initalizing...");
  } while (u8g.nextPage());
}