//
//  Rain.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/6/1.
//
//
#include <iostream>
#include "Rain.hpp"
Rain::Rain(){
    
}

Rain::~Rain(){
    
}

bool Rain::init(){
    visibleSize = Director::getInstance()->getVisibleSize();
    createRains();
    isRaining = false;
    rainSymbolAdded = false;
    return true;
}

void Rain::createRains(){
    
    Sprite * rainDrop = NULL;
    for (int i = 0; i < 300; i++) {
        rainDrop = Sprite::create("res/rain.png");
        rainDrop->setAnchorPoint(Vec2(0.5,0.5));
        rainDrop->setScale(0.2, 0.2);
        rainDrop->setPosition(Vec2(visibleSize.width * random(0.0, 1.0),visibleSize.height * random(1.2, 20.0)));
        
        auto body = PhysicsBody::create();
        body->addShape(PhysicsShapeCircle::create(25));
        body->setMass(0.3);
        body->setLinearDamping(1.4);
        body->setVelocityLimit(600.0f);
        
        rainDrop->setPhysicsBody(body);

        rains.pushBack(rainDrop);
    }

}

void Rain::addRainSymbol(){
    rainSymbol = Sprite::create("res/rain_symbol.png");
    rainSymbol->setAnchorPoint(Vec2(0.5,0.5));
    rainSymbol->setScale(0.12, 0.12);
    rainSymbol->setPosition(Vec2(visibleSize.width * 0.04, visibleSize.height * 0.94));
    
    this->addChild(rainSymbol);
    rainSymbolAdded = true;
    
    SimpleAudioEngine::getInstance()->playEffect("res/rain.wav", true);
    
}

void Rain::removeRainSymbol(){
    this->removeChild(rainSymbol);
    rainSymbolAdded = false;
    
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void Rain::startRain(float dt){
    for (auto rainDrop :rains) {
        this->addChild(rainDrop);
    }
    isRaining = true;
    addRainSymbol();
}

void Rain::stopRain(float dt){
    checkRaining();
    if (isRaining == false && rainSymbolAdded) {
        removeRainSymbol();
    }
    if (isRaining == true && !rainSymbolAdded) {
        addRainSymbol();
    }
}

void Rain::clearRainDrops(float dt){
    for (auto rainDrop :rains) {
        if (rainDrop->getPositionY() < visibleSize.height * 0.01) {
            this->removeChild(rainDrop);
            rainDrop->getPhysicsBody()->setVelocity(Vec2(0,0));
            rainDrop->getPhysicsBody()->resetForces();
            rainDrop->setPosition(Vec2(visibleSize.width * random(0.0, 1.0),visibleSize.height * random(1.2, 8.0)));
        }
    }
}

void Rain::checkRaining(){
    isRaining = false;
    for (auto rainDrop : rains) {
        if (rainDrop->getPositionY() < visibleSize.height && rainDrop->getPositionY() > 0) {
            isRaining = true;
        }
    }
}

void Rain::rainAtRandom(){
    schedule(schedule_selector(Rain::startRain), 15.0f + random(0.0, 30.0), -1, 0.0f);
    schedule(schedule_selector(Rain::clearRainDrops));
    schedule(schedule_selector(Rain::stopRain));
}

void Rain::pause(){
    for (auto rainDrop : rains) {
        rainDrop->getPhysicsBody()->setEnabled(false);
    }
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void Rain::resume(){
    for (auto rainDrop : rains) {
        rainDrop->getPhysicsBody()->setEnabled(true);
    }
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}


