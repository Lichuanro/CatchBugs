//
//  Bird.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/10.
//
//

/**
 This class is to define the bird class
 create and control everything about the bird
 create only one bird while playing
 the action state is for further use
 */
#ifndef Bird_hpp
#define Bird_hpp

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

typedef enum action_State{
    READY_ACTION,
    FLY_ACTION,
    CATCHBUGS_ACTION,
    DIE_ACTION
    }ActionState;

class Bird:public Node{
    
public:
    Bird();
    virtual ~Bird();
    
    virtual bool init();
    
    static Bird * getInstance();
    
    void createBird();
    
    void ready();
    void fly();
    void catchBugs();
    void die();
    
    void setVelocity();
    void setPosX();
    void rotateBird();
    
    void pause();
    void resume();
private:
    static Bird * shareBird;
    Sprite * bird;
    
    bool changeState(ActionState actionState);
    
    Action * readyAction;
    Action * moveAction;
    
    ActionState current_actionState;
    
};

#endif /* Bird_hpp */
