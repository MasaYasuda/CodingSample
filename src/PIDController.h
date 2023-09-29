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
 * @param (double)Kp
 * @param (double)Ki
 * @param (double)Kd
 */
class PIDController
{
public:
  PIDController(double Kp, double Ki, double Kd)
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
   * @param (double)maxIntegral
   */
  void setmaxIntegral(double maxIntegral)
  {
    _maxIntegral = maxIntegral;
  }

  /**
   * @brief 目標値を設定する
   * @param (double)goalValue
   */
  void setGoalValue(double goalValue)
  {
    _goalValue = goalValue;
  }

  /**
   * @brief 現在値を入力してPID制御の計算を実行する
   * @param (double)nowValue
   * @return (double)output
   */
  double calculate(double nowValue)
  {
    double error = _goalValue - nowValue;
    double errorDiff = error-_previousError;
    _previousError = error;
    _integral += error;
    _integral = min(max(_integral, -_maxIntegral), _maxIntegral);
    double output = _Kp * error + _Ki * _integral + _Kd * errorDiff;
    return output;
  }

private:
  double _Kp;
  double _Ki;
  double _Kd;
  double _goalValue;
  double _integral;
  double _maxIntegral;
  double _previousError;
};

#endif
