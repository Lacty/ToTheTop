
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
  cam_.setPosition(0, 0, 300);
  bg_.setup();
  
  originPos_.set(-70, 100);
  destPos_.set(-70, -100);
  brickSize_.set(24, 24);
  round_ = 4;
  time_ = 0.3;
}

void YanaiScene::update(float deltaTime) {
  bg_.update(deltaTime);
  UpdateActors(deltaTime);
}

void YanaiScene::draw() {
  ofSetColor(0, 0, 0);
  ofDrawBitmapString("Yanai Scene", 20, 20);
  
  bg_.draw();
  
  cam_.begin();
  DrawActors();
  cam_.end();
  
  // | GUI |-------------------------------------------------------------------------------
  ImGui::Begin("Brick Param");
    ImGui::Text("%s", "Press any key to Create");
    ImGui::DragFloat2("Origin Pos", originPos_.getPtr());
    ImGui::DragFloat2("Dest Pos", destPos_.getPtr());
    ImGui::DragFloat2("Size", brickSize_.getPtr());
    ImGui::SliderFloat("Round", &round_, 0, 20);
    ImGui::SliderFloat("Fall Time", &time_, 0, 3);
  
    if (ImGui::ListBox("Ease Select", &curve_, eases_list, NUM_ANIM_CURVES))
     { ofLog() << "ease : " << curve_; }
  ImGui::End();
}

void YanaiScene::keyPressed(int key) {
  // 登録されたBrickを削除
  DeleteActors(BRICK);
  
  shared_ptr<Brick> temp = make_shared<Brick>();
  
  temp->setPos(originPos_);              // 現在位置
  temp->setSize(brickSize_);             // サイズ
  temp->setRectRound(round_);            // 丸み
  temp->moveTo(destPos_,                 // 移動先
               AnimCurve(curve_),        // アニメーション
               time_);                   // 時間
  
  AddActor(temp);
}
