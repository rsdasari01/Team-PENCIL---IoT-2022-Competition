//Including Libraries
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>

//Define SPI Pins for TFT Screen
#define TFT_CS        5
#define TFT_RST        4 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         2
#define SEALEVELPRESSURE_HPA (1013.25)

#define LED_PIN     13
#define NUM_LEDS    16
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_BME680 bme; // I2C

//SSID and Password for NTPTime
const char* ssid     = "dasari-5g";
const char* password = "Sw33thome264";

//Initialize more NTP Stuff
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//Initialize the DFPlayerMini stuff
HardwareSerial mySoftwareSerial(1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//Initialize all the strings for NTPTime
String NTPTime;
String NTPHour;
String NTPMinute;
String NTPDay;
String AMPM;

float Step1;
float Step2;
float Step3;
float Step4;
float Step5;
float Step6;
float Step7;
float Step8;
float Step9;
float Step10;

int count;

void setup(void) {
  mySoftwareSerial.begin(9600, 16, 17);
  Serial.begin(115200);
  //Initialize TFT Screen
  tft.initR(INITR_GREENTAB);
  initializeNTP();
  initializeDFPlayerMini();
  initializeLEDs();
  initializeBMESensor();
  startupScreen();
  delay(10000);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  printTime();
  detectGases();
  measureGasResistance();
  tft.fillScreen(ST77XX_BLACK);
}

void startupScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.fillTriangle(64, 5, 59, 15, 69, 15, ST77XX_CYAN);
  tft.fillRect(59, 20, 11, 50, ST77XX_CYAN);
  tft.fillRect(59, 75, 11, 5, ST77XX_CYAN);
  tft.fillRect(59, 85, 11, 10, ST77XX_CYAN);
  tft.setCursor(30, 110);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print("PENCIL");
  tft.setCursor(45, 130);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print("INC.");
}

void initializeNTP() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone:
  timeClient.setTimeOffset(-14400);
}


void initializeBMESensor() {
  while (!Serial);
  Serial.println(F("BME680 test"));
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
}

void initializeDFPlayerMini() {
  mySoftwareSerial.begin(9600, SERIAL_8N1, 16, 17);  // speed, type, RX, TX

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(myDFPlayer.readType(), HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

}

void initializeLEDs() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
}
void printTime() {
  timeClient.update();
  NTPTime = timeClient.getFormattedTime();
  Serial.println(NTPTime);
  NTPHour = NTPTime.substring(0, 2);
  Serial.println(NTPHour);
  int Hour = NTPHour.toInt();
  Serial.println(Hour);
  NTPMinute = NTPTime.substring(3, 5);
  Serial.println(NTPMinute);
  if (Hour < 12 || Hour == 24) {
    AMPM = "AM";
  }
  else {
    AMPM = "PM";
  }
  if (Hour >= 13) {
    Hour = Hour - 12;
  }
  if (Hour < 10) {
    NTPHour = "0" + String(Hour);
  }
  else {
    NTPHour = String(Hour);
  }

  Serial.println(NTPHour);
  String FormattedNTPTime = NTPHour + ":" + NTPMinute + AMPM;
  Serial.println(FormattedNTPTime);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(23, 20);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print(FormattedNTPTime);
}

void measureGasResistance() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  //Equivalent to HP-354
  bme.setGasHeater(320, 700);
  Step1 = bme.readGas() / 1000;
  bme.setGasHeater(100, 280);
  Step2 = bme.readGas() / 1000;
  bme.setGasHeater(100, 1400);
  Step3 = bme.readGas() / 1000;
  bme.setGasHeater(100, 2200);
  Step4 = bme.readGas() / 1000;
  bme.setGasHeater(200, 700);
  Step5 = bme.readGas() / 1000;
  bme.setGasHeater(200, 700);
  Step6 = bme.readGas() / 1000;
  bme.setGasHeater(200, 700);
  Step7 = bme.readGas() / 1000;
  bme.setGasHeater(320, 700);
  Step8 = bme.readGas() / 1000;
  bme.setGasHeater(320, 700);
  Step9 = bme.readGas() / 1000;
  bme.setGasHeater(320, 700);
  Step10 = bme.readGas() / 1000;
  Serial.print("Step 1:");
  Serial.println(Step1);
  Serial.print("Step 2:");
  Serial.println(Step2);
  Serial.print("Step 3:");
  Serial.println(Step3);
  Serial.print("Step 4:");
  Serial.println(Step4);
  Serial.print("Step 5:");
  Serial.println(Step5);
  Serial.print("Step 6:");
  Serial.println(Step6);
  Serial.print("Step 7:");
  Serial.println(Step7);
  Serial.print("Step 8:");
  Serial.println(Step8);
  Serial.print("Step 9:");
  Serial.println(Step9);
  Serial.print("Step 10:");
  Serial.println(Step10);
  Serial.println(" ");
}

void detectGases() {
  count = 1;
  //Gas Detection
  if ((0 <= Step1) && (Step1 <= 58)) {
    if ((0 <= Step2) && (Step2 <= 260)) {
      if ((0 <= Step3) && (Step3 <= 230)) {
        if ((0 <= Step4) && (Step4 <= 250)) {
          if ((10 <= Step5) && (Step5 <= 50)) {
            if ((0 <= Step6) && (Step6 <= 50)) {
              if ((0 <= Step7) && (Step7 <= 50)) {
                if ((0 <= Step8) && (Step8 <= 53)) {
                  if ((0 <= Step9) && (Step9 <= 53)) {
                    if ((0 <= Step10) && (Step10 <= 53)) {
                      myDFPlayer.volume(30);
                      myDFPlayer.play(1);
                      myDFPlayer.volume(30);
                      myDFPlayer.play(3);
                      tft.setCursor(23, 50);
                      tft.setTextColor(ST77XX_CYAN);
                      tft.setTextSize(2);
                      tft.print("Status: ");
                      tft.setCursor(37, 80);
                      tft.println("GAS");
                      tft.setCursor(35, 100);
                      tft.println("LEAK");
                      tft.setCursor(15, 120);
                      tft.println("DETECTED");
                      count = 0;
                      FastLED.show();
                      Serial.println("Gas Leak Detected");
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  //Fire Detection
  else if ((20 <= Step1) && (Step1 <= 40)) {
    if ((400 <= Step2) && (Step2 <= 650)) {
      if ((300 <= Step3) && (Step3 <= 450)) {
        if ((200 <= Step4) && (Step4 <= 350)) {
          if ((10 <= Step5) && (Step5 <= 30)) {
            if ((10 <= Step6) && (Step6 <= 30)) {
              if ((10 <= Step7) && (Step7 <= 20)) {
                if ((8 <= Step8) && (Step8 <= 16)) {
                  if ((10 <= Step9) && (Step9 <= 25)) {
                    if ((15 <= Step10) && (Step10 <= 30)) {
                      myDFPlayer.volume(30);
                      myDFPlayer.play(1);
                      myDFPlayer.volume(30);
                      myDFPlayer.play(3);
                      tft.setCursor(23, 50);
                      tft.setTextColor(ST77XX_CYAN);
                      tft.setTextSize(2);
                      tft.print("Status: ");
                      tft.setCursor(35, 80);
                      tft.println("FIRE");
                      tft.setCursor(15, 100);
                      tft.println("DETECTED");
                      fill_solid(leds, NUM_LEDS, CRGB::Red);
                      count = 2;
                      FastLED.show();
                      Serial.println("Fire Detected");
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  //Bleach Detection
  if ((170 <= Step1) && (Step1 <= 180)) {
    if ((11100 <= Step2) && (Step2 <= 11300)) {
      if ((4900 <= Step3) && (Step3 <= 5100)) {
        if ((3400 <= Step4) && (Step4 <= 3600)) {
          if ((230 <= Step5) && (Step5 <= 250)) {
            if ((200 <= Step6) && (Step6 <= 230)) {
              if ((160 <= Step7) && (Step7 <= 190)) {
                if ((100 <= Step8) && (Step8 <= 130)) {
                  if ((140 <= Step9) && (Step9 <= 170)) {
                    if ((150 <= Step10) && (Step10 <= 180)) {
                      myDFPlayer.volume(30);
                      myDFPlayer.play(1);
                      myDFPlayer.volume(30);
                      myDFPlayer.play(2);
                      tft.setCursor(23, 50);
                      tft.setTextColor(ST77XX_CYAN);
                      tft.setTextSize(2);
                      tft.print("Status: ");
                      tft.setCursor(25, 80);
                      tft.println("BLEACH");
                      tft.setCursor(35, 100);
                      tft.println("LEAK");
                      tft.setCursor(15, 120);
                      tft.println("DETECTED");
                      fill_solid(leds, NUM_LEDS, CRGB::Red);
                      count = 3;
                      FastLED.show();
                      Serial.println("Bleach Leak Detected");
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  else {

    if (count == 1) {
      fill_solid(leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
      Serial.println("everything is normal");
      tft.setCursor(23, 50);
      tft.setTextColor(ST77XX_CYAN);
      tft.setTextSize(2);
      tft.print("Status: ");
      tft.setCursor(25, 80);
      tft.println("Normal");
    }
    else if (count == 0) {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
      tft.fillScreen(ST77XX_BLACK);
      tft.println("GAS");
      tft.setCursor(35, 100);
      tft.println("LEAK");
      tft.setCursor(15, 120);
      tft.println("DETECTED");
    }
    else if (count == 2) {
      tft.setCursor(23, 50);
      tft.setTextColor(ST77XX_CYAN);
      tft.setTextSize(2);
      tft.print("Status: ");
      tft.setCursor(35, 80);
      tft.println("FIRE");
      tft.setCursor(15, 100);
      tft.println("DETECTED");
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
    }
    else if (count == 3) {
      tft.setCursor(23, 50);
      tft.setTextColor(ST77XX_CYAN);
      tft.setTextSize(2);
      tft.print("Status: ");
      tft.setCursor(25, 80);
      tft.println("BLEACH");
      tft.setCursor(35, 100);
      tft.println("LEAK");
      tft.setCursor(15, 120);
      tft.println("DETECTED");
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
    }
  }
}
