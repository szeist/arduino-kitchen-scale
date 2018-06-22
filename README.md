# Arduino Kitchen Scale with binary display

# Parts

1. `Arduino Nano` with ATmega328
2. `HX711` Load cell amplifier
3. `Straight bar load cell (2kg)`
4. `Charlieplexed led array with 12 leds`

# Requirements

1. [HX711_ADC](https://github.com/olkal/HX711_ADC) library
2. [CHPLX12](https://github.com/szeist/CHPLX12) library

## Calibrate

### 1. Upload calibration firmware

Define CALIBRATE_MODE in `firmware.ino`, complile and upload the firmware.

### 2. Put a known weightd item to the scale and use the serial interface for calibration

Connect to the serial port and use the following keys to adjust the measured weight:

| Key | Calibration Value |
| --- | ----------------- |
| `h` | +1                |
| `H` | +10               |
| `l` | -1                |
| `L` | -10               |
| `t` | Tare              |

### 3. Update the calibration factor

Update the `DEFAULT_CAL_FACTOR` in the `firmware.ino` with the new CalFactor value.
