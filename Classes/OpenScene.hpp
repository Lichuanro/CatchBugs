//
//  OpenScene.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

#ifndef OpenScene_hpp
#define OpenScene_hpp

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.hpp"

USING_NS_CC;
class SceneManager;

class OpenLayer:public Layer{
    
public:
    CREATE_FUNC(OpenLayer);
    virtual bool init();
    void menuCallBack(Ref *pSender);
    
public:
    SceneManager * tsm;
};


#endif /* OpenScene_hpp */