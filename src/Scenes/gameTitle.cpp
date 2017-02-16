/**
* @file   gameTitle.h
* @brief  ゲームタイトルのシーンです
*
* @author y.akira
* @date   2016.12.14
*/

#include "precompiled.h"


void GameTitle::setup() {
  cam_.setup();
  bg_.setup();

  AddUI(make_shared<uiTitle>());

  //auto brickMgr = make_shared<BrickManager>();
  //wp_brickMgr_ = brickMgr;
  //AddActor(brickMgr);

  ofxJSON json;
  json.open("Actor/brickManager.json");

  // 画面分割数を取得
  auto column = json["Column"].asInt();
  auto verticalLimit = json["Limit"].asInt();

  // Brickのサイズを求める
  ofVec2f brickSize;
  {
    float size = (float)g_local->Width() / column;
    brickSize = ofVec2f(size, size);
  }

  // Brickで足場を生成
  for (int i = 0; i < column; i++) {
    auto brick = make_shared<Brick>();
    brick->setPos({ i * brickSize.x, (float)g_local->Height(), 0 });
    brick->setSize(brickSize);
    brick->moveTo(i * brickSize.x, 0, AnimCurve::EASE_IN_EASE_OUT, i * 0.1f + 0.5f);
    AddActor(brick);
  }

  auto player = make_shared<Player>();
  player->setPos(g_local->WindowHalfSize());
  shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
  spwPlayer->setActor(player);
  spwPlayer->setSpawnTime(2);
  AddActor(spwPlayer);
  wp_player_ = player;

  ofxJSON userJson;
  userJson.open("user.json");
  w_ = userJson["Window"]["width"].asInt();
  h_ = userJson["Window"]["height"].asInt();
  auto wRatio = g_local->Width() / (float)w_;
  auto hRatio = g_local->Height() / (float)h_;

  shared_ptr<WarpZone> warpZone = make_shared<WarpZone>();
  warpZone->setPos(ofVec2f(g_local->Width() - (70 * wRatio), g_local->HalfHeight() + (100 * hRatio)));
  warpZone->setDistination(ofVec2f(g_local->HalfWidth(), g_local->Height() + warpZone->getPos().y));
  AddActor(warpZone);

  spawn_ = false;
}

void GameTitle::update(float deltaTime) {
  bg_.update(deltaTime);
  UpdateActors(deltaTime);
  UpdateUIs(deltaTime);

  // ＢＧＭのループと別シーンのＢＧＭを止める
  if (!isSoundPlaying(TITLE_BGM)) { PlaySound(TITLE_BGM); }
  if (isSoundPlaying(GAME_BGM))   { StopSound(GAME_BGM); }
  if (isSoundPlaying(RESULT_BGM)) { StopSound(RESULT_BGM); }

  stageSpawn();

  if (nextSceneTrriger()) { getManager()->goToScene(Scene::GAME); }
}

void GameTitle::draw() {
  bg_.draw();

  cam_.begin();
  DrawActors();
  cam_.end();

  DrawUIs();


  // プレイヤーが画面より下に出たらシーンをリロードする
  if (auto player = wp_player_.lock()) {
    if (player->getPos().y < 0) {
      getManager()->goToScene(TITLE);
    }
  }
}

void GameTitle::gui() {
  // 背景のGuiを描画
  bg_.gui();

  // アクターのGuiを描画
  DrawActorsGui();

  // UIのGuiを描画
  DrawUIsGui();
}

void GameTitle::exit() {
  ClearActors();
  ClearUIs();
}

void GameTitle::stageSpawn() {
  
  //コンストラクターで生成されたブロックを一旦消去
  if (!wp_brickMgr_.lock()) {
  wp_brickMgr_ = dynamic_pointer_cast<BrickManager>(FindActor(BRICK_MANAGER));
  return;
  }
  if (auto brickMgr = wp_brickMgr_.lock()) {
    if (brickMgr->shouldUpdate()) {
      brickMgr->disableUpdate();
    }
  }
  //ブロックを平坦に配置する
  if (!spawn_) {
  DeleteActors(BRICK);
  if (auto brickMgr = wp_brickMgr_.lock()) {
  for (int i = 0; i < 5; i++) {
  brickMgr->createBrick(i, 0);
  }
  }
  spawn_ = true;
  }
  
}

bool GameTitle::nextSceneTrriger() {
  //プレイヤーが画面外に出たらシーンを移動
  if (auto player = wp_player_.lock()) {
    if (player->getPos().y >= g_local->Height()) {
      return true;
    }
    else return false;
  }
}