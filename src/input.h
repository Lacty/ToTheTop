
/**
* @file   input.h
* @brief  デバイスのボタン配列を管理するクラス
*
* @author wem
* @date   2016.12.20
*/

#pragma once


class Input {
public:
  static int Left;
  static int Right;
  static int Up;
  static int Down;
  static int X;
  static int Y;
  static int A;
  static int B;

  // jsonファイルからボタン配列を読み込む
  static void setup(const string& path);
};
