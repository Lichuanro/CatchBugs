//
//  Tree.hpp
//  CatchBugs
//
//  Created by Lichuanro on 16/5/27.
//
//

/**
 the class for trees
 creates 4 different sizes of trees to make the game more challenging
 tree manager control all the trees added to the scene
 actually only 3 or less trees are shown at the same time
 trees are created at random, both the size and the position
 */

#ifndef Tree_hpp
#define Tree_hpp

#include "cocos2d.h"
USING_NS_CC;

class Tree:public Node{
public:
    Tree();
    virtual ~Tree();
    
    virtual bool init();
    
    void createTrees();
    
    void moveWithScene();
    
    void reset(int treeType);
    
    Vector<Sprite*> getTrees();
    
    
private:
    Sprite * treeXL;
    Sprite * treeL;
    Sprite * treeM;
    Sprite * treeS;
    
    Vector<Sprite*> trees;
    
    Size visibleSize;
    
};

class TreeManager:public Node{
public:
    CREATE_FUNC(TreeManager);
    
    virtual bool init();
    
    virtual void update(float dt);
    
    void setRandomTree();
    void addTrees();
    void resetTree();
    
    
private:
    Size visibleSize;
    
    void createTreesVec();

    Tree * trees1;
    Tree * trees2;
    Tree * trees3;
    
    Vector<Sprite*> trees1Vec;
    Vector<Sprite*> trees2Vec;
    Vector<Sprite*> trees3Vec;
    
    Sprite * randomTree1;
    Sprite * randomTree2;
    Sprite * randomTree3;
    
};

#endif /* Tree_hpp */
