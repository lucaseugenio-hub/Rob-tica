#include <Wire.h>
#include "Adafruit_TCS34725.h"

/*
   CODIGO PARA 2 SENSORES TCS34725
   usando multiplexador I2C TCA9548A

   TCS34725 endereco I2C = 0x29
   TCA9548A endereco = 0x70
*/

// ================================
// OBJETOS DOS SENSORES
// ================================
Adafruit_TCS34725 tcs1 =
Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_614MS,
  TCS34725_GAIN_1X
);

Adafruit_TCS34725 tcs2 =
Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_614MS,
  TCS34725_GAIN_1X
);

// ================================
// FUNCAO SELECIONAR CANAL TCA9548A
// ================================
void tcaSelect(uint8_t i) {

  if (i > 7) return;

  Wire.beginTransmission(0x70);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup(void) {

  Serial.begin(9600);
  Wire.begin();

  // =========================
  // SENSOR 1 -> CANAL 0
  // =========================
  tcaSelect(0);

  if (tcs1.begin()) {
    Serial.println("Sensor 1 encontrado");
  } else {
    Serial.println("Erro Sensor 1");
    while (1);
  }

  // =========================
  // SENSOR 2 -> CANAL 1
  // =========================
  tcaSelect(1);

  if (tcs2.begin()) {
    Serial.println("Sensor 2 encontrado");
  } else {
    Serial.println("Erro Sensor 2");
    while (1);
  }
}

void loop(void) {

  uint16_t r, g, b, c;
  uint16_t colorTemp, lux;

  // ====================================
  // LEITURA SENSOR 1
  // ====================================
  tcaSelect(0);

  tcs1.getRawData(&r, &g, &b, &c);

  colorTemp = tcs1.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs1.calculateLux(r, g, b);

  Serial.println("===== SENSOR 1 =====");

  Serial.print("Color Temp: ");
  Serial.print(colorTemp);
  Serial.print(" K - ");

  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.print(" - ");

  Serial.print("R: ");
  Serial.print(r);

  Serial.print(" G: ");
  Serial.print(g);

  Serial.print(" B: ");
  Serial.print(b);

  Serial.print(" C: ");
  Serial.println(c);

  // ====================================
  // LEITURA SENSOR 2
  // ====================================
  tcaSelect(1);

  tcs2.getRawData(&r, &g, &b, &c);

  colorTemp = tcs2.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs2.calculateLux(r, g, b);

  Serial.println("===== SENSOR 2 =====");

  Serial.print("Color Temp: ");
  Serial.print(colorTemp);
  Serial.print(" K - ");

  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.print(" - ");

  Serial.print("R: ");
  Serial.print(r);

  Serial.print(" G: ");
  Serial.print(g);

  Serial.print(" B: ");
  Serial.print(b);

  Serial.print(" C: ");
  Serial.println(c);

  Serial.println();

  delay(1000);
}