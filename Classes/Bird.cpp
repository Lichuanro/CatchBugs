//
//  Bird.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/10.
//
//

#include "Bird.hpp"
#include "cocos2d.h"

USING_NS_CC;

bool Bird::init(){
    return true;
}

Bird::Bird(){

}

Bird::~Bird(){
    if (readyAction) {
        readyAction->release();
        readyAction = NULL;
    }
    if (flyAction) {
        flyAction->release();
        flyAction = NULL;
    }
    
}

Bird * Bird::shareBird = nullptr;
Bird * Bird::getInstance(){
    if (shareBird == NULL) {
        shareBird = (Bird*)Sprite::create("res/bird1.png");
        Size winSize = Director::getInstance()->getWinSize();
        shareBird->setPosition(Vec2(winSize.width/2, winSize.height/2));
        shareBird->setScale(0.08, 0.08);
    }
    return shareBird;
}


Bird* Bird::createBird(){

    Animation * readyAnimation = Animation::create();
    readyAnimation->addSpriteFrameWithFile("res/bird1.png");
    readyAnimation->addSpriteFrameWithFile("res/bird2.png");
    readyAnimation->setDelayPerUnit(0.15);
    readyAnimation->setRestoreOriginalFrame(true);
    readyAnimation->setLoops(-1);
    
    this->readyAction = Animate::create(readyAnimation);
    
    
    
    Animation * flyAnimation = Animation::create();
    flyAnimation->addSpriteFrameWithFile("res/bird1.png");
    flyAnimation->addSpriteFrameWithFile("res/bird2.png");
    
    flyAnimation->setDelayPerUnit(0.2);
    flyAnimation->setRestoreOriginalFrame(true);
    flyAnimation->setLoops(2);
    this->flyAction = Animate::create(flyAnimation);
    
    ActionInterval * up = MoveBy::create(0.4f, Point(0,8));
    ActionInterval * down = up->reverse();
    
    this->moveAction = RepeatForever::create(Sequence::create(up,down, NULL));

    return this;
    
}

bool Bird::changeState(ActionState actionState){
    current_actionState = actionState;
    return true;
    
}


void Bird::ready(){
    changeState(READY_ACTION);
    this->runAction(readyAction);
    this->runAction(moveAction);
    
}

void Bird::fly(){
    changeState(FLY_ACTION);
    this->getPhysicsBody()->setGravityEnable(true);
    
}

void Bird::swing(){
    changeState(SWING_ACTION);
 //   this->stopAllActions();
 //   this->runAction(flyAction);
 //   this->runAction(moveAction);
    
}

void Bird::catchBugs(){
    changeState(CATCHBUGS_ACTION);
    this->runAction(moveAction);
    
}

void Bird::die(){
    changeState(DIE_ACTION);
    this->stopAllActions();
    
}
