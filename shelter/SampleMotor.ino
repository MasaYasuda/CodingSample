/**
 * @file SampleMotor.ino
 * @brief MotorDriver.hのサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-9-27
*/

#include <Arduino.h>
#include <MotorDriver.h>

const int PWMPIN=8;
const int DIRPIN=40;

MotorDriver motorDriver(PWMPIN,DIRPIN);

void setup(){

}
void loop(){
  motorDriver.write(125);
  delay(10);
  motorDriver.write(-125);
  delay(10);
}


