//
//  GameLayer.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/13.
//
//

#include "GameLayer.hpp"
#include <iostream>

GameLayer::GameLayer(){
    
}

GameLayer::~GameLayer(){
    
}

bool GameLayer::init(){
    if (Layer::init()) {
        visibleSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        
        this->gameStatus = GAME_READY;
        this->score = 0;

        bird = NULL;
        bird = new Bird;
        bird->Bird::createBird();
        bird->setPosition(origin.x + visibleSize.width/6 , origin.y + visibleSize.height/2 + 5);
        
        this->addChild(this->bird);
        bird->ready();
        
        this->createGround();
        
        this->addBranch();
        
        this->rain = Rain::create();
        this->addChild(rain);
        
        this->scheduleUpdate();
        
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
        
        return true;
        
    }
    else return false;
    
}

bool GameLayer::onContactBegin(const cocos2d::PhysicsContact &contact){
    
    Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    int tag_A = spriteA->getTag();
    int tag_B = spriteB->getTag();
    //1 for trees, 2 for bird and 3+ for bugs
    
    if (tag_A == 2 && tag_B >= 3) {
        this->bird->catchBugs();
        bugManager->resetBug(tag_B);
        this->score++;
        
    }
    
    else if (tag_B == 2 && tag_A >= 3) {
        this->bird->catchBugs();
        bugManager->resetBug(tag_A);
        this->score++;
        
    }
    
    else
        this->gameOver();
    
    this->delegator->gamePlay(score);
    return true;
}

void GameLayer::onTouch(){
    if (this->gameStatus == GAME_OVER) {
        return;
    }
    if (this->gameStatus == GAME_READY) {
        this->delegator->gameStart();
        this->bird->fly();

        SimpleAudioEngine::getInstance()->playEffect("res/start.wav");

        this->removeBranch();

        bugManager = BugManager::create();
        this->addChild(bugManager);
        
        treeManager = TreeManager::create();
        this->addChild(treeManager);
        
        this->rain->rainAtRandom();
        
        this->gameStatus = GAME_START;
        this->delegator->gamePlay(score);
        this->delegator->setGamelayer(this);
    }
    
    else if (this->gameStatus == GAME_START){
        this->bird->setVelocity();
    }
    
}

void GameLayer::rotateBird(){
    float vertcalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(fmin(fmax(-90, vertcalSpeed*0.2 + 60), 30));
}

void GameLayer::update(float delta){
    if (this->gameStatus == GAME_START) {
        this->bird->rotateBird();
        bird->setPosX();
    }
}



void GameLayer::createGround(){

    auto groundBody = PhysicsBody::create();
    auto shape = PhysicsShapeEdgeSegment::create(Vec2(0,0), Vec2(visibleSize.width,0));
    groundBody->addShape(shape);
    groundBody->setDynamic(false);
    Sprite * ground = Sprite::create("res/ground.png");
    ground->setScale(2.54,0.55);
    ground->setPhysicsBody(groundBody);
    ground->getPhysicsBody()->setCollisionBitmask(1);
    ground->getPhysicsBody()->setCategoryBitmask(1);
    ground->getPhysicsBody()->setContactTestBitmask(1);
    this->addChild(ground);
    
}



void GameLayer::gameOver(){
    if (this->gameStatus == GAME_OVER) {
        return;
    }
    
    this->bird->die();
    this->bird->setRotation(-90);
    this->bugManager->unscheduleUpdate();
    this->treeManager->unscheduleUpdate();
    this->rain->pause();
    
    this->delegator->gameOver(0);
    
    
    this->gameStatus = GAME_OVER;
}


void GameLayer::addBranch(){
    branch = Sprite::create("res/branch.png");
    branch->setAnchorPoint(Vec2(0,0.5));
    branch->setScale(0.45, 0.4);
    branch->setPosition(Vec2(0,visibleSize.height*0.46));
    this->addChild(branch);
}

void GameLayer::removeBranch(){
    this->removeChild(branch);
}

void GameLayer::gamePause(){
    Director::getInstance()->pause();
    bird->pause();
    rain->pause();
}

void GameLayer::gameResume(){
    Director::getInstance()->resume();
    bird->resume();
    rain->resume();
}