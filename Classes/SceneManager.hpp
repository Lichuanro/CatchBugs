//
//  SceneManager.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <iostream>
#include "cocos2d.h"
#include "OpenScene.hpp"
#include "PlayScene.hpp"
#include "EndScene.hpp"

USING_NS_CC;

class PlayScene;

class SceneManager{
    
public:
    Scene * openScene;
    PlayScene * playScene;
    Scene * endScene;
    void createOpenScene();
    void gotoOpenScene();
    void gotoPlayScene();
    void gotoEndScene();
    
};

#endif /* SceneManager_hpp */
