/**
 * @file SampleSpeedPID.cpp
 * @brief 速度PID制御でモーターを一定速度で回す
 * @author Masanaga Yasuda
 * @date 2023/09/27
 */

#include <Arduino.h>
#include "MotorDriver.h"
#include "Encoder.h"
#include "PIDController.h"

// Motor driver and encoder pins
const int pwmPin = 3;
const int dirPin = 4;
const int encoderPinA = 2;
const int encoderPinB = 5;

// Motor driver and encoder objects
MotorDriver motor(pwmPin, dirPin);
Encoder encoder(encoderPinA, encoderPinB);

// PID controller parameters
const double Kp = 0.1;
const double Ki = 0.01;
const double Kd = 0.05;

// PID controller object
PIDController pid(Kp, Ki, Kd);

void setup() {
  // Initialize motor driver and encoder
  motor.init();
  encoder.init();
  
  // Set PID controller setpoint
  pid.setSetpoint(100);  // Desired speed in RPM
}

void loop() {
  // Read encoder value
  int encoderValue = encoder.read();
  
  // Calculate speed error
  double speedError = pid.getSetpoint() - encoderValue;
  
  // Calculate motor output
  double motorOutput = pid.calculate(speedError);
  
  // Set motor speed
  motor.setSpeed(motorOutput);
  
  // Delay for stability
  delay(10);
}
