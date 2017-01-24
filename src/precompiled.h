
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
// Add a typedef for a shorter type name
class ofxJSONElement;
typedef ofxJSONElement ofxJSON;

#include "ofxJoystick.h"
#include "ofxSceneManager.h"
#include "ofxScreenCurtain.h"

// --------------------------------------------------------
// Utils
// --------------------------------------------------------
#include "Utils/gameLocal.h"
#include "Utils/actorManager.h"
#include "Utils/uiManager.h"
#include "Utils/input.h"
#include "Utils/yCamera.h"

// --------------------------------------------------------
// Sound
// --------------------------------------------------------
#include "Sound/soundTags.h"
#include "Sound/soundManager.h"

// --------------------------------------------------------
// Score
// --------------------------------------------------------
#include "Score/scoreManager.h"

// --------------------------------------------------------
// Applicaton
// --------------------------------------------------------
#include "ofApp.h"

// --------------------------------------------------------
// BackGround
// --------------------------------------------------------
#include "BackGround/backGround.h"

// --------------------------------------------------------
// UserInterface
// --------------------------------------------------------
#include "UserInterface/uiTags.h"
#include "UserInterface/uiBase.h"

#include "UserInterface/uiMeter.h"

#include "UserInterface/uiScoreRank.h"

// --------------------------------------------------------
// Actors
// --------------------------------------------------------
#include "Actors/actorTags.h"
#include "Actors/actor.h"
#include "Actors/spawner.h"

#include "Actors/Particle/particleSystem.h"

#include "Actors/Player/player.h"
#include "Actors/Player/stateManager.h"
#include "Actors/Player/playerState.h"
#include "Actors/Player/teleportCursor.h"

#include "Actors/Brick/conspecies.h"
#include "Actors/Brick/brick.h"
#include "Actors/Brick/brickManager.h"
#include "Actors/Brick/brickSpawner.h"

#include "Actors/WarpZone/warpZone.h"
#include "Actors/WarpZone/warpManager.h"

#include "Actors/Leveler/leveler.h"

// --------------------------------------------------------
// Scenes
// --------------------------------------------------------
#include "Scenes/scene.h"
#include "Scenes/gameTitle.h"
#include "Scenes/gameMain.h"
#include "Scenes/yanaiScene.h"
#include "Scenes/wemScene.h"
#include "Scenes/ninjaScene.h"

#endif // _PRECOMPILED_H_
