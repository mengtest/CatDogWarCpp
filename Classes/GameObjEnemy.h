//
//  GameObjEnemy.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/8.
//
//

#ifndef __CatDogWarCpp__GameObjEnemy__
#define __CatDogWarCpp__GameObjEnemy__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameObjEnemy : public cocos2d::Layer {
public:
    Sprite *mainBody;
    Sprite *boom;
    
    int type;
    bool isLife;
    
public:
    GameObjEnemy(void);
    virtual ~GameObjEnemy(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void setType(int var);
    void moveStart();
    void restart();
    
    void releaseBullet(float dt);
    void setDie();
};

#endif /* defined(__CatDogWarCpp__GameObjEnemy__) */
