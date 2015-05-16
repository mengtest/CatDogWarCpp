//
//  GameObjEnemy.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/8.
//
//

#include "GameObjEnemy.h"
#include "GameScene.h"

GameObjEnemy::GameObjEnemy()
{
    
}


GameObjEnemy::~GameObjEnemy()
{
    
}

void GameObjEnemy::onEnter()
{
    Layer::onEnter();
    this->setContentSize(Size(99,111));
    mainBody = Sprite::create("DrDog1.png");
    
    Animation *ani = Animation::create();
    ani->addSpriteFrameWithFile("DrDog1.png");
    ani->addSpriteFrameWithFile("DrDog2.png");
    ani->setDelayPerUnit(0.1f);
    ani->setRestoreOriginalFrame(true);
    
    mainBody->runAction(RepeatForever::create(Animate::create(ani)));
    
    addChild(mainBody);
    
    boom = Sprite::create("boom1.png");
    addChild(boom);
    boom->setVisible(false);
    
    isLife = true;
}

void GameObjEnemy::onExit()
{
    Layer::onExit();
}

void GameObjEnemy::setType(int var)
{
    type = var;
}

void GameObjEnemy::moveStart()
{
    isLife = true;
    int type = rand_0_1() * 4;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    // move as bezier
    ccBezierConfig bezier1;
    bezier1.controlPoint_1 = Point(this -> getPosition().x + 400, 330);
    bezier1.controlPoint_2 = Point(this -> getPosition().x - 400, 280);
    bezier1.endPosition = Point(this -> getPosition().x, -70);
    BezierTo *bezierBy1 = CCBezierTo::create(6, bezier1);
    
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Point(this -> getPosition().x - 400, 330);
    bezier2.controlPoint_2 = Point(this -> getPosition().x + 400, 280);
    bezier2.endPosition = Point(this -> getPosition().x, -70);
    BezierTo * bezierBy2 = CCBezierTo::create(6, bezier2);
    
    switch (type) {
        case 0:
        case 1:
            this->runAction(Sequence::create(MoveBy::create(6, Vec2(0, -winSize.height+70)),
                                             CallFuncN::create(CC_CALLBACK_0(GameObjEnemy::restart, this)), nullptr));
            break;
        case 2:
            this->runAction(Sequence::create(bezierBy1, CallFuncN::create(CC_CALLBACK_0(GameObjEnemy::restart, this)), nullptr));
            break;
        case 3:
            this->runAction(Sequence::create(bezierBy2, CallFuncN::create(CC_CALLBACK_0(GameObjEnemy::restart, this)), nullptr));
            break;
    }
    
    schedule(CC_SCHEDULE_SELECTOR(GameObjEnemy::releaseBullet), 1.0f, CC_REPEAT_FOREVER, 0.0f);
    
}

void GameObjEnemy::restart()
{
    mainBody->setVisible(true);
    Size size = Director::getInstance()->getWinSize();
    this->setPosition(Vec2(size.width/4 * type, size.height + 50));
    
    isLife = true;
    
    mainBody->setVisible(true);
    boom->setVisible(false);
    this->moveStart();
}

void GameObjEnemy::releaseBullet(float dt)
{
    Size size = Director::getInstance()->getWinSize();
    
    Point pos = this->getPosition();
    if (pos.y > 20 && pos.y < size.height && isLife) {
        GameMain *p = (GameMain *)this->getParent();
        p->releaseEnemyBullet(pos.x, pos.y-30);
    }
}

void GameObjEnemy::setDie()
{
    isLife = false;
    mainBody->setVisible(false);
    boom->setVisible(true);
    this->stopAllActions();
    
    // boom animation
    Animation *ani = Animation::create();
    ani->addSpriteFrameWithFile("boom1.png");
    ani->addSpriteFrameWithFile("boom2.png");
    ani->addSpriteFrameWithFile("boom3.png");
    ani->addSpriteFrameWithFile("boom4.png");
    ani->addSpriteFrameWithFile("boom5.png");
    
    ani->setDelayPerUnit(0.1f);
    ani->setRestoreOriginalFrame(true);
    
    boom->runAction(Sequence::create(Animate::create(ani), CallFuncN::create(CC_CALLBACK_0(GameObjEnemy::restart, this)),  NULL));

}