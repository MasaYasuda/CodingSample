/**
 * @file SampleSpeedMeter.ino
 * @brief SpeedMeter.hのサンプルプログラム(割込みあり)
 * @author Yasuda Masanaga
 * @date 2023-10-2 作成
 */

#include <Arduino.h>
#include "SpeedMeter.h"
#include "TimerOne.h"
const uint8_t PIN_ENC_A = 2;
const uint8_t PIN_ENC_B = 10;
const int16_t RESOLUTION = 8912;
const float DIAMETER = 1000;

SpeedMeter speedMeter(PIN_ENC_A, PIN_ENC_B, RESOLUTION, DIAMETER); // CUI AMT10シリーズでResolution設定が2048の場合
volatile float speed = 0;
void timerHandler() // 割込み関数
{
  speed = speedMeter.speedRead();
}

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(20000);
  Timer1.attachInterrupt(timerHandler);
  speedMeter.reset();
}
void loop()
{
  Serial.println(speed);
  delay(100);
}