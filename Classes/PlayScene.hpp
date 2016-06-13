//
//  PlayScene.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

/**
 put all layers together to make this scene
 */

#ifndef PlayScene_hpp
#define PlayScene_hpp

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.hpp"
#include "GameLayer.hpp"
#include "ControlLayer.hpp"
#include "StatusLayer.hpp"
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

class PlayScene:public Scene{
    
public:
    virtual bool init();
    
    PlayScene();
    ~PlayScene();
    
    CREATE_FUNC(PlayScene);
    
    void set_tsm(SceneManager * sceneManager);
    
private:
    PlayLayer * playLayer;
    
};

#endif /* PlayScene_hpp */

