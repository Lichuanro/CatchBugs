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
        shareBird->setScale(0.07, 0.07);
    }
    return shareBird;
}


void Bird::createBird(){
    
    bird = Sprite::create("res/bird1.png");
    Size winSize = Director::getInstance()->getWinSize();
 //   bird->setPosition(Vec2(winSize.width/2, winSize.height/2));
    bird->setScale(0.07, 0.07);
    
    PhysicsBody * body = PhysicsBody::create();
    body->addShape(PhysicsShapeCircle::create(620));
    body->setDynamic(true);
    body->setLinearDamping(0.0f);
    body->setGravityEnable(false);
    bird->setPhysicsBody(body);
    bird->getPhysicsBody()->setCollisionBitmask(1);
    bird->getPhysicsBody()->setCategoryBitmask(1);
    bird->getPhysicsBody()->setContactTestBitmask(1);
    bird->setTag(2);
    
    addChild(bird);
    
    Animation * readyAnimation = Animation::create();
    readyAnimation->addSpriteFrameWithFile("res/bird1.png");
    readyAnimation->addSpriteFrameWithFile("res/bird2.png");
    readyAnimation->setDelayPerUnit(0.2);
    readyAnimation->setRestoreOriginalFrame(true);
    readyAnimation->setLoops(-1);
    
    this->readyAction = Animate::create(readyAnimation);
    
    
    
    Animation * flyAnimation = Animation::create();
    flyAnimation->addSpriteFrameWithFile("res/bird1.png");
    flyAnimation->addSpriteFrameWithFile("res/bird2.png");
    
    flyAnimation->setDelayPerUnit(0.15);
    flyAnimation->setRestoreOriginalFrame(true);
    flyAnimation->setLoops(-1);
    this->flyAction = Animate::create(flyAnimation);
    
    ActionInterval * up = MoveBy::create(0.5f, Point(0,5));
    ActionInterval * down = up->reverse();
    
    this->moveAction = RepeatForever::create(Sequence::create(up,down, NULL));
    
    ActionInterval * rotateWhenCatchBug = RotateBy::create(0.1, 30);
    
    this->catchBugAction = Repeat::create(Sequence::create(rotateWhenCatchBug,rotateWhenCatchBug->reverse(), NULL), 1);
    
        
    
}

bool Bird::changeState(ActionState actionState){
    current_actionState = actionState;
    return true;
    
}


void Bird::ready(){
    changeState(READY_ACTION);
    bird->runAction(readyAction);
    bird->runAction(moveAction);
    
}

void Bird::fly(){
    changeState(FLY_ACTION);
    bird->getPhysicsBody()->setGravityEnable(true);

}

void Bird::swing(){
    changeState(SWING_ACTION);
 //   this->stopAllActions();
 //   this->runAction(flyAction);
 //   this->runAction(moveAction);
    
}

void Bird::catchBugs(){
    changeState(CATCHBUGS_ACTION);
 //   this->runAction(catchBugAction);
    
}

void Bird::die(){
    changeState(DIE_ACTION);
    bird->stopAllActions();
    bird->getPhysicsBody()->setEnabled(false);
    
}

void Bird::setPosX(){
    bird->setPositionX(0);
}

void Bird::setVelocity(){
    bird->getPhysicsBody()->setVelocity(Vec2(0,260));
}

void Bird::rotateBird(){
    float vertcalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(fmin(fmax(-90, vertcalSpeed*0.2 + 60), 30));
    
}

