//
//  StatusLayer.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/15.
//
//

#ifndef StatusLayer_hpp
#define StatusLayer_hpp

#include "cocos2d.h"
#include "GameLayer.hpp"
#include "PlayScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;


class StatusLayer:public Layer, public StatusDelegate{
  
public:
    StatusLayer();
    ~StatusLayer();
    
    virtual bool init();
    
    CREATE_FUNC(StatusLayer);
    
    virtual void gameStart(void);
    virtual void gamePlay(int score);
    virtual void gameOver(int currentScore, int bestScore);
    
private:
    void showReady();
    void showStart();
    void showOver(int current, int best);
    
    
    void fadeInGameOver();
    
    void jumpToScorePanel();
    
    void fadeInRestartBtn();
    
    void refreshScoreCallback();
    
    void refreshScoreExecutor(float dt);

    
    
    Sprite * count3;
    Sprite * count2;
    Sprite * count1;
    Sprite * score;
    
    
    int currentScore;
    int bestScore;
    
    int tmpScore;
    
    bool isNewRecord;
    
    Point originPoint;
    
    Size visibleSize;
    
};

#endif /* StatusLayer_hpp */
