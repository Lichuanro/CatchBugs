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
#include <cstdlib>

USING_NS_CC;

class SceneManager;

static int bestScore;

class StatusLayer:public Layer, public StatusDelegate{
  
public:
    StatusLayer();
    ~StatusLayer();
    
    virtual bool init();
    
    CREATE_FUNC(StatusLayer);
    
    virtual void gameStart(void);
    virtual void gamePlay(int score);
    virtual void gameOver(int bestScore);
    virtual void setGamelayer(GameLayer * layer);
private:
    void showReady();
    void showStart();
    void showPause();
    void backgroundBlur();
    
    void addReplayButton();
    
    void addEndButton();
    
    void addGamePauseButton();
    
    void addGameResumeButton();
    
    void replayButtonCallBack(Ref *sender);
    
    void endButtonCallBack(Ref *sender);
    
    void gamePauseButtonCallBack(Ref *sender);
    
    void gameResumeButtonCallBack(Ref *sender);

    Sprite * click;
    Sprite * count3;
    Sprite * count2;
    Sprite * count1;
    
    bool isNewRecord;
    
    Point originPoint;
    
    Size visibleSize;
    
    LabelAtlas * scoreNumber;
    LabelAtlas * bestScoreNumber;
    
    char scoreString[4];
    char bestScoreString[4];
    
    GameLayer * gamelayer;
};

#endif /* StatusLayer_hpp */
