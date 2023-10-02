/**
 * @file SampleSpeedPID.cpp
 * @brief 速度PID制御でモーターを一定速度で回す(割込みあり)
 * @author Masanaga Yasuda
 * @date 2023-10-2
 */

#include <Arduino.h>
#include <TimerOne.h>
#include "MotorDriver.h"
#include "PIDController.h"
#include "SpeedMeter.h"

// Motor driver and encoder pins
const int PWMPIN = 3;
const int DIRPIN = 4;
const uint8_t ENC_PINA = 2;
const uint8_t ENC_PINB = 5;
const int RESOLUTION = 360;
const double DIAMETER = 200.0;

// Motor driver and encoder objects
MotorDriver motorDriver(PWMPIN, DIRPIN);
SpeedMeter speedMeter(ENC_PINA, ENC_PINB, RESOLUTION, DIAMETER);

volatile long nowSpeed=0;//割込み時に書き換えられる変数

// PID controller parameters
const double Kp = 0.1;
const double Ki = 0.01;
const double Kd = 0.05;

// PID controller object
PIDController pid(Kp, Ki, Kd);

volatile double pidOutValue=0;

void timerHandler(){
  nowSpeed=speedMeter.read();
  pidOutValue=pid.calculate(nowSpeed);
}

void setup()
{
  // Set PID controller GOalValue
  pid.setGoalValue(100.0);
  Timer1.initialize(20000); //20msごとの割込み
  Timer1.attachInterrupt(timerHandler); 
}

void loop()
{
  motorDriver.write(pidOutValue);
  // Delay for stability
  delay(10);
}
