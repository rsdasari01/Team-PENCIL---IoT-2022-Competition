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

//Define SPI Pins for TFT Screen
#define TFT_CS        5
#define TFT_RST        4 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         2
#define SEALEVELPRESSURE_HPA (1013.25)

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_BME680 bme; // I2C

//SSID and Password for NTPTime
const char* ssid     = "dasari-5g";
const char* password = "Sw33thome264";

//Initialize more NTP Stuff
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

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

void setup(void) {
  Serial.begin(115200);
  //Initialize TFT Screen
  tft.initR(INITR_GREENTAB);
  initializeNTP();
  startupScreen();
  delay(10000);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  printTime();
  delay(1000);
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
  tft.setCursor(23, 130);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print(FormattedNTPTime);
}

void measureGasResistance() {
   //Equivalent to HP-354
  bme.setGasHeater(320, 700);
  Step1 = bme.readGas()/1000;
  bme.setGasHeater(100, 280);
  Step2 = bme.readGas()/1000;
  bme.setGasHeater(100, 1400);
  Step3 = bme.readGas()/1000;
  bme.setGasHeater(100, 2200);
  Step4 = bme.readGas()/1000;
  bme.setGasHeater(200, 700);
  Step5 = bme.readGas()/1000;
  bme.setGasHeater(200, 700);
  Step6 = bme.readGas()/1000;
  bme.setGasHeater(200, 700);
  Step7 = bme.readGas()/1000;
  bme.setGasHeater(320, 700);
  Step8 = bme.readGas()/1000;
  bme.setGasHeater(320, 700);
  Step9 = bme.readGas()/1000;
  bme.setGasHeater(320, 700);
  Step10 = bme.readGas()/1000;
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

void detectGases(){
  if (165 <= Step1 <= 170){
    }
  }
