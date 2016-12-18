
/**
 * @file      precompiled.h
 * @brief     使われる全てのヘッダーをここに記述します
 * @attention 依存度の低いものからインクルードしないといけない
 *
 * @author    y.akira
 * @date      2016.12.14
 */

// ========================================================
//                 Precompiled Header
// ========================================================
#ifndef _PRECOMPILED_H_
#define _PRECOMPILED_H_

// --------------------------------------------------------
// openFrameworks
// --------------------------------------------------------
#include "ofMain.h"

// --------------------------------------------------------
// oF Addons
// --------------------------------------------------------
#include "ofxAnimatable.h"
#include "ofxImGui.h"
#include "ofxJSON.h"
#include "ofxJoystick.h"
#include "ofxSceneManager.h"
#include "ofxScreenCurtain.h"

// --------------------------------------------------------
// Utils
// --------------------------------------------------------

// --------------------------------------------------------
// Applicaton
// --------------------------------------------------------
#include "ofApp.h"

// --------------------------------------------------------
// Actors
// --------------------------------------------------------
#include "Actors/actor.h"
#include "actorManager.h"

#include "Actors/Player/player.h"
#include "Actors/Player/stateManager.h"
#include "Actors/Player/playerState.h"
#include "Actors/Brick/brick.h"

// --------------------------------------------------------
// Scenes
// --------------------------------------------------------
#include "Scenes/scene.h"
#include "Scenes/gameTitle.h"
#include "Scenes/gameMain.h"
#include "Scenes/sandbox.h"

#endif // _PRECOMPILED_H_
