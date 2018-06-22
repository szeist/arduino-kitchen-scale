#include <Arduino.h>
#include <HX711_ADC.h>
#include <CHPLX12.h>

// #define CALIBRATE_MODE

#define STABILISING_TIME_MS 2000
#define DEFAULT_CAL_FACTOR 1030.0
#define REFRESH_TIME 250

float global_timer;
uint16_t global_display_value;

/*
  HX711 wiring (custom PINs)
  DT  = D3
  SCK = D4
*/
HX711_ADC LoadCell(3, 4);

/*
  CHPLC12 wiring
  PIN1 = D8
  PIN1 = D7
  PIN1 = D6
  PIN1 = D5
*/
CHPLX12 binaryDisplay(8, 7, 6, 5);


void setup() {
  binaryDisplay.clear();

  LoadCell.begin();
  LoadCell.start(STABILISING_TIME_MS);
  LoadCell.setCalFactor(DEFAULT_CAL_FACTOR);
  LoadCell.tare();

  #ifdef CALIBRATE_MODE
    Serial.begin(9600);
    Serial.println("Calibration mode initialized");
  #endif
}

void loop() {
  LoadCell.update();

  if (millis() > global_timer + REFRESH_TIME) {
    float weight = LoadCell.getData();

    #ifdef CALIBRATE_MODE
      float calFactor = LoadCell.getCalFactor();
      bool tareStatus = LoadCell.getTareStatus();
      calibrate_sendStatus(weight, calFactor, tareStatus);
      if (Serial.available() > 0) {
        char receivedCommand = Serial.read();
        calibrate_handleSerialCommand(receivedCommand);
      }
    #else
      global_display_value = getDisplayValue(weight);
    #endif
  
    global_timer = millis();
  }

  binaryDisplay.displayNumber(global_display_value);
}

static unsigned int getDisplayValue(float weight) {
  unsigned int value;

  if (weight < 0) {
    value = 0;
  } else if (weight > 4095) {
    value = 4095;
  } else {
    value = round(weight);
  }

  return value;
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