
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
  PLAYER,          ///< プレイヤー
  SPAWNER,         ///< スポナー
  BRICK,           ///< レンガ
  BRICK_SPAWNER,   ///< レンガスポナー
  BRICK_MANAGER,   ///< レンガ管理クラス
  WARPZONE,        ///< ワープゾーン
  WARP_MANAGER,    ///< ワープゾーン管理クラス
  TELEPORT_CURSOR, ///< テレポートカーソル
  CONSPECIES,      ///< 同種
};
