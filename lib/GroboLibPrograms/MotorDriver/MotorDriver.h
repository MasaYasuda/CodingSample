/**
 * @file MotorDriver.h
 * @brief Motorを操作するモジュール
 * @author Yasuda Masanaga
 * @date 2023-9-27　作成
 */

#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <Arduino.h>

class MotorDriver;

/**
 * @brief MotorDriverへの入力用クラス
 * @param (int)pwmPin
 * @param (int)dirPin
 */
class MotorDriver
{
public:
  MotorDriver(int pwmPin, int dirPin)
  {
    _pwmPin = pwmPin;
    _dirPin = dirPin;
    pinMode(dirPin, OUTPUT);
  }

  /**
   * @brief DIR,PWM出力を行なう
   * @param (int)speed -255~255の整数値
   * @note speed>0のときDIRピンはHIGH
   */
  void write(int speed)
  {
    speed = min(max(speed, -255), 255);
    if (speed > 0)
    {
      digitalWrite(_dirPin, HIGH);
      analogWrite(_pwmPin, speed);
    }
    else
    {
      digitalWrite(_dirPin, LOW);
      analogWrite(_pwmPin, -speed);
    }
  }

private:
  int _pwmPin;
  int _dirPin;
};

#endif
