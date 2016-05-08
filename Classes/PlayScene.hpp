//
//  PlayScene.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

#ifndef PlayScene_hpp
#define PlayScene_hpp

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.hpp"
USING_NS_CC;

class SceneManager;
class PlayLayer:public Layer{
    
public:
    CREATE_FUNC(PlayLayer);
    virtual bool init();
    void menuCallBack(Ref *pSender);
    
public:
    SceneManager * tsm;
    
    Sprite * background;
    
};

#endif /* PlayScene_hpp */

