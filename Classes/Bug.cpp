//
//  Bug.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/20.
//
//

#include "Bug.hpp"

Bug::Bug(){
    
}

Bug::~Bug(){
    
}

bool Bug::init(){
    return true;
}

void Bug::createBug(){
    bug = Sprite::create("res/bug.png");
    bug->setScale(0.05, 0.05);
    bug->setRotation(15);
    
    auto body = PhysicsBody::create();
    body->addShape(PhysicsShapeCircle::create(300));
    body->setDynamic(false);
    bug->setPhysicsBody(body);
    
    addChild(bug);
    
    ActionInterval * up = MoveBy::create(1.0f, Point(0,20));
    ActionInterval * down = up->reverse();
    
    this->move = RepeatForever::create(Sequence::create(up,down, NULL));
    bug->runAction(move);
    
    isEaten = false;
}

void Bug::show(){
    bug->setVisible(true);
}

void Bug::caught(){
    bug->setVisible(false);
    isEaten = true;
}

void Bug::moveWithScene(){
    
    bug->setPosition((Vec2(bug->getPositionX() - 3.3,bug->getPositionY())));
    if (bug->getPositionX() < 0) {
        reset();
    }
    
}

void Bug::reset(){
    Size winSize = Director::getInstance()->getWinSize();
    bug->setPosition(Vec2(winSize.width * random(1.1, 1.8),winSize.height * random(0.3, 0.8)));
}

bool Bug::checkEaten(){
    return isEaten;
}


bool BugManager::init(){
    
    createBug();
    this->scheduleUpdate();
    return true;
}

void BugManager::createBug(){
    Bug * bug = NULL;
    for (int i = 0; i < MAX_BUGS; i++) {
        bug = new Bug;
        bug->createBug();
        bug->reset();
        
        this->addChild(bug);
        
        bugs.pushBack(bug);
    }
}

void BugManager::update(float dt){
    for (auto bug : bugs) {
        bug->moveWithScene();
        if (bug->checkEaten() == false) {
            bug->show();
        }
        if (bug->checkEaten() == true) {
            bug->reset();
            bug->show();
        }
    }
    
}




