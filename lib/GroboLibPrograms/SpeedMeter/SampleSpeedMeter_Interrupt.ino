/**
 * @file SampleSpeedMeter.ino
 * @brief SpeedMeter.hのサンプルプログラム(割込みあり)
 * @author Yasuda Masanaga
 * @date 2023-10-2 作成
 */

#include <Arduino.h>
#include "SpeedMeter.h"
#include "TimerOne.h"

SpeedMeter speedMeter(2, 10, 8192, 1000); // CUI AMTではResolutionは2048設定
volatile double speed = 0;
void timerHandler()//割込み関数
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