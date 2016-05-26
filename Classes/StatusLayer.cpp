//
//  StatusLayer.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/15.
//
//

#include "StatusLayer.hpp"
#include <stdio.h>

StatusLayer::StatusLayer(){
    
}
StatusLayer::~StatusLayer(){
    
}


bool StatusLayer::init(){
 //   this->bestScore = 0;
 //   this->currentScore = 0;
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->originPoint = Director::getInstance()->getVisibleOrigin();

    
    this->showReady();
    
    return true;
    
}

void StatusLayer::showReady(){
    count3=Sprite::create("res/3.png");
    count3->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    count2=Sprite::create("res/2.png");
    count2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    count1=Sprite::create("res/1.png");
    count1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    this->addChild(count3);
//    this->addChild(count2);
//    this->addChild(count1);
    
    score = Sprite::create();
    


}


void StatusLayer::showStart(){

}


void StatusLayer::showOver(int best){
    

    
}

void StatusLayer::gameStart(){
    Sprite * scoreLable = Sprite::create("res/scoreLabel.png");
    scoreLable->setPosition(Vec2(this->visibleSize.width * 0.85, this->visibleSize.height * 0.94));
    scoreLable->setScale(0.3, 0.3);
    this->addChild(scoreLable);
    
    scoreNumber = LabelAtlas::create(scoreString, "res/numbers.png", 68, 110, '0');
    scoreNumber->setPosition(Vec2(this->visibleSize.width * 0.91, this->visibleSize.height * 0.925));
    scoreNumber->setScale(0.3,0.3);
    this->addChild(scoreNumber);
    
    this->showStart();
}

void StatusLayer::gamePlay(int score){

    sprintf(scoreString, "%d", score);
    scoreNumber->setString(scoreString);
    
    
}

void StatusLayer::gameOver(int bestScore){
    
    Sprite * gameOverBoard;
    gameOverBoard = Sprite::create("res/gameover.png");
    gameOverBoard->setScale(0.55, 0.55);
    gameOverBoard->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(gameOverBoard);
    
    LabelAtlas * finalScore = LabelAtlas::create(scoreString, "res/numbers.png", 68, 110, '0');
    finalScore->setPosition(Vec2(this->visibleSize.width * 0.46, this->visibleSize.height * 0.44));
    finalScore->setScale(0.9,0.9);
    
    this->addChild(finalScore);
    
    this->addReplayButton();
}


void StatusLayer::replayButtonCallBack(Ref *sender){
    auto playScene = PlayScene::create();
    TransitionScene * transScene = TransitionFade::create(1, playScene);
    Director::getInstance()->replaceScene(transScene);
    
}

void StatusLayer::addReplayButton(){
    MenuItemImage * replayMenu = MenuItemImage::create("res/replay_button.png", "res/replay_button_press.png", CC_CALLBACK_1(StatusLayer::replayButtonCallBack, this));
    replayMenu->setScale(0.3);
    
    auto menu = Menu::create(replayMenu, NULL);
    menu->setPosition(Vec2(this->visibleSize.width * 0.38, this->visibleSize.height*0.35));
    this->addChild(menu);
    
}

