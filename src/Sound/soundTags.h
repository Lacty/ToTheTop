
/**
 * @file   soundTags.h
 * @brief  サウンドのタグを管理します
 *
 * @author y.akira
 * @date   2017.01.15
 */

#pragma once


/**
 * @brief     サウンドのタグ
 * @attention jsonと同じ並びにしてください
 */
enum SoundTag {
  TELEPORT_REUSEABLE      ///< テレポート再使用可能
  , DUCK_START            ///< しゃがみ
  , JUMP_START            ///< ジャンプ
  , TELEPORT_USE          ///< プレイヤーのテレポートSE
  , SOUND_NUM             ///< サウンドの数
};
