/**
 * @file SampleSpeedPID.cpp
 * @brief 速度PID制御でモーターを一定速度で回す
 * @author Yasuda Masanaga
 * @date 2023-9-27
 */

#include <Arduino.h>
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

volatile long previousSpeedReadTime = 0; // 前回速度を読み取った時間

// PID controller parameters
const double Kp = 0.1;
const double Ki = 0.01;
const double Kd = 0.05;

// PID controller object
PIDController pid(Kp, Ki, Kd);

void setup()
{
  // Set PID controller GOalValue
  pid.setGoalValue(100.0);
}

void loop()
{
  if (micros() - previousSpeedReadTime > 20000)//前回の読みとりから20ms経過していたら
  {
    double nowSpeed=speedMeter.read();
    motorDriver.write(pid.calculate(nowSpeed));
    previousSpeedReadTime=micros();
  }
  // Delay for stability
  delay(10);
}
