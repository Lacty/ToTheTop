
/**
 * @file   actorTags.h
 * @brief  Actorのタグをまとめで管理する
 *
 * @author y.akira
 * @date   2016.12.28
 */

#pragma once


/**
 * @brief アクターのタグをまとめる
 */
enum ActorTags {
  LEVELER,         ///< ゲーム難度調整クラス
  WARP_MANAGER,    ///< ワープゾーン管理クラス
  BRICK_MANAGER,   ///< レンガ管理クラス
  SPAWNER,         ///< スポナー
  BRICK_SPAWNER,   ///< レンガスポナー
  WARPZONE,        ///< ワープゾーン
  BRICK,           ///< レンガ
  CONSPECIES,      ///< 仲間
  PARTICLE,        ///< 通常パーティクル
  PARTICLE_SYSTEM, ///< パーティクル管理クラス
  HOMING_PARTICLE, ///< 追従パーティクル
  TELEPORT_CURSOR, ///< テレポートカーソル
  PLAYER,          ///< プレイヤー
};
