//
//  GameObjHero.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/4.
//
//

#ifndef CatDogWarCpp_GameObjHero_h
#define CatDogWarCpp_GameObjHero_h

#include "cocos2d.h"
#include "GameHeroBullet.h"

USING_NS_CC;

class GameObjHero : public cocos2d::Layer
{
public:
    GameObjHero(void);
    virtual ~GameObjHero(void);
    
    // overrides
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool containsTouchLocation(Touch * touch);
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;
    
    void releaseBullet(float dt);
    
public:
    Point offset;
    bool isControl;
    
protected:
    Scheduler *_pScheduler;
};

#endif
