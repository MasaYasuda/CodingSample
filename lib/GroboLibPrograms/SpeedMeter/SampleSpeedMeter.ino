/**
 * @file SampleSpeedMeter.ino
 * @brief SpeedMeter.hのサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-10-2 作成
*/

#include <Arduino.h>
#include "SpeedMeter.h"

SpeedMeter speedMeter(2,10,8192,1000);//CUI AMTではResolutionは2048設定

void setup(){
  Serial.begin(9600);
  speedMeter.reset();
}
void loop(){
  Serial.println(speedMeter.speedRead());
  delay(100);
}