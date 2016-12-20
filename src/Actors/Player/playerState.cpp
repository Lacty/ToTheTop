
/**
 * @file   playerState.h
 * @brief  プレイヤーの状態
 *
 * @author y.akira
 * @date   2016.12.20
 */

#include "precompiled.h"


/**
 * @brief 起動後に一度呼ばれます
 * @param [in] player プレイヤーのポインタが入ります
 */
void StateBase::setup(Player* player) {}

/** 
 * @brief 入力により状態を変更するために毎フレーム呼ばれます
 * @param [in] player   プレイヤーのポインタが入ります
 * @param [in] stateMgr 状態管理クラスがポインタで入ります
 * @param [in] input    ゲームパッドの入力判定が参照で入ります
 */
void StateBase::handleInput(Player* player, StateManager* stateMgr, ofxJoystick& input) {}

/**
 * @brief 毎フレーム呼ばれます
 * @param [in] deltaTime フレーム間にかかったゲーム内仮想時間が入ります
 * @param [in] player    プレイヤーがポインタで入ります
 * @param [in] input     ゲームパッドの入力判定が参照で入ります
 */
void StateBase::update(float deltaTime, Player* player, ofxJoystick& input) {}

/**
 * @brief 描画用に毎フレーム呼ばれます
 * @param [in] player プレイヤーのポインタが入ります
 */
void StateBase::draw(Player* player) {}

/**
 * @brief プレイヤーが別のアクターと衝突した際に呼ばれます
 * @param [in] player  プレイヤーのポインタが入ります
 * @param [in] c_actor 衝突した相手がActorのポインタで入ります
 */
void StateBase::onCollision(Player* player, Actor* c_actor) {}
