# Encrypted Pager with ESP32 and Hardware Encryption

## Description

This project implements an encrypted pager using an ESP32 microcontroller, a LoRa module, an OLED display, and the ATSHA204A hardware encryption chip. The pager sends and receives encrypted messages wirelessly and displays them on the OLED screen.

## Components

- ESP32 development board
- OLED display (SSD1306)
- LoRa module (SX1278)
- Atmel ATSHA204A encryption chip
- Push buttons
- Battery pack or suitable power supply

## Circuit Diagram

### OLED Display (SSD1306)
- VCC -> 3.3V on ESP32
- GND -> GND on ESP32
- SCL -> GPIO22 on ESP32
- SDA -> GPIO21 on ESP32

### LoRa Module (SX1278)
- VCC -> 3.3V on ESP32
- GND -> GND on ESP32
- SCK -> GPIO18 on ESP32
- MISO -> GPIO19 on ESP32
- MOSI -> GPIO23 on ESP32
- NSS -> GPIO5 on ESP32
- RESET -> GPIO14 on ESP32
- DIO0 -> GPIO26 on ESP32

### ATSHA204A
- VCC -> 3.3V on ESP32
- GND -> GND on ESP32
- SDA -> GPIO4 on ESP32
- SCL -> GPIO15 on ESP32

## Libraries

Install the following libraries from the Arduino Library Manager:
- Adafruit SSD1306
- Adafruit GFX Library
- RadioHead
- SHA204 Library

## Setup

1. Connect all the components as described in the circuit diagram.
2. Install the necessary libraries in the Arduino IDE.
3. Upload the provided code to the ESP32.

## Usage

- Upon powering up the ESP32, the OLED display will initialize and be ready to display messages.
- The ESP32 will send and receive encrypted messages using the LoRa module.
- Received messages will be decrypted and displayed on the OLED screen.

## Future Improvements

- Add user input for custom messages via push buttons.
- Implement a more robust encryption method if necessary.
- Expand the project to use a GSM module for broader communication capabilities.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
