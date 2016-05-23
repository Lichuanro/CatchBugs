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
    this->bestScore = 0;
    this->currentScore = 0;
    
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


void StatusLayer::showOver(int current, int best){
    this->currentScore = current;
    this->bestScore = best;
    
}

void StatusLayer::gameStart(){
    Sprite * scoreLable = Sprite::create("res/scoreLabel.png");
    scoreLable->setPosition(Vec2(this->visibleSize.width * 0.85, this->visibleSize.height * 0.94));
    scoreLable->setScale(0.3, 0.3);
    this->addChild(scoreLable);
    
    scoreNumber = LabelAtlas::create("0", "res/numbers.png", 68, 110, '0');
    scoreNumber->setPosition(Vec2(this->visibleSize.width * 0.91, this->visibleSize.height * 0.925));
    scoreNumber->setScale(0.3,0.3);
    this->addChild(scoreNumber);
    
    this->showStart();
}

void StatusLayer::gamePlay(int score){

    sprintf(scoreString, "%d", score);
    scoreNumber->setString(scoreString);
    
    
}

void StatusLayer::gameOver(int currentScore, int bestScore){
    
}

