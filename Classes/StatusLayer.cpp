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

    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->originPoint = Director::getInstance()->getVisibleOrigin();

    isNewRecord = false;
    
    this->showReady();
    
    return true;
    
}

void StatusLayer::showReady(){
//    count3=Sprite::create("res/3.png");
//    count3->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    count2=Sprite::create("res/2.png");
//    count2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    count1=Sprite::create("res/1.png");
//    count1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    this->addChild(count3);
//    this->addChild(count2);
//    this->addChild(count1);
    click = Sprite::create("res/click.png");
    click->setScale(0.6, 0.6);
    click->setPosition(Vec2(visibleSize.width * 0.52, visibleSize.height * 0.55));
    
    auto blink = Blink::create(18.0f, 10);
    click->runAction(blink);
    
    this->addChild(click);

}


void StatusLayer::showStart(){
    this->removeChild(click);

}


void StatusLayer::backgroundBlur(){
    Sprite * backgroundEnd = Sprite::create("res/background_end.png");
    backgroundEnd->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    backgroundEnd->setScale(0.8, 0.9);
    this->addChild(backgroundEnd);
    
}

void StatusLayer::gameStart(){
    Sprite * scoreLable = Sprite::create("res/scoreLabel.png");
    scoreLable->setPosition(Vec2(this->visibleSize.width * 0.85, this->visibleSize.height * 0.94));
    scoreLable->setScale(0.3, 0.3);
    this->addChild(scoreLable);
    
    scoreNumber = LabelAtlas::create(scoreString, "res/numbers.png", 68.8, 110, '0');
    scoreNumber->setPosition(Vec2(this->visibleSize.width * 0.91, this->visibleSize.height * 0.925));
    scoreNumber->setScale(0.3,0.3);
    this->addChild(scoreNumber);
    
    Sprite * bestScoreLable = Sprite::create("res/best.png");
    bestScoreLable->setPosition(Vec2(this->visibleSize.width * 0.87, this->visibleSize.height * 0.89));
    bestScoreLable->setScale(0.2, 0.2);
    this->addChild(bestScoreLable);
    
    sprintf(bestScoreString, "%d", bestScore);
    
    bestScoreNumber = LabelAtlas::create(bestScoreString, "res/numbers.png", 68.8, 110, '0');
    bestScoreNumber->setAnchorPoint(Vec2(0.5,0.5));
    bestScoreNumber->setPosition(Vec2(this->visibleSize.width * 0.92, this->visibleSize.height * 0.898));
    bestScoreNumber->setScale(0.2,0.2);
    this->addChild(bestScoreNumber);
    
    this->showStart();
}

void StatusLayer::gamePlay(int score){

    sprintf(scoreString, "%d", score);
    scoreNumber->setString(scoreString);
    
    if (score > bestScore) {
        isNewRecord = true;
        bestScore = score;
        sprintf(bestScoreString, "%d", bestScore);
        bestScoreNumber->setString(bestScoreString);
    }
    
    
}

void StatusLayer::gameOver(int bestScore){
    
    backgroundBlur();
    
    Sprite * gameOverBoard;
    gameOverBoard = Sprite::create("res/gameover.png");
    gameOverBoard->setScale(0.55, 0.55);
    gameOverBoard->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(gameOverBoard);
    
    LabelAtlas * finalScoreNumber = LabelAtlas::create(scoreString, "res/numbers.png", 68.8, 110, '0');
    finalScoreNumber->setAnchorPoint(Vec2(0.5,0.5));
    finalScoreNumber->setPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height * 0.51));
    finalScoreNumber->setScale(0.9,0.9);
    if (isNewRecord) {
        Sprite * newRecord = Sprite::create("res/new_record.png");
        newRecord->setPosition(Vec2(visibleSize.width * 0.66, visibleSize.height * 0.48));
        newRecord->setScale(0.4, 0.4);
        newRecord->setRotation(30);
        this->addChild(newRecord);
        
        isNewRecord = false;
    }
    else{
        
        Sprite * bestScoreLable = Sprite::create("res/best.png");
        bestScoreLable->setPosition(Vec2(this->visibleSize.width * 0.6, this->visibleSize.height * 0.45));
        bestScoreLable->setScale(0.4, 0.4);
        this->addChild(bestScoreLable);
        
        bestScoreNumber->setPosition(Vec2(this->visibleSize.width * 0.68, this->visibleSize.height * 0.462));
        bestScoreNumber->setScale(0.35,0.35);
        this->addChild(bestScoreNumber);
        
    }
    
    this->addChild(finalScoreNumber);
    
    this->addReplayButton();
    this->addEndButton();
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

void StatusLayer::endButtonCallBack(Ref *sender){
    Director::getInstance()->end();
    exit(0);
}

void StatusLayer::addEndButton(){
    MenuItemImage * endMenu = MenuItemImage::create("res/end_button.png", "res/end_button_press.png", CC_CALLBACK_1(StatusLayer::endButtonCallBack, this));
    endMenu->setScale(0.3);
    
    auto menu = Menu::create(endMenu,NULL);
    menu->setPosition(Vec2(this->visibleSize.width * 0.62, this->visibleSize.height*0.35));
    this->addChild(menu);

}

