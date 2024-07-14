#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RH_RF95.h>
#include <SHA204.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LoRa settings
#define RFM95_CS 5
#define RFM95_RST 14
#define RFM95_INT 26

RH_RF95 rf95(RFM95_CS, RFM95_INT);

// ATSHA204A settings
SHA204 sha204;

// Encryption key
const uint8_t encryptionKey[32] = { /* Your 32-byte key here */ };

void setup() {
  Serial.begin(115200);

  // Initialize display
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Initializing...");
  display.display();

  // Initialize LoRa module
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa init failed");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("LoRa init failed");
    display.display();
    while (1);
  }
  rf95.setFrequency(915.0);
  rf95.setTxPower(13, false);

  // Initialize ATSHA204A
  if (!sha204.init()) {
    Serial.println("ATSHA204A init failed");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("ATSHA204A init failed");
    display.display();
    while (1);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Ready");
  display.display();
}

void loop() {
  // Example send message
  uint8_t msg[] = "Hello, world!";
  uint8_t encryptedMsg[32];
  
  // Encrypt the message
  if (sha204.encrypt(encryptionKey, msg, sizeof(msg), encryptedMsg)) {
    rf95.send(encryptedMsg, sizeof(encryptedMsg));
    rf95.waitPacketSent();
  } else {
    Serial.println("Encryption failed");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Encryption failed");
    display.display();
  }

  // Example receive message
  if (rf95.available()) {
    uint8_t buf[32];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      uint8_t decryptedMsg[32];
      
      // Decrypt the message
      if (sha204.decrypt(encryptionKey, buf, len, decryptedMsg)) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Received: ");
        display.print((char*)decryptedMsg);
        display.display();
      } else {
        Serial.println("Decryption failed");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Decryption failed");
        display.display();
      }
    }
  }

  delay(1000); // Adjust as needed for your application
}
