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
const int16_t PIN_PWM = 3;
const int16_t PIN_DIR = 4;
const uint8_t PIN_ENC_A = 2;
const uint8_t PIN_ENC_B = 5;
const int16_t RESOLUTION = 360;
const double DIAMETER = 200.0;//[mm]

// Motor driver and encoder objects
MotorDriver motorDriver(PIN_PWM, PIN_DIR);
SpeedMeter speedMeter(PIN_ENC_A, PIN_ENC_B, RESOLUTION, DIAMETER);
volatile int32_t previousSpeed=0;//割込み時に書き換えられる変数

// PID controller parameters
const double Kp = 0.1;
const double Ki = 0.01;
const double Kd = 0.05;

// PID controller object
PIDController pid(Kp, Ki, Kd);

volatile double pidOutValue=0;

void timerHandler(){
  previousSpeed=speedMeter.read();
  pidOutValue=pid.calculate(previousSpeed);
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
