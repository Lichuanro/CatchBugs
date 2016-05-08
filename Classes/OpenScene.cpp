//
//  OpenScene.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "OpenScene.hpp"

USING_NS_TIMELINE;

bool OpenLayer::init(){
    
    Size winSize = Director::getInstance()->getWinSize();
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    addChild(rootNode);
    
    Node * node = CSLoader::createNode("MainScene.csb");
    this->addChild(node);
    ActionTimeline * action = CSLoader::createTimeline("MainScene.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0, true);

    
    MenuItemImage * playMenu = MenuItemImage::create("res/play_button.png", "res/play_button_press.png", CC_CALLBACK_1(OpenLayer::menuCallBack, this));
    playMenu->setPosition(Vec2(winSize.width*0.05,winSize.height*(-0.35)));
    playMenu->setScale(0.65);
    
    auto menu = Menu::create(playMenu, NULL);
    this->addChild(menu);
    
    
    return true;
    
}

void OpenLayer::menuCallBack(cocos2d::Ref *pSender){
    tsm->gotoPlayScene();
}
