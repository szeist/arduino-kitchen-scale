void measure_setup() {}

void measure_loop() {
  float weight = LoadCell.getData();
  measure_drawWeight(round(weight));
}

void measure_drawWeight(float weight) {
  u8g.firstPage();  
  do {
    String displayStr = String(weight, 0) + " g";
    u8g.setFont(u8g_font_helvB24);
    u8g.drawStr(0, 44, displayStr.c_str());
  } while (u8g.nextPage());
}