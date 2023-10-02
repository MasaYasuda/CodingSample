/**
 * @file SamplePositionPID.ino
 * @brief 位置PID制御を行なうサンプルプログラム
 * @author Yasuda Masanaga
 * @date 2023-9-29
 */

#include <Arduino.h>
#include <Encoder.h>
#include <PIDController.h>
#include <MotorDriver.h>

const int BUTTON1_PIN = 4;
const int BUTTON2_PIN = 5;
const int BUTTON3_PIN = 6;

const int ENC_PINA = 2;
const int ENC_PINB = 3;
Encoder encoder(ENC_PINA, ENC_PINB);

const int MOTOR_PWMPIN = 7;
const int MOTOR_DIRPIN = 12;
MotorDriver motorDriver(MOTOR_PWMPIN, MOTOR_DIRPIN);

const int Kp = 10;
const int Ki = 0;
const int Kd = 0;
PIDController pidController(Kp, Ki, Kd);

long goalPosition = 0; // PIDの目標値

void setup()
{
}
void loop()
{
  pidController.setGoalValue(goalPosition);
  int output = (int)pidController.calculate(encoder.read());
  motorDriver.write(output);
}
