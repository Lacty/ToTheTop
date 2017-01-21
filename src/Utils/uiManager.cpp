
/**
 * @file   uiManager.cpp
 * @brief  UIをマネージメントする関数群が置かれています
 *
 * @author y.akria
 * @date   2016.12.25
 */

#include "precompiled.h"


//! @brief AddUIを使って登録されたUIはこのリストにまとめられます
std::list<shared_ptr<uiBase>> g_uisList;

/**
 * @brief UIを追加します
 * @param [in] ui 登録するui
 */
void AddUI(const shared_ptr<uiBase>& ui) {
  g_uisList.emplace_back(ui);
}

/**
 * @brief 登録されたUIのupdateを呼びます
 * @param [in] deltaTime 前のフレームから現在のフレームまでにかかった時間を与えます
 */
void UpdateUIs(float deltaTime) {
  for (auto& ui : g_uisList) {
    if (!ui->hasSetup()) {
      ui->setup();
      if (ui->shouldUpdate()) {
        ui->update(deltaTime);
      }
    }
    else
    // updateが有効になっていればupdateを実行
    if (ui->shouldUpdate()) {
      ui->update(deltaTime);
    }
  }
  
  // 削除対象のactorは削除する
  g_uisList.remove_if(
    [] (const shared_ptr<uiBase>& ui)->bool {
      return ui->isDead();
    }
  );
}

//! 登録されたUIのdrawを呼びます
void DrawUIs() {
  for (auto& ui : g_uisList) {
    ui->draw();
  }
}

void DrawUIsGui() {
  for (auto& ui : g_uisList) {
    ui->gui();
  }
}

/**
 * @brief登録されたUIを全て削除します
 */
void ClearUIs() {
  g_uisList.clear();
}

/**
 * @brief 特定のUIを管理下から削除対象にする
 * @param [in] name 削除したいUIの名前
 */
void DeleteUI(const string& name) {
  for (auto& ui : g_uisList) {
    if (ui->getName() == name)
      ui->destroy();
  }
}

/**
 * @brief 特定のUIを管理下から削除対象にする
 * @param [in] tag 削除したいUIのタグ
 */
void DeleteUI(const int tag) {
  for (auto& ui : g_uisList) {
    if (ui->getTag() == tag)
      ui->destroy();
  }
}

/**
 * @brief  特定のUIを取得する
 * @param  [in] name 取得したいアクターの名前
 * @retval アクターを指すスマポを返す
 * @note   見つからなければnullptrを返す
 */
shared_ptr<uiBase> FindUI(const string& name) {
  for (auto& ui : g_uisList) {
    if (ui->getName() == name) {
      return ui;
    }
  }
  
  // 見つからなければnullを返す
  return nullptr;
}

/**
 * @brief  特定のUIを取得する
 * @param  [in] tag 取得したいUIのタグ
 * @retval アクターを指すスマポを返す
 * @note   見つからなければnullptrを返す
 */
shared_ptr<uiBase> FindUI(const int tag) {
  for (auto& ui : g_uisList) {
    if (ui->getTag() == tag) {
      return ui;
    }
  }
  
  // 見つからなければnullを返す
  return nullptr;
}
