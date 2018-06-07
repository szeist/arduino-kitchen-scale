void calibrate_setup() {
  Serial.begin(9600);
  calibrate_drawScreen();
  Serial.println("Calibration mode initialized");
}

void calibrate_loop() {
  float weight = LoadCell.getData();
  float calFactor = LoadCell.getCalFactor();
  bool tareStatus = LoadCell.getTareStatus();
  
  calibrate_sendStatus(weight, calFactor, tareStatus);

  if (Serial.available() > 0) {
    char receivedCommand = Serial.read();
    calibrate_handleSerialCommand(receivedCommand);
  }
}

void calibrate_drawScreen() {
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);
    u8g.drawStr(0, 38, "Calibrate mode");
  } while (u8g.nextPage());
}

void calibrate_handleSerialCommand(char inByte) {
  float calDelta = 0;

  if (inByte == 'l') calDelta = -1.0;
  else if (inByte == 'L') calDelta = -10.0;
  else if (inByte == 'h') calDelta = 1.0;
  else if (inByte == 'H') calDelta = 10.0;
  else if (inByte == 't') LoadCell.tareNoDelay();

  if (calDelta != 't') {
    float calFactor = LoadCell.getCalFactor() + calDelta;
    LoadCell.setCalFactor(calFactor);
  }
}

void calibrate_sendStatus(float weight, float calFactor, bool tareStatus) {
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.print(" | CalFactor: ");
  Serial.println(calFactor);

  if (tareStatus) {
    Serial.println("Tare completed");
  }
}