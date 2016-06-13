//
//  Rain.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/6/1.
//
//

/**
 raining is to make the game more challenging
 it will rain at random while playing the game
 a rain symbol will show at the upper left corner of the scene when it's going to rain
 */

#ifndef Rain_hpp
#define Rain_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

class Rain:public Node{
public:
    Rain();
    virtual ~Rain();
    
    virtual bool init();
    
    CREATE_FUNC(Rain);
    
    void createRains();
    void addRainSymbol();
    void removeRainSymbol();
    void startRain(float dt);
    void stopRain(float dt);
    void clearRainDrops(float dt);
    void checkRaining();
    void rainAtRandom();
    
    void pause();
    void resume();
    
private:
    Vector<Sprite*> rains;
    
    Sprite * rainSymbol;
    
    bool isRaining;
    bool rainSymbolAdded;
    
    Size visibleSize;
};

#endif /* Rain_hpp */
