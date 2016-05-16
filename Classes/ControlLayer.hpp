//
//  ControlLayer.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/13.
//
//

#ifndef ControlLayer_hpp
#define ControlLayer_hpp

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class ControlDelegate{
    
public:
    virtual void onTouch() = 0;
};


class ControlLayer:public Layer{
public:
    ControlLayer();
    ~ControlLayer();
    
    virtual bool init();
    CREATE_FUNC(ControlLayer);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(ControlDelegate*, delegator, Delegator);
};

#endif /* ControlLayer_hpp */