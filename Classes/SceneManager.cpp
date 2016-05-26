//
//  SceneManager.cpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/8.
//
//

#include "SceneManager.hpp"

void SceneManager::createOpenScene(){
    
    openScene = Scene::create();
    OpenLayer * layer = OpenLayer::create();
    layer->tsm = this;
    openScene->addChild(layer);

}

void SceneManager::gotoOpenScene(){
    
    openScene = Scene::create();
    OpenLayer * layer = OpenLayer::create();
    layer->tsm = this;
    openScene->addChild(layer);
    
    Director::getInstance()->replaceScene(openScene);
    
    
}

void SceneManager::gotoPlayScene(){
    
 //   PlayLayer * layer = PlayLayer::create();
 //   layer->tsm = this;
 //   playScene->addChild(layer);
    
    playScene = PlayScene::create();
    playScene->set_tsm(this);
    
    Director::getInstance()->replaceScene(playScene);
    
}

void SceneManager::replay(){
    playScene->restart();
    playScene = PlayScene::create();
    
    Director::getInstance()->replaceScene(playScene);
}

void SceneManager::gotoEndScene(){
    
}

/*

 void SceneManager::goOpenScene(){
 openScene = Scene::create();
 OpenLayer * layer = OpenLayer::create();
 layer->tsm = this;
 openScene->addChild(layer);
 
 Director::getInstance()->replaceScene(openScene);
 
 }
 
 }*/