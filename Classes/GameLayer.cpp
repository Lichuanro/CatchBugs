//
//  GameLayer.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/13.
//
//

#include "GameLayer.hpp"

GameLayer::GameLayer(){
    
}

GameLayer::~GameLayer(){
    
}

bool GameLayer::init(){
    if (Layer::init()) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        this->gameStatus = GAME_READY;
        this->score = 0;
        
        this->bird = Bird::getInstance();
        this->bird->createBird();
        PhysicsBody * body = PhysicsBody::create();
        body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
        body->setDynamic(true);
        body->setLinearDamping(0.0f);
        body->setGravityEnable(false);
        this->bird->setPhysicsBody(body);
        this->bird->setPosition(origin.x + visibleSize.width/6 , origin.y + visibleSize.height/2 + 5);
        this->bird->ready();
        this->addChild(this->bird);
        
        this->createTrees();
        
        moveAllTrees = schedule_selector(GameLayer::moveTrees);
        this->schedule(moveAllTrees, 0.01f);
        
        this->scheduleUpdate();
        
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
        
        return true;
        
    }
    else return false;
    
}

bool GameLayer::onContactBegin(const cocos2d::PhysicsContact &contact){
    this->gameOver();
    return true;
}

void GameLayer::onTouch(){
    if (this->gameStatus == GAME_OVER) {
        return;
    }
    
//    SimpleAudioEngine::getInstance()->playEffect(<#const char *filePath#>);
    if (this->gameStatus == GAME_READY) {
        this->delegator->gameStart();
        this->bird->fly();
        this->gameStatus = GAME_START;
    }
    
    else if (this->gameStatus == GAME_START){
        this->bird->getPhysicsBody()->setVelocity(Vec2(0,260));
    }
    
}

void GameLayer::rotateBird(){
    float vertcalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(min(max(-90, vertcalSpeed*0.2 + 60), 30));
}

void GameLayer::update(float delta){
    if (this->gameStatus == GAME_START) {
        this->rotateBird();
        this->bird->swing();
 //       this->checkCollide();
    }
}

void GameLayer::createTrees(){
    treeL = Sprite::create("res/treeL.png");
    treeM = Sprite::create("res/treeM.png");
    treeS = Sprite::create("res/treeS.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    treeL->setAnchorPoint(Vec2(0.5,0));
    treeM->setAnchorPoint(Vec2(0.5,0));
    treeS->setAnchorPoint(Vec2(0.5,0));
    
    treeL->setScale(0.75, 0.75);
    treeM->setScale(0.75, 0.75);
    treeS->setScale(0.75, 0.75);
    
    treeL->setPosition(Vec2(visibleSize.width*1.2,0));
    treeM->setPosition(Vec2(visibleSize.width*1.9,0));
    treeS->setPosition(Vec2(visibleSize.width*1.5,0));
    
    this->addChild(treeL);
    this->addChild(treeM);
    this->addChild(treeS);

    
}

void GameLayer::moveTrees(float dt){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    if (treeL) {
        treeL->setPosition(Vec2(treeL->getPositionX() - 2,0));
        if (treeL->getPositionX() < 0) {
            treeL->setPosition(Vec2(visibleSize.width*1.2,0));
        }
    }
    
    if (treeS) {
        treeS->setPosition(Vec2(treeS->getPositionX() - 2,0));
        if (treeS->getPositionX() < 0) {
            treeS->setPosition(Vec2(visibleSize.width*1.2,0));
        }
    }
    
    if (treeM) {
        treeM->setPosition(Vec2(treeM->getPositionX() - 2,0));
        if (treeM->getPositionX() < 0) {
            treeM->setPosition(Vec2(visibleSize.width*1.2,0));
        }
    }
    
    
}



void GameLayer::gameOver(){
    if (this->gameStatus == GAME_OVER) {
        return;
    }
    
 //   SimpleAudioEngine::getInstance()->playEffect(<#const char *filePath#>);
    this->bird->die();
    this->bird->setRotation(-90);
    this->birdFadeOut();
    this->birdRemove();
    this->gameStatus = GAME_OVER;
}


void GameLayer::birdFadeOut(){
    FadeOut* animation = FadeOut::create(1.5);
    CallFunc* animationDone = CallFunc::create(std::bind(&GameLayer::birdRemove,this));
    Sequence* sequence = Sequence::createWithTwoActions(animation, animationDone);
    this->bird->stopAllActions();
    this->bird->runAction(sequence);
}

void GameLayer::birdRemove(){
    this->bird->setRotation(0);
    this->removeChild(this->bird);
}


