
/**
 * @file   uiManager.h
 * @brief  UIをマネージメントする関数群が置かれています
 *
 * @author y.akria
 * @date   2016.12.25
 */

#pragma once


//! UIを追加します
void AddUI(const shared_ptr<uiBase>& ui);

//! 登録されたUIのupdateを呼びます
void UpdateUIs(float deltaTime);

//! 登録されたUIのdrawを呼びます
void DrawUIs();

//! 登録されたUIのGuiを描画します
void DrawUIsGui();

//! 特定のUIを管理下から削除します
void DeleteUI(const string& name);
void DeleteUI(const int     tag);

//! 特定のUIを取得する
shared_ptr<uiBase> FindUI(const string& name);
shared_ptr<uiBase> FindUI(const int     tag);
