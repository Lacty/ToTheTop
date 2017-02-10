
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
  // BGM
  GAME_BGM
  , RESULT_BGM
  , TITLE_BGM

  // SE
  , BRICK_IMPACT_1        ///< Brick落下終了音
  , BRICK_IMPACT_2        ///< Brick落下終了音
  , BRICK_IMPACT_3        ///< Brick落下終了音
  , CSP_CRUSH             ///< 仲間死亡時
  , RESCUE_CSP            ///< 仲間救出時
  , TELEPORT_REUSEABLE    ///< テレポート再使用可能
  , PLAYER_DEAD           ///< プレイヤー死亡時
  , DUCK_START            ///< しゃがみ
  , JUMP_START            ///< ジャンプ
  , TELEPORT_USE          ///< プレイヤーのテレポートSE
  , SLIDE_SCORE           ///< ランキング表示時
  , SOUND_NUM             ///< サウンドの数
};
