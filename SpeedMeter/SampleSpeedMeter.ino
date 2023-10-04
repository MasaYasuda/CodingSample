/**
 * @file SampleSpeedMeter.ino
 * @brief SpeedMeter.hのサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-10-2 作成
 */

#include <Arduino.h>
#include "SpeedMeter.h"

const uint8_t PIN_ENC_A = 2;
const uint8_t PIN_ENC_B = 10;
const int16_t RESOLUTION = 8912;
const float DIAMETER = 1000;

SpeedMeter speedMeter(PIN_ENC_A, PIN_ENC_B, RESOLUTION, DIAMETER); // CUI AMT10シリーズでResolution設定が2048の場合

void setup()
{
  Serial.begin(9600);
  speedMeter.reset();
}
void loop()
{
  Serial.println(speedMeter.speedRead());
  delay(100);
}