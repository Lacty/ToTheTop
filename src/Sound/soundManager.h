
/**
 * @file   soundManager.h
 * @brief  SE,BGMなどサウンド関係を管理します
 *
 * @author y.akira
 * @date   2017.01.15
 */

#pragma once


//! ゲームで使うサウンドを全て読み込む
void LoadAllSound(const string& path);

//! サウンドの取得
shared_ptr<ofSoundPlayer> FindSound(SoundTag tag);

//! サウンドの再生
void PlaySound(SoundTag tag);

//! サウンドを止める
void StopSound(SoundTag tag);
