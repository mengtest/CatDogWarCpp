//
//  GameHeroBullet.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/9.
//
//

#include "GameHeroBullet.h"

GameHeroBullet::GameHeroBullet()
{
    
}

GameHeroBullet::~GameHeroBullet()
{
    
}

void GameHeroBullet::onEnter()
{
    Layer::onEnter();
    
    this->setContentSize(Size(21, 52));
    Sprite *bullet = Sprite::create("YuGuZD.png");
    
    addChild(bullet);
}

void GameHeroBullet::onExit()
{
    Layer::onExit();
}

void GameHeroBullet::setIsVisible()
{
    this->setVisible(true);
    isVisible = true;
    Size winSize = Director::getInstance()->getWinSize();
    this->runAction(Sequence::create(MoveTo::create((this->getPosition().y + winSize.height)/150, Vec2(this->getPosition().x, winSize.height)),
                                     CallFuncN::create(CC_CALLBACK_0(GameHeroBullet::setIsNotVisible, this)), nullptr));
}

void GameHeroBullet::setIsNotVisible()
{
    this->setVisible(false);
    isVisible = false;
    this->stopAllActions();
}

bool GameHeroBullet::getIsVisible()
{
    return isVisible;
}
