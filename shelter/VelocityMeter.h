/**
 * @file VelocityMeter.h
 * @brief エンコーダー値から速度を測定するモジュール
 * @author Yasuda Masanaga
 * @date 2023-9-27
 */

#ifndef VELOCITYMETER_H
#define VELOCITYMETER_H

#include <Arduino.h>
#include <math.h>
#include <Encoder.h>
#include <TimerOne.h>

/**
 * @brief エンコーダー値から速度を計算するモジュール
 * @param (uint8_t)pinA エンコーダーA相のピン
 * @param (uint8_t)pinB エンコーダーB相のピン
 * @param (int)resolution エンコーダーの分解度
 * @param (double)diameter 回転円盤(車輪・ローラー)の直径(mm)
 * @note 20msごとに速度が更新される
 */

class SpeedMeter : public Encoder
{
public:
  SpeedMeter(uint8_t pinA, uint8_t pinB, int resolution, double diameter) : Encoder(pinA, pinB)
  {

    Timer1.initialize(20 * 1000); // 20msごとに割込み
    Timer1.attachInterrupt(timerCalculate);
  }


  /**
   * @brief タイマ割込み時実行関数
   * @note publicで定義されているが、絶対にクラス外から呼び出さないこと。
  */
  static void timerCalculate()
  {
    long nowInterruptTime = micros();
    double timeDiff = (double)(nowInterruptTime - _previousInterruptTime) / 1000000.0;
    long positionDiff = (long)Encoder::read() - _previousPosition;
    _rpm = (double) positionDiff / (_resolution * timeDiff);
    _speed = (double)_rpm * PI * _diameter / 1000.0;
    _previousInterruptTime = nowInterruptTime;
  }

  /**
   * @brief 現在の速度[m/s]を返す
   * @return (double)speed
  */
  double speedRead()
  {
    return _speed;
  }

  /**
   * @現在の回転数(rpm)を返す
   * @return (double)rpm
  */
  double rpmRead()
  {
    return _rpm;
  }

private:
  static int _resolution;
  static double _diameter;
  static volatile double _previousPosition;
  static volatile long _previousInterruptTime;
  static volatile double _rpm;
  static volatile double _speed; //[m/s]
};

#endif
