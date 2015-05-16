//
//  GameObjHero.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/4.
//
//

#include "GameObjHero.h"
#include "GameScene.h"

GameObjHero::GameObjHero()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameObjHero::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameObjHero::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameObjHero::onTouchEnded,this);
    listener->setSwallowTouches(true);//不向下传递触摸
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}


GameObjHero::~GameObjHero()
{
    
}

void GameObjHero::onEnter()
{
    Layer::onEnter();
    
    this->setContentSize(Size(85, 90));
    
    // cat body
    auto mainsprite = Sprite::create("catBody1.png");
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("catBody1.png");
    ani->addSpriteFrameWithFile("catBody2-4.png");
    ani->addSpriteFrameWithFile("catBody3.png");
    ani->addSpriteFrameWithFile("catBody2-4.png");
    ani->setDelayPerUnit(0.1f);
    ani->setRestoreOriginalFrame(true);
    
    mainsprite->runAction(RepeatForever::create(Animate::create(ani)));
    
    addChild(mainsprite);
    
    
    // cat tail
    auto tail= Sprite::create("catTail.png");
    tail->setAnchorPoint(Vec2(0.5, 1));
    tail->setPosition(Vec2(-5, -29));
    tail->setScale(0.5, 0.5);
    tail->setRotation(20);
    
    tail->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5, -40), RotateBy::create(0.5, 40), NULL)));
    
    addChild(tail);
    
    // cat left hand
    auto lefthand = Sprite::create("catHand1.png");
    lefthand->setAnchorPoint(Vec2(1, 0.5));
    lefthand->setPosition(Vec2(-18, -20));
    addChild(lefthand);
    
    
    // cat right hand
    auto righthand = Sprite::create("catHand2.png");
    righthand->setAnchorPoint(Vec2(0, 0.5));
    righthand->setPosition(Vec2(18,-20));
    addChild(righthand);
    
    schedule(CC_SCHEDULE_SELECTOR(GameObjHero::releaseBullet), 1.0f , CC_REPEAT_FOREVER, 0.0f);
}

void GameObjHero::onExit()
{
    Layer::onExit();
    
}

bool GameObjHero::containsTouchLocation(Touch * touch)
{
    Size size = getContentSize();
    Point pos = getPosition();
    Rect pRect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
    
    Point location = touch -> getLocationInView();
    location = CCDirector::getInstance() -> convertToGL(location);
    return pRect.containsPoint(location);
}

bool GameObjHero::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    CCLOG("onTouchBegin");
    
    if (!containsTouchLocation(touch)) {
        return false;
        
    }else{
        isControl = true;
        Point touchPoint = touch->getLocationInView();
        touchPoint = Director::getInstance()->convertToGL(touchPoint);
        offset.x = touchPoint.x - this->getPosition().x;
        offset.y = touchPoint.y - this->getPosition().y;
    }
    
//    CCLOG("offset x:%f, y:%f", offset.x, offset.y);
    
    return true;
}

void GameObjHero::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    CCLOG("onTouchMoved");
    
    if (isControl) {
        Point touchPoint = touch->getLocationInView();
        touchPoint = Director::getInstance()->convertToGL(touchPoint);
        float x = touchPoint.x - offset.x;
        float y = touchPoint.y - offset.y;
        
//        CCLOG("move x:%f, y:%f", x, y);
        
        this->setPosition(x, y);
    }
}

void GameObjHero::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    CCLOG("onTouchEnded");
    
    if (isControl) {
        isControl = false;
    }
}

void GameObjHero::releaseBullet(float dt)
{
//    if (isControl) {
        Point pos = this->getPosition();
        GameMain *p = (GameMain *)this->getParent();
        p->releaseHeroBullet(pos.x, pos.y + 30);
//    }
}
