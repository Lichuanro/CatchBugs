//
//  ControlLayer.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/13.
//
//

#include "ControlLayer.hpp"

ControlLayer::ControlLayer(){
    
}

ControlLayer::~ControlLayer(){
    
}

bool ControlLayer::init(){
    if (Layer::init()) {
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(ControlLayer::onTouchesBegan, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        return true;
    }
    else return false;
}

void ControlLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event){
    this->delegator->onTouch();
}