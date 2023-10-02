/**
 * @file SampleMotorDriver.ino
 * @brief MotorDriver.hのサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-9-27 作成
 * @date 2023-10-2 動作確認済み
*/

#include <Arduino.h>
#include <MotorDriver.h>

const int PWMPIN=8;
const int DIRPIN=40;

MotorDriver motorDriver(PWMPIN,DIRPIN);

void setup(){

}
void loop(){
  motorDriver.write(60);
  delay(1000);
  motorDriver.write(-255);
  delay(1000);
}


