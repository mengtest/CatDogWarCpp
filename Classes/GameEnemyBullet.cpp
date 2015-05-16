//
//  GameEnemyBullet.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/9.
//
//

#include "GameEnemyBullet.h"

GameEnemyBullet::GameEnemyBullet()
{
    isVisible = false;
}


GameEnemyBullet::~GameEnemyBullet()
{
    
}

void GameEnemyBullet::onEnter()
{
    Layer::onEnter();
    
    this->setContentSize(Size(21, 52));
    Sprite *bullet = Sprite::create("DrDogZD.png");
    bullet->runAction(RepeatForever::create(RotateBy::create(1, 360)));
    
    addChild(bullet);
}

void GameEnemyBullet::onExit()
{
    Layer::onExit();
}

void GameEnemyBullet::setIsVisible()
{
    this->setVisible(true);
    isVisible = true;
    this->runAction(Sequence::create(MoveTo::create((this->getPosition().y + 50)/150, Point(this->getPosition().x, -550)),
                                     CallFuncN::create(CC_CALLBACK_0(GameEnemyBullet::setIsNotVisible, this)), NULL));
}

void GameEnemyBullet::setIsNotVisible()
{
    this->setVisible(false);
    isVisible = false;
    this->stopAllActions();
}

bool GameEnemyBullet::getIsVisible()
{
    return isVisible;
}

