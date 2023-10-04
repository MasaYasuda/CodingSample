/**
 * @file PIDController.h
 * @brief PID制御の計算を行うモジュール
 * @author Yasuda Masanaga
 * @date 2023-9-27
 */

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <Arduino.h>

class PIDController;

/**
 * @brief PID制御計算用クラス
 * @param (float)Kp
 * @param (float)Ki
 * @param (float)Kd
 */
class PIDController
{
public:
  PIDController(float Kp, float Ki, float Kd)
  {
    _Kp = Kp;
    _Ki = Ki;
    _Kd = Kd;
    _goalValue = 0;
    _integral = 0;
    _maxIntegral = 1000000;
    _previousError = 0;
  }

  /**
   * @brief 積分値上限を設定する
   * @param (float)maxIntegral
   */
  void setmaxIntegral(float maxIntegral)
  {
    _maxIntegral = maxIntegral;
  }

  /**
   * @brief 目標値を設定する
   * @param (float)goalValue
   */
  void setGoalValue(float goalValue)
  {
    _goalValue = goalValue;
  }

  /**
   * @brief 現在値を入力してPID制御の計算を実行する
   * @param (float)previousValue
   * @return (float)output
   */
  float calculate(float previousValue)
  {
    float error = _goalValue - previousValue;
    float errorDiff = error-_previousError;
    _previousError = error;
    _integral += error;
    _integral = min(max(_integral, -_maxIntegral), _maxIntegral);
    float output = _Kp * error + _Ki * _integral + _Kd * errorDiff;
    return output;
  }

private:
  float _Kp;
  float _Ki;
  float _Kd;
  float _goalValue;
  float _integral;
  float _maxIntegral;
  float _previousError;
};

#endif
