/**
 * @file SamplePIDCalc.ino
 * @brief PIDController.hのサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-9-23
*/

#include <Arduino.h>
#include <PIDController.h>

PIDController pid(10,.001,1);

void setup(){
  pid.setGoalValue(2000);
}

void loop(){
  double output=pid.calculate(1500);
}

