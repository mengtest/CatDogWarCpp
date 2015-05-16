//
//  GameHeroBullet.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/9.
//
//

#ifndef __CatDogWarCpp__GameHeroBullet__
#define __CatDogWarCpp__GameHeroBullet__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameHeroBullet : public cocos2d::Layer {
public:
    bool isVisible;
    
public:
    GameHeroBullet(void);
    virtual ~GameHeroBullet(void);
    
    virtual void onEnter(void) override;
    virtual void onExit(void) override;
    
    void setIsVisible();
    void setIsNotVisible();
    bool getIsVisible();
};

#endif /* defined(__CatDogWarCpp__GameHeroBullet__) */
