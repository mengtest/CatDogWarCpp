#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameObjHero.h"
#include "GameObjEnemy.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"
#include "GameMark.h"

class GameMain : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuBackCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
    
    void releaseHeroBullet(int x, int y);
    void releaseEnemyBullet(int x, int y);
    
    virtual void update(float time) override;
    
    void setHeroHurt();
    void resetReduce(float dt);
    void setOver();
    
private:
    GameObjHero *hero;
    Vector<GameObjEnemy *> enemies;
    Vector<GameHeroBullet *> heroBullets;
    Vector<GameEnemyBullet *> enemyBullets;
    
    bool isReduce;     // when true: hero blinking invincible
    bool isOver;       // when true: game over, all stop
    
    Sprite *bg1;
    Sprite *bg2;
    
    int blood;
    Sprite *blood1;
    Sprite *blood2;
    Sprite *blood3;
    Sprite *gameover;
    
    GameMark *gamemark;
};

#endif // __HELLOWORLD_SCENE_H__
