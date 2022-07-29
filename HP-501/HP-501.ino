#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

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

void setup() {
  Serial.begin(9600);
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

void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  //Equivalent to HP-501
  bme.setGasHeater(210, 3360);
  Step1 = bme.readGas()/1000;
  bme.setGasHeater(265, 240);
  Step2 = bme.readGas()/1000;
  bme.setGasHeater(265, 3080);
  Step3 = bme.readGas()/1000;
  bme.setGasHeater(320, 280);
  Step4 = bme.readGas()/1000;
  bme.setGasHeater(320, 3080);
  Step5 = bme.readGas()/1000;
  bme.setGasHeater(265, 3360);
  Step6 = bme.readGas()/1000;
  bme.setGasHeater(210, 3360);
  Step7 = bme.readGas()/1000;
  bme.setGasHeater(155, 3360);
  Step8 = bme.readGas()/1000;
  bme.setGasHeater(100, 3360);
  Step9 = bme.readGas()/1000;
  bme.setGasHeater(155, 3360);
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
