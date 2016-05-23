//
//  Bird.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/10.
//
//

#ifndef Bird_hpp
#define Bird_hpp

#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

typedef enum action_State{
    READY_ACTION,
    FLY_ACTION,
    SWING_ACTION,
    CATCHBUGS_ACTION,
    DIE_ACTION
    }ActionState;

class Bird:public Sprite{
    
public:
    Bird();
    virtual ~Bird();
    
    virtual bool init();
    
    static Bird * getInstance();
    
    Bird* createBird();
    
    void ready();
    void fly();
    void swing();
    void catchBugs();
    void die();
    
private:
    static Bird * shareBird;

    
    bool changeState(ActionState actionState);
    
    Action * readyAction;
    Action * flyAction;
    Action * swingAction;
    Action * moveAction;
    Action * catchBugAction;
    
    
    ActionState current_actionState;
    
};

#endif /* Bird_hpp */
