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
const int16_t PIN_PWM = 3;
const int16_t PIN_DIR = 4;
const uint8_t PIN_ENC_A = 2;
const uint8_t PIN_ENC_B = 5;
const int16_t RESOLUTION = 360;
const float DIAMETER = 200.0;

// Motor driver and encoder objects
MotorDriver motorDriver(PIN_PWM, PIN_DIR);
SpeedMeter speedMeter(PIN_ENC_A, PIN_ENC_B, RESOLUTION, DIAMETER);

volatile int32_t previousSpeedReadTime = 0; // 前回速度を読み取った時間

// PID controller parameters
const float Kp = 0.1;
const float Ki = 0.01;
const float Kd = 0.05;

// PID controller object
PIDController pid(Kp, Ki, Kd);

void setup()
{
  // Set PID controller GOalValue
  pid.setGoalValue(100.0);
}

void loop()
{
  if (micros() - previousSpeedReadTime > 20000) // 前回の読みとりから20ms経過していたら
  {
    float previousSpeed = speedMeter.read();
    motorDriver.write(pid.calculate(previousSpeed));
    previousSpeedReadTime = micros();
  }
  // Delay for stability
  delay(10);
}
