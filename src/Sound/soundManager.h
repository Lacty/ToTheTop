
/**
 * @file   soundManager.h
 * @brief  SE,BGMなどサウンド関係を管理します
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
  , DUCK                    ///< しゃがみ
  , JUMP                    ///< ジャンプ
  , TELEPORT_USE            ///< プレイヤーのテレポートSE
  , SOUND_NUM               ///< サウンドの数
};


//! ゲームで使うサウンドを全て読み込む
void LoadAllSound(const string& path);

//! サウンドの取得
shared_ptr<ofSoundPlayer> FindSound(SoundTag tag);

//! サウンドの再生
void PlaySound(SoundTag tag);

//! サウンドを止める
void StopSound(SoundTag tag);
