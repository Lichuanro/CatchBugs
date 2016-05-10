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

void PlayLayer::menuCallBack(cocos2d::Ref *pSender){
    
}