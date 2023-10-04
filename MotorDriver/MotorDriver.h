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
 * @param (int16_t)pinPWM
 * @param (int16_t)pinDir
 */
class MotorDriver
{
public:
  MotorDriver(int16_t pinPWM, int16_t pinDir)
  {
    _pinPWM = pinPWM;
    _pinDir = pinDir;
    pinMode(pinDir, OUTPUT);
  }

  /**
   * @brief DIR,PWM出力を行なう
   * @param (int16_t)speed -255~255の整数値
   * @note speed>0のときDIRピンはHIGH
   */
  void write(int16_t speed)
  {
    speed = min(max(speed, -255), 255);
    if (speed > 0)
    {
      digitalWrite(_pinDir, HIGH);
      analogWrite(_pinPWM, speed);
    }
    else
    {
      digitalWrite(_pinDir, LOW);
      analogWrite(_pinPWM, -speed);
    }
  }

private:
  int16_t _pinPWM;
  int16_t _pinDir;
};

#endif
