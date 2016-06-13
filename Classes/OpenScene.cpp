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
    
    winSize = Director::getInstance()->getWinSize();
    
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
    
    MenuItemImage * copyrightMenu = MenuItemImage::create("res/copyright_button.png", "res/copyright_button_press.png", CC_CALLBACK_1(OpenLayer::copyrightCallBack, this));
    copyrightMenu->setScale(0.2);
    
    auto copyButton = Menu::create(copyrightMenu, NULL);
    copyButton->setPosition(Vec2(winSize.width * 0.04, winSize.height * 0.06));
    this->addChild(copyButton);
    
    return true;
    
}

void OpenLayer::menuCallBack(cocos2d::Ref *sender){
    tsm->gotoPlayScene();
}

void OpenLayer::copyrightCallBack(cocos2d::Ref *sender){
    Sprite * copyrightText = Sprite::create("res/copyright_text.png");
    copyrightText->setPosition(Vec2(winSize.width * 0.2, winSize.height * 0.15));
    copyrightText->setScale(0.3, 0.3);
    copyrightText->setTag(1005);
    if (this->getChildByTag(1005)) {
        this->removeChildByTag(1005);
    }
    else
        this->addChild(copyrightText);
}
