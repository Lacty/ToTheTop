
/**
 * @file   actorManager.h
 * @brief  アクターをマネージメントする関数群が置かれています
 *
 * @author y.akria
 * @date   2016.12.14
 */

#pragma once


//! アクターを追加します
void AddActor(const shared_ptr<Actor>& actor);

//! 登録されたアクターのupdateを呼びます
void UpdateActors(float deltaTime);

//! 登録されたアクターのdrawを呼びます
void DrawActors();

/*
//! 特定のアクターを管理下から削除します
void DeleteActorsFromName(const string& name);

//! 特定のアクターを管理下から削除します
void DeleteActorsFromTag(const int tag);
*/
