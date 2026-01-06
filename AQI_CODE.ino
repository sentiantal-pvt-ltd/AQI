#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SensirionI2CSen5x.h>

/* ---------- TFT ---------- */
#define TFT_CS   5
#define TFT_DC   27
#define TFT_RST  4

/* ---------- I2C ---------- */
#define I2C_SDA  25
#define I2C_SCL  26

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
SensirionI2CSen5x sen5x;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // TFT init
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(10, 10);
  tft.println("SEN5x TFT TEST");

  // SEN5x init
  sen5x.begin(Wire);
  sen5x.deviceReset();
  delay(100);
  sen5x.startMeasurement();

  tft.setCursor(10, 40);
  tft.println("SEN5x OK");
}

void loop() {
  float pm1, pm2_5, pm4, pm10;
  float temp, hum, voc, nox;

  uint16_t error = sen5x.readMeasuredValues(
    pm1, pm2_5, pm4, pm10,
    hum, temp, voc, nox
  );

  if (error == 0) {
    tft.fillRect(0, 80, 320, 200, ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(10, 90);

    tft.print("PM2.5: ");
    tft.print(pm2_5);
    tft.println(" ug/m3");

    tft.print("PM10 : ");
    tft.print(pm10);
    tft.println(" ug/m3");

    tft.print("VOC  : ");
    tft.print(voc);
    tft.println(" idx");

    tft.print("NOx  : ");
    tft.print(nox);
    tft.println(" idx");
  }

  delay(2000);
}
