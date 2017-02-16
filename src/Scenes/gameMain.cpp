
/**
* @file   gameMain.h
* @brief  ゲームメインのシーンです
*
* @author y.akira
* @date   2016.12.14
*/

#include "precompiled.h"


void GameMain::moveCam() {
  ofVec2f pos = cam_.getPos();
  if (auto player = player_.lock()) {
    if (pos.y + camOffsetMax_ <= player_.lock()->getPos().y) {
      int offset = player_.lock()->getPos().y - (pos.y + camOffsetMax_);
      pos.y += offset;
      cam_.setPos(pos);
    }
    if (pos.y + camOffsetMin_ >= player_.lock()->getPos().y) {
      int offset = player_.lock()->getPos().y - (pos.y + camOffsetMin_);
      pos.y += offset;
      cam_.setPos(pos);
    }
  }

}

void GameMain::setup() {
  cam_.setup();
  bg_.setup();

  shared_ptr<Player> sp_player = make_shared<Player>();
  sp_player->setPos(g_local->WindowHalfSize());

  shared_ptr<Spawner> spwPlayer = make_shared<Spawner>();
  spwPlayer->setActor(sp_player);
  spwPlayer->setSpawnTime(1);
  AddActor(spwPlayer);

  player_ = sp_player;

  camOffsetMax_ = g_local->Height() * 0.6f;
  camOffsetMin_ = g_local->Height() * 0.2f;

  resultTimer_ = 0.0f;

  AddActor(make_shared<WarpManager>());

  AddActor(make_shared<Leveler>());
}

void GameMain::exit() {
  // 登録されたアクターとUIを削除
  ClearActors();
  ClearUIs();
}

void GameMain::update(float deltaTime) {
  moveCam();

  if (auto meter = meter_.lock()) {
    meter->setCamY(cam_.getPos().y);
  }
  else {
    meter = dynamic_pointer_cast<uiMeter>(FindUI(METER));
    meter_ = meter;
  }

  if (auto resque = resque_.lock()) {
    resque->setCamY(cam_.getPos().y);
  }
  else {
    resque = dynamic_pointer_cast<uiResque>(FindUI(RESQUE));
    resque_ = resque;
  }

  bg_.update(deltaTime);

  UpdateActors(deltaTime);
  UpdateUIs(deltaTime);

  if (!player_.lock()) {
    player_ = dynamic_pointer_cast<Player>(FindActor(PLAYER));
    return;
  }

  // シーン遷移時にタイトルＢＧＭを止める
  if (isSoundPlaying(TITLE_BGM)) { StopSound(TITLE_BGM); }

  if (auto player = player_.lock()) {
    // プレイヤーが生きていれば
    if (!player_.lock()->isDead()) {
      if (!isSoundPlaying(GAME_BGM)) { PlaySound(GAME_BGM); }
    }
    // 死んでいれば
    else {
      resultTimer_ += deltaTime;
      if (!isSoundPlaying(RESULT_BGM)) { PlaySound(RESULT_BGM); }
      if (isSoundPlaying(GAME_BGM))    { StopSound(GAME_BGM); }
      // タイトルへの遷移処理(一定時間経過してからボタンを押したら)
      if (resultTimer_ > 6 && player_.lock()->isPushButton()) {
        getManager()->goToScene(Scene::TITLE);
      }
    }
  }
}

void GameMain::draw() {
  bg_.draw();

  cam_.begin();
  DrawActors();
  cam_.end();

  DrawUIs();
}

// Gui用に独立した関数
void GameMain::gui() {
  if (ImGui::BeginMenu("YanaiScene")) {
    ImGui::Text("this is test scene.");
    ImGui::EndMenu();
  }

  // 背景のGuiを描画
  bg_.gui();

  // アクターのGuiを描画
  DrawActorsGui();

  // UIのGuiを描画
  DrawUIsGui();
}
