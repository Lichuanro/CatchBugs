//
//  GameLayer.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/13.
//
//

/**
 the most important layer
 all the game objects are added here
 */
#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
#include "Bird.hpp"
#include "Bug.hpp"
#include "Tree.hpp"
#include "Rain.hpp"
#include "ControlLayer.hpp"
#include "SimpleAudioEngine.h"
#include <cstdlib>
USING_NS_CC;
using namespace CocosDenshion;

typedef enum game_Status {
    GAME_READY = 1,
    GAME_START,
    GAME_OVER
}GameStatus;

class GameLayer;
class StatusDelegate{
    
public:
    virtual void gameStart(void) = 0;
    
    virtual void gamePlay(int score) = 0;
    virtual void setGamelayer(GameLayer * gamelayer) = 0;
    virtual void gameOver(int bestScore) = 0;
    
};

class GameLayer:public Layer, public ControlDelegate{
    
public:
    GameLayer();
    ~GameLayer();
    
    bool virtual init();
    
    CREATE_FUNC(GameLayer);
    
    CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);
    
    void onTouch();
    
    void setPhysicsWorld(PhysicsWorld * world){
        this->world = world;
    }
    
    void update(float delta);
    
    void gamePause();
    void gameResume();
    
private:
    
    void rotateBird();
    
    void createGround();
    
    void addBranch();
    
    void removeBranch();
    
    bool onContactBegin(const cocos2d::PhysicsContact &contact);
    
    void gameOver();
    
    PhysicsWorld * world;
    
    GameStatus gameStatus;
    
    Size visibleSize;
    Point origin;
    
    int score;
    
    Bird * bird;
    BugManager * bugManager;
    TreeManager * treeManager;
    Sprite * branch;
    Rain * rain;

};


#endif /* GameLayer_hpp */
