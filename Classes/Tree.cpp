//
//  Tree.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/27.
//
//

#include "Tree.hpp"

Tree::Tree(){
    
}

Tree::~Tree(){
    
}

bool Tree::init(){
    return true;
}

void Tree::createTrees(){
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    treeXL  =Sprite::create("res/treeXL.png");
    treeL = Sprite::create("res/treeL.png");
    treeM = Sprite::create("res/treeM.png");
    treeS = Sprite::create("res/treeS.png");
    
    treeXL->setAnchorPoint(Vec2(0.5,0));
    treeL->setAnchorPoint(Vec2(0.5,0));
    treeM->setAnchorPoint(Vec2(0.5,0));
    treeS->setAnchorPoint(Vec2(0.5,0));
    
    treeXL->setScale(0.72, 0.72);
    treeL->setScale(0.75, 0.75);
    treeM->setScale(0.75, 0.75);
    treeS->setScale(0.75, 0.75);
    
    treeXL->setPosition(Vec2(visibleSize.width*1.7,0));
    treeL->setPosition(Vec2(visibleSize.width*1.2,0));
    treeM->setPosition(Vec2(visibleSize.width*1.9,0));
    treeS->setPosition(Vec2(visibleSize.width*1.4,0));
    
    auto bodyXL = PhysicsBody::create();
    auto shapeXL1 = PhysicsShapeEdgeSegment::create(Vec2(4,-320), Vec2(4,330));
    auto shapeXL2 = PhysicsShapeEdgeSegment::create(Vec2(4,40), Vec2(-105,148));
    auto shapeXL3 = PhysicsShapeEdgeSegment::create(Vec2(4,138), Vec2(109,246));
    auto shapeXL4 = PhysicsShapeEdgeSegment::create(Vec2(4,-49), Vec2(95,40));
    bodyXL->addShape(shapeXL1);
    bodyXL->addShape(shapeXL2);
    bodyXL->addShape(shapeXL3);
    bodyXL->addShape(shapeXL4);
    bodyXL->setDynamic(false);
    treeXL->setPhysicsBody(bodyXL);
    treeXL->getPhysicsBody()->setCollisionBitmask(1);
    treeXL->getPhysicsBody()->setCategoryBitmask(1);
    treeXL->getPhysicsBody()->setContactTestBitmask(1);
    
    treeXL->setTag(1);
    
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
    
    addChild(treeXL);
    addChild(treeL);
    addChild(treeM);
    addChild(treeS);
    
    trees.pushBack(treeS);
    trees.pushBack(treeM);
    trees.pushBack(treeL);
    trees.pushBack(treeXL);
}


void Tree::moveWithScene(){
    
    if (treeXL) {
        treeXL->setPosition(Vec2(treeXL->getPositionX() - 3.3,0));
        if (treeXL->getPositionX() < -10) {
            reset(4);  //4 stands for treeXL
        }
    }
    
    if (treeL) {
        treeL->setPosition(Vec2(treeL->getPositionX() - 3.3,0));
        if (treeL->getPositionX() < -10) {
            reset(3);  //3 stands for treeL
        }
    }

    
    if (treeM) {
        treeM->setPosition(Vec2(treeM->getPositionX() - 3.3,0));
        if (treeM->getPositionX() < -10) {
            reset(2);  //2 stands for treeM
        }
    }
    
    if (treeS) {
        treeS->setPosition(Vec2(treeS->getPositionX() - 3.3,0));
        if (treeS->getPositionX() < -10) {
            reset(1);  //1 stands for treeS
        }
    }
    
}

void Tree::reset(int treeType){

    switch (treeType) {
        case 1:
            treeS->setPosition(Vec2(visibleSize.width*random(1.2, 1.5) + visibleSize.width * random(0.0, 0.1),0));
            break;
            
        case 2:
            treeM->setPosition(Vec2(visibleSize.width*random(1.2, 1.5) + visibleSize.width * random(0.0, 0.1),0));
            break;
            
        case 3:
            treeL->setPosition(Vec2(visibleSize.width*random(1.2, 1.7) + visibleSize.width * random(0.0, 0.1),0));
            break;
            
        case 4:
            treeXL->setPosition(Vec2(visibleSize.width*random(1.3, 1.9) + visibleSize.width * random(0.0, 0.1),0));
            break;
            
        default:
            break;
    }
    
}

Vector<Sprite*> Tree::getTrees(){
    createTrees();
    return trees;
}


bool TreeManager::init(){
    visibleSize = Director::getInstance()->getVisibleSize();
    
    createTreesVec();
    setRandomTree();
    addTrees();

    this->scheduleUpdate();
    return true;
}

void TreeManager::update(float dt){
    trees1->moveWithScene();
    trees2->moveWithScene();
    trees3->moveWithScene();
    resetTree();
}

void TreeManager::createTreesVec(){
    
    trees1 = new Tree;
    trees1Vec = trees1->getTrees();
    
    trees2 = new Tree;
    trees2Vec = trees2->getTrees();

    trees3 = new Tree;
    trees3Vec = trees3->getTrees();

    
}

void TreeManager::setRandomTree(){
    
    randomTree1 = trees1Vec.at(random(0, 3));
    randomTree2 = trees2Vec.at(random(0, 3));
    randomTree3 = trees3Vec.at(random(0, 3));
}

void TreeManager::addTrees(){
    
    if (randomTree1->getPositionX() > visibleSize.width) {
        this->addChild(randomTree1);
    }
    
    if (randomTree2->getPositionX() > visibleSize.width) {
        this->addChild(randomTree2);
    }
    
    if (randomTree3->getPositionX() > visibleSize.width) {
        this->addChild(randomTree3);
    }
    
}

void TreeManager::resetTree(){

    if (randomTree1->getPositionX() < 0) {
        this->removeChild(randomTree1);
        randomTree1 = trees1Vec.at(random(0, 3));
        if (randomTree1->getPositionX() > visibleSize.width) {
            this->addChild(randomTree1);
        }
        else{
            randomTree1 = trees1Vec.at(0);
            if (randomTree1->getPositionX() > visibleSize.width) {
                this->addChild(randomTree1);
            }
            else{
                randomTree1 = trees1Vec.at(1);
                if (randomTree1->getPositionX() > visibleSize.width) {
                    this->addChild(randomTree1);
                }
                else{
                    randomTree1 = trees1Vec.at(2);
                    if (randomTree1->getPositionX() > visibleSize.width) {
                        this->addChild(randomTree1);
                    }
                    
                }
                
            }

        }
    }
    
    if (randomTree2->getPositionX() < 0) {
        this->removeChild(randomTree2);
        randomTree2 = trees2Vec.at(random(0, 3));
        if (randomTree2->getPositionX() > visibleSize.width) {
            this->addChild(randomTree2);
        }
        else{
            randomTree2 = trees1Vec.at(1);
            if (randomTree2->getPositionX() > visibleSize.width) {
                this->addChild(randomTree2);
            }
            else{
                randomTree2 = trees1Vec.at(2);
                if (randomTree2->getPositionX() > visibleSize.width) {
                    this->addChild(randomTree2);
                }
                else{
                    randomTree2 = trees1Vec.at(3);
                    if (randomTree2->getPositionX() > visibleSize.width) {
                        this->addChild(randomTree2);
                    }
                    
                }
                
            }
            
        }
    }
    
    if (randomTree3->getPositionX() < 0) {
        this->removeChild(randomTree3);
        randomTree3 = trees3Vec.at(random(0, 3));
        if (randomTree3->getPositionX() > visibleSize.width) {
            this->addChild(randomTree3);
        }
        else{
            randomTree3 = trees1Vec.at(2);
            if (randomTree3->getPositionX() > visibleSize.width) {
                this->addChild(randomTree3);
            }
            else{
                randomTree3 = trees1Vec.at(3);
                if (randomTree3->getPositionX() > visibleSize.width) {
                    this->addChild(randomTree3);
                }
                else{
                    randomTree3 = trees1Vec.at(0);
                    if (randomTree3->getPositionX() > visibleSize.width) {
                        this->addChild(randomTree3);
                    }
                    
                }
                
            }
            
        }
    }
}
