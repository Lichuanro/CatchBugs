//
//  Bug.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/20.
//
//

#ifndef Bug_hpp
#define Bug_hpp

#include "cocos2d.h"
USING_NS_CC;


class Bug:public Node{
public:
    Bug();
    virtual ~Bug();
    
    virtual bool init();
    
    void createBug();
    
    void show();
    void caught();
    void moveWithScene();
    void reset();
    bool checkEaten();
    
    void setBugTag(int tag);
    
private:
    Sprite * bug;
    bool isEaten;    //true for already being eaten
    Action * move;
    
};



#define MAX_BUGS 5

class BugManager:public Node{
    
public:
    CREATE_FUNC(BugManager);
    virtual bool init();
    
    virtual void update(float dt);
    
    void resetBug(int tag);
    
private:
    void createBugs();
    
    Vector<Bug*> bugs;
};

#endif /* Bug_hpp */
