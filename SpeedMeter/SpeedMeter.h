/**
 * @file SpeedMeter.h
 * @brief エンコーダー値から速度を測定するモジュール
 * @author Yasuda Masanaga
 * @date 2023-9-27 作成
 */

#ifndef VELOCITYMETER_H
#define VELOCITYMETER_H

#include <Arduino.h>
#include <math.h>
#include <Encoder.h>

class SpeedMeter;

/**
 * @brief エンコーダー値から速度を計算するモジュール
 * @param (uint8_t)pinA エンコーダーA相のピン
 * @param (uint8_t)pinB エンコーダーB相のピン
 * @param (int16_t)resolution エンコーダーの分解度(エンコーダーが1回転した時の.positionRead()の値)
 * @param (float)diameter 回転円盤(車輪・ローラー)の直径(mm)
 * @note 割込み不使用のため、あくまで"平均"速度を測定するモジュールであることに注意。
 */
class SpeedMeter : public Encoder
{
public:
  SpeedMeter(uint8_t pinA, uint8_t pinB, int16_t resolution, float diameter) : Encoder(pinA, pinB)
  {
    _resolution = resolution;
    _diameter = diameter;
    reset();
  }

  /**
   * @brief エンコーダーの値を読む
   * @return (long)
   */
  int32_t positionRead()
  {
    return Encoder::read();
  }

  /**
   * @現在の回転数(rpm)を読む
   * @return (float)rpm
   * @note 前回のspeedRead()から今のspeedRead()までの平均回転数を計算する
   */
  float rpmRead()
  {
    int32_t previousTime = micros();
    int32_t position = positionRead();
    float timeDiff = (float)(previousTime - _previousTime) / 60000000.0;
    int32_t positionDiff = position - _previousPosition;
    float rpm = (float)positionDiff / _resolution / timeDiff;
    _previousTime = previousTime;
    _previousPosition = position;
    return rpm;
  }

  /**
   * @brief 現在の速度[m/s]を読む
   * @return (float)speed [m/s]
   * @note 前回のspeedRead()から今のspeedRead()までの平均速度を計算する
   */
  float speedRead()
  {
    float rpm = rpmRead();
    float speed = rpm /60.0 * PI * _diameter / 1000.0;
    return speed;
  }

  /**
   * @brief rpmRead()またはspeedRead()してから長時間経った時のための基準点リセット用関数
   * @note 前回の**Read()から長時間経過している場合、次回の**Read()実行前に一度これを実行する。
   * @note ※速度計測の開始時刻およびエンコーダーの基準位置を現時点の値に再設定している
   */
  void reset()
  {
    _previousTime = micros();
    _previousPosition = positionRead();
  }

private:
  int16_t _resolution;
  float _diameter; //[mm]
  volatile float _previousPosition;    // この変数は、rpmRead()またはspeedRead()がタイマ割り込み関数内で使用された場合の対策のためvolatileで定義されています。
  volatile int32_t _previousTime; // この変数は、rpmRead()またはspeedRead()がタイマ割り込み関数内で使用された場合の対策のためvolatileで定義されています。
};

#endif
