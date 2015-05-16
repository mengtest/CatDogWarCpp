//
//  GameMark.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/10.
//
//

#ifndef __CatDogWarCpp__GameMark__
#define __CatDogWarCpp__GameMark__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameMark : public cocos2d::Layer
{
public:
    Vector<Sprite *> bits;
    Texture2D *ui;
    int mark;
    
public:
    GameMark();
    virtual ~GameMark();
    
    virtual void onEnter(void) override;
    virtual void onExit(void) override;
    
    void addNumber(int var);
};

#endif /* defined(__CatDogWarCpp__GameMark__) */
