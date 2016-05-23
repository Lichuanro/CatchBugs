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
        visibleSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        
        this->gameStatus = GAME_READY;
        this->score = 0;
        
        this->bird = Bird::getInstance();
        this->bird->createBird();
        PhysicsBody * body = PhysicsBody::create();
        body->addShape(PhysicsShapeCircle::create(620));
        body->setDynamic(true);
        body->setLinearDamping(0.0f);
        body->setGravityEnable(false);
        this->bird->setPhysicsBody(body);
        this->bird->getPhysicsBody()->setCollisionBitmask(1);
        this->bird->getPhysicsBody()->setCategoryBitmask(1);
        this->bird->getPhysicsBody()->setContactTestBitmask(1);
        this->bird->setTag(2);
        this->bird->setPosition(origin.x + visibleSize.width/6 , origin.y + visibleSize.height/2 + 5);
        this->bird->ready();
        this->addChild(this->bird);
        
        
        this->createTrees();
        
        moveAllTrees = schedule_selector(GameLayer::moveTrees);
        
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
    //1 for trees, 2 for bird and 3 for bugs
    
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
//    SimpleAudioEngine::getInstance()->playEffect(<#const char *filePath#>);
    if (this->gameStatus == GAME_READY) {
        this->delegator->gameStart();
        this->bird->fly();
        
        this->schedule(moveAllTrees, 0.01f);
        
        bugManager = BugManager::create();
        this->addChild(bugManager);
        
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
        this->bird->setPositionX(origin.x + visibleSize.width/6);
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
    
    auto bodyL = PhysicsBody::create();
    auto shapeL1 = PhysicsShapeEdgeSegment::create(Vec2(4,-260), Vec2(4,250));
    auto shapeL2 = PhysicsShapeEdgeSegment::create(Vec2(4,5), Vec2(-100,105));
    auto shapeL3 = PhysicsShapeEdgeSegment::create(Vec2(4,95), Vec2(100,198));
    auto shapeL4 = PhysicsShapeEdgeSegment::create(Vec2(4,-76), Vec2(95,20));
    bodyL->addShape(shapeL1);
    bodyL->addShape(shapeL2);
    bodyL->addShape(shapeL3);
    bodyL->addShape(shapeL4);
    bodyL->setDynamic(false);
    treeL->setPhysicsBody(bodyL);
    treeL->getPhysicsBody()->setCollisionBitmask(1);
    treeL->getPhysicsBody()->setCategoryBitmask(1);
    treeL->getPhysicsBody()->setContactTestBitmask(1);
    
    treeL->setTag(1);
    
    auto bodyM = PhysicsBody::create();
    auto shapeM1 = PhysicsShapeEdgeSegment::create(Vec2(0,-200), Vec2(0,195));
    auto shapeM2 = PhysicsShapeEdgeSegment::create(Vec2(4,10), Vec2(-85,95));
    auto shapeM3 = PhysicsShapeEdgeSegment::create(Vec2(4,95), Vec2(60,145));
    auto shapeM4 = PhysicsShapeEdgeSegment::create(Vec2(4,-40), Vec2(85,40));
    bodyM->addShape(shapeM1);
    bodyM->addShape(shapeM2);
    bodyM->addShape(shapeM3);
    bodyM->addShape(shapeM4);
    bodyM->setDynamic(false);
    treeM->setPhysicsBody(bodyM);
    treeM->getPhysicsBody()->setCollisionBitmask(1);
    treeM->getPhysicsBody()->setCategoryBitmask(1);
    treeM->getPhysicsBody()->setContactTestBitmask(1);
    
    treeM->setTag(1);
    
    auto bodyS = PhysicsBody::create();
    auto shapeS1 = PhysicsShapeEdgeSegment::create(Vec2(4,-130), Vec2(4,115));
    auto shapeS2 = PhysicsShapeEdgeSegment::create(Vec2(4,-40), Vec2(-55,20));
    auto shapeS3 = PhysicsShapeEdgeSegment::create(Vec2(4,20), Vec2(65,75));
    bodyS->addShape(shapeS1);
    bodyS->addShape(shapeS2);
    bodyS->addShape(shapeS3);
    bodyS->setDynamic(false);
    treeS->setPhysicsBody(bodyS);
    treeS->getPhysicsBody()->setCollisionBitmask(1);
    treeS->getPhysicsBody()->setCategoryBitmask(1);
    treeS->getPhysicsBody()->setContactTestBitmask(1);
    
    treeS->setTag(1);
    
    
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

void GameLayer::checkCollide(){
    
    
}



void GameLayer::gameOver(){
    if (this->gameStatus == GAME_OVER) {
        return;
    }
    
 //   SimpleAudioEngine::getInstance()->playEffect(<#const char *filePath#>);
    this->bird->die();
    this->bird->setRotation(-90);
//    this->birdFadeOut();
//    this->birdRemove();
    this->bugManager->unscheduleUpdate();
    this->unschedule(moveAllTrees);
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


