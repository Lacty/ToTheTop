
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

//! 登録されたアクターのGuiを描画します
void DrawActorsGui();

//! 特定のアクターを管理下から削除します
void DeleteActors(const string& name);
void DeleteActors(const int     tag);

//! 特定のアクターを取得する
shared_ptr<Actor> FindActor(const string& name);
shared_ptr<Actor> FindActor(const int     tag);

//! 特定のアクターを配列で取得する
list<shared_ptr<Actor>> FindActorsList(const string& name);
list<shared_ptr<Actor>> FindActorsList(const int     tag);
