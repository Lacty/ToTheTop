
/**
 * @file   yanaiScene.h
 * @brief  テストシーン
 *
 * @author y.akira
 * @date   2016.12.21
 */

#include "precompiled.h"


const static char* eases_list[] = {
  "EASE_IN_EASE_OUT",
  "EASE_IN",
  "EASE_OUT",
  "LINEAR",
  "EARLY_LINEAR",
  "LATE_LINEAR",
  "VERY_LATE_LINEAR",
  "BOUNCY",
  "OBJECT_DROP",
  "TANH",
  "SINH",
  "EARLY_SQUARE",
  "SQUARE",
  "LATE_SQUARE",
  
  "BLINK_5",
  "BLINK_3",
  "BLINK_2",
  "BLINK_AND_FADE_1",
  "BLINK_AND_FADE_2",
  "BLINK_AND_FADE_3",
  
  "LATE_EASE_IN_EASE_OUT",
  "VERY_LATE_EASE_IN_EASE_OUT",
  "QUADRATIC_EASE_IN",
  "QUADRATIC_EASE_OUT",
  "EARLY_QUADRATIC_EASE_OUT",
  
  "QUADRATIC_BEZIER_PARAM",
  
  "CUBIC_BEZIER_PARAM",
  
  "EXPONENTIAL_SIGMOID_PARAM",
  
  "SWIFT_GOOGLE",
  
  "EASE_IN_BOUNCE",
  "EASE_OUT_BOUNCE",
  "EASE_IN_OUT_BOUNCE",
  "EASE_OUT_IN_BOUNCE",
  "EASE_IN_BACK",
  "EASE_OUT_BACK",
  "EASE_IN_OUT_BACK",
  "EASE_OUT_IN_BACK",
  
  "EASE_IN_ELASTIC",
  "EASE_OUT_ELASTIC",
  "EASE_IN_OUT_ELASTIC",
  "EASE_OUT_IN_ELASTIC",
  
  "BOUNCE_IN_CUSTOM",
  "BOUNCE_OUT_CUSTOM",
  
  "SMOOTH_STEP",
  "SMOOTHER_STEP",
  
  "NUM_ANIM_CURVES"
};

void YanaiScene::setup() {
  cam_.setup();
  bg_.setup();
  
  originPos_.set(-70, 100);
  destPos_.set(-70, -100);
  brickSize_.set(24, 24);
  round_ = 4;
  time_ = 0.3;
  
  AddActor(make_shared<BrickManager>());
}

void YanaiScene::update(float deltaTime) {
  bg_.update(deltaTime);
  UpdateActors(deltaTime);
  
  //auto pos = cam_.getPosition();
  //pos.y += 0.1;
  //cam_.setPosition(pos);
}

void YanaiScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Yanai Scene", 20, 20);
  
  bg_.draw();
  
  cam_.begin();
  DrawActors();
  cam_.end();
}

// Gui用に独立した関数
void YanaiScene::gui() {
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

void YanaiScene::keyPressed(int key) {
  // 登録されたBrickを削除
  /*DeleteActors(BRICK);
  
  shared_ptr<Brick> temp = make_shared<Brick>();
  
  temp->setPos(originPos_);              // 現在位置
  temp->setSize(brickSize_);             // サイズ
  temp->setRectRound(round_);            // 丸み
  temp->moveTo(destPos_,                 // 移動先
               AnimCurve(curve_),        // アニメーション
               time_);                   // 時間
  
  AddActor(temp);*/
  
  shared_ptr<BrickSpawner> spw = make_shared<BrickSpawner>();
  
  spw->setSpawnTime(1);
  spw->setPos(destPos_);
  spw->setSize(brickSize_);
  
  spw->set(AnimCurve(curve_), time_);
  
  AddActor(spw);
}
