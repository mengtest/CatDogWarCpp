//
//  GameEnemyBullet.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/9.
//
//

#ifndef __CatDogWarCpp__GameEnemyBullet__
#define __CatDogWarCpp__GameEnemyBullet__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameEnemyBullet : public cocos2d::Layer {
public:
    bool isVisible;
    
public:
    GameEnemyBullet(void);
    virtual ~GameEnemyBullet(void);
    
    virtual void onEnter(void) override;
    virtual void onExit(void) override;
    
    void setIsVisible();
    void setIsNotVisible();
    bool getIsVisible();
};

#endif /* defined(__CatDogWarCpp__GameEnemyBullet__) */
