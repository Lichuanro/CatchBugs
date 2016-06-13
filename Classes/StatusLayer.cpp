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
    Sprite * blur = Sprite::create("res/background_end.png");
    blur->setTag(1001);
    blur->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blur->setScale(0.8, 0.9);
    this->addChild(blur);
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
    
    this->addGamePauseButton();
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
    this->removeChildByTag(1004);
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
        newRecord->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.48));
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
    MenuItemImage * replay = MenuItemImage::create("res/replay_button.png", "res/replay_button_press.png", CC_CALLBACK_1(StatusLayer::replayButtonCallBack, this));
    replay->setScale(0.3);
    
    auto replayButton = Menu::create(replay, NULL);
    replayButton->setPosition(Vec2(this->visibleSize.width * 0.38, this->visibleSize.height*0.35));
    this->addChild(replayButton);
    
}

void StatusLayer::endButtonCallBack(Ref *sender){
    Director::getInstance()->end();
    exit(0);
}

void StatusLayer::addEndButton(){
    MenuItemImage * end = MenuItemImage::create("res/end_button.png", "res/end_button_press.png", CC_CALLBACK_1(StatusLayer::endButtonCallBack, this));
    end->setScale(0.3);
    
    auto endButton = Menu::create(end,NULL);
    endButton->setPosition(Vec2(this->visibleSize.width * 0.62, this->visibleSize.height*0.35));
    this->addChild(endButton);

}

void StatusLayer::addGamePauseButton(){
    MenuItemImage * pause = MenuItemImage::create("res/pause_button.png", "res/pause_button_press.png", CC_CALLBACK_1(StatusLayer::gamePauseButtonCallBack,this));
    pause->setScale(0.15,0.15);
    
    auto pauseButton = Menu::create(pause, NULL);
    pauseButton->setTag(1004);
    pauseButton->setPosition(Vec2(visibleSize.width * 0.77, visibleSize.height * 0.93));
    this->addChild(pauseButton);
}

void StatusLayer::setGamelayer(GameLayer *layer){
    this->gamelayer = layer;
}

void StatusLayer::gamePauseButtonCallBack(cocos2d::Ref *sender){
    Director::getInstance()->pause();
    gamelayer->gamePause();
    backgroundBlur();
    
    this->showPause();
    this->addGameResumeButton();
}

void StatusLayer::addGameResumeButton(){
    MenuItemImage * resume = MenuItemImage::create("res/resume_button.png", "res/resume_button_press.png", CC_CALLBACK_1(StatusLayer::gameResumeButtonCallBack, this));
    resume->setScale(0.35, 0.35);
    
    auto resumeButton = Menu::create(resume, NULL);
    resumeButton->setTag(1003);
    resumeButton->setPosition(Vec2(visibleSize.width/2,visibleSize.height * 0.44));
    
    this->addChild(resumeButton);
}

void StatusLayer::gameResumeButtonCallBack(cocos2d::Ref *sender){
    Director::getInstance()->resume();
    gamelayer->gameResume();
    this->removeChildByTag(1001);
    this->removeChildByTag(1002);
    this->removeChildByTag(1003);
}

void StatusLayer::showPause(){
    Sprite * pauseBoard  = Sprite::create("res/pause.png");
    pauseBoard->setTag(1002);
    pauseBoard->setScale(0.5, 0.5);
    pauseBoard->setAnchorPoint(Vec2(0.5,0.5));
    pauseBoard->setPosition(Vec2(visibleSize.width/2,visibleSize.height * 0.5));
    
    this->addChild(pauseBoard);
}
