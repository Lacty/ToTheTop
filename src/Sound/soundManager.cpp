
/**
 * @file   soundManager.cpp
 * @brief  SE,BGMなどサウンド関係を管理します
 *
 * @author y.akira
 * @date   2017.01.15
 */

#include "precompiled.h"


//! サウンドを配列で保管
vector<shared_ptr<ofSoundPlayer>> g_sounds;


/**
 * @brief ゲームで使うサウンドを全て読み込む
 */
void LoadAllSound(const string& path) {
  ofxJSON json;
  json.open(path);
  
  // enumとjson内の数に相違がないか確認
  unsigned int size = json["Sounds"].size();
  assert(size == SOUND_NUM); // 上記の理由によりエラー
  
  // 配列の初期化、メモリ確保
  g_sounds.clear();
  g_sounds.resize(SOUND_NUM);
  
  // サウンドの名前を配列で取得
  auto names = json["Sounds"].getMemberNames();
  
  // jsonまでのパスの取得
  string root = json["Root"].asString();
  
  // サウンドの読み込み
  for (unsigned int i = 0; i < SOUND_NUM; i++) {
    g_sounds[i] = make_shared<ofSoundPlayer>();
    g_sounds[i]->load(root + names[i]);
    
    // 読み込めてなかった時のためヌルチェック
    if (auto sound = g_sounds[i]) {
      auto j = json["Sounds"][names[i]];
    
      // パラメータの設定
      if (j.isMember("volume")) {
        sound->setVolume(j["volume"].asFloat());
      }
      if (j.isMember("speed")) {
        sound->setSpeed(j["speed"].asFloat());
      }
      if (j.isMember("loop")) {
        sound->setLoop(j["loop"].asBool());
      }
      if (j.isMember("multiplay")) {
        sound->setMultiPlay(j["multiplay"].asBool());
      }
    }
  }
}


/**
 * @brief サウンドの取得
 * @brief 細かな設定をしたい時に使用してください
 */
shared_ptr<ofSoundPlayer> FindSound(SoundTag tag) {
  return g_sounds[tag];
}

//! サウンドの再生
void PlaySound(SoundTag tag) {
  g_sounds[tag]->play();
}

//! サウンドを止める
void StopSound(SoundTag tag) {
  g_sounds[tag]->stop();
}
