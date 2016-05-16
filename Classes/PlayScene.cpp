//
//  PlayScene.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

#include "PlayScene.hpp"

bool PlayLayer::init(){
    
    
    Size winSize = Director::getInstance()->getWinSize();
    
    background = Sprite::create("res/background.jpg");
    background->setPosition(Vec2(winSize.width/2,winSize.height/2));
    background->setScale(0.8, 0.9);
    this->addChild(background,0);

    
    return true;
    
}

void PlayScene::set_tsm(SceneManager * sceneManager){
    playLayer->tsm = sceneManager;
}

void PlayLayer::menuCallBack(cocos2d::Ref *pSender){
    
}

PlayScene::PlayScene(){
    
}

PlayScene::~PlayScene(){
    
}

bool PlayScene::init(){
    if (Scene::initWithPhysics()) {
        this->getPhysicsWorld()->setGravity(Vec2(0,-900));
        playLayer = PlayLayer::create();
        this->addChild(playLayer);
        
        auto statusLayer = StatusLayer::create();
    
        auto gameLayer = GameLayer::create();
        if (gameLayer) {
            gameLayer->setPhysicsWorld(this->getPhysicsWorld());
            gameLayer->setDelegator(statusLayer);
            this->addChild(gameLayer);
        }
        
        if (statusLayer) {
            this->addChild(statusLayer);
        }
        
        auto controlLayer = ControlLayer::create();
        if (controlLayer) {
            controlLayer->setDelegator(gameLayer);
            this->addChild(controlLayer);
        }
        return true;
    }
    else
        return false;
}

void PlayScene::restart(){
    this->removeAllChildrenWithCleanup(true);
    this->init();
}