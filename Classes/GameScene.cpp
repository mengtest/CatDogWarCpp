#include "GameScene.h"

USING_NS_CC;

Scene* GameMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *pCloseItem = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(GameMain::menuBackCallback, this));
    pCloseItem->setPosition(visibleSize.width/2, visibleSize.height/2 - 50);
    pCloseItem->setScale(0.5);

    // create menu, it's an autorelease object
    Menu *pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 5, 25);
    pMenu->setVisible(false);
    pMenu->setEnabled(false);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "GameMain" splash screen"
    hero = new GameObjHero();

    // position the sprite on the center of the screen
    hero->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/10 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(hero, 1);
    
    
    enemies = Vector<GameObjEnemy *>(3);
    for (int i=0; i<enemies.capacity(); i++) {
        int type = i + 1;
        GameObjEnemy *enemy = new GameObjEnemy();
        enemy->setPosition(Vec2(visibleSize.width/4 * type, visibleSize.height - 50));
        enemy->setScale(0.5f);
        enemy->setType(type);
        enemy->moveStart();
        enemies.pushBack(enemy);
        
        addChild(enemy, 1);
    }
    
    heroBullets = Vector<GameHeroBullet *>(10);
    for (int i=0; i<heroBullets.capacity(); i++) {
        GameHeroBullet *bullet = new GameHeroBullet();
        bullet->setIsNotVisible();
        bullet->setScale(0.5f);
        heroBullets.pushBack(bullet);
        addChild(bullet, 3);
    }
    
    enemyBullets = Vector<GameEnemyBullet *>(10);
    for (int i=0; i<enemyBullets.capacity(); i++) {
        GameEnemyBullet *bullet = new GameEnemyBullet();
        bullet->setIsNotVisible();
        bullet->setScale(0.5f);
        enemyBullets.pushBack(bullet);
        addChild(bullet, 3);
    }
    
    isReduce = false;
    isOver = false;
    
    scheduleUpdate();
    
    Size winSize = Director::getInstance()->getWinSize();
    
    bg1 = Sprite::create("bg.png", Rect(0, 0, winSize.width, winSize.height));
    bg1->setScale(1);
    
    bg2 = Sprite::create("bg.png", Rect(0, 0, winSize.width, winSize.height));
    bg2->setScale(1);
    
    bg1->setAnchorPoint(Point(0, 0));
    bg2->setAnchorPoint(Point(0, 1));
    
    addChild(bg1, 0);
    addChild(bg2, 0);
    
    
    blood = 3;
    SpriteBatchNode *ui = SpriteBatchNode::create("cat.png");
    blood1 = Sprite::createWithTexture(ui->getTexture());
    blood1->setPosition(Point(20, visibleSize.height - 20));
    blood1->setScale(0.2);
    ui->addChild(blood1);
    
    blood2 = Sprite::createWithTexture(ui->getTexture());
    blood2->setPosition(Point(50, visibleSize.height - 20));
    blood2->setScale(0.2);
    ui->addChild(blood2);
    
    blood3 = Sprite::createWithTexture(ui->getTexture());
    blood3->setPosition(Point(80, visibleSize.height - 20));
    blood3->setScale(0.2);
    ui->addChild(blood3);
    
    addChild(ui, 4);
    
    
    gameover = Sprite::create("gameover.png");
    gameover->setAnchorPoint(Point(0.5, 0.5));
    gameover->setPosition(visibleSize.width/2, visibleSize.height/2 + 70);
    gameover->setVisible(false);
    gameover->setScale(0.5);
    addChild(gameover, 5);
    
    gamemark = new GameMark();
    addChild(gamemark, 4);
    
    return true;
}


void GameMain::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameMain::releaseHeroBullet(int x, int y)
{
    for (int i=0; i<heroBullets.size(); i++) {
        if (!((GameHeroBullet *)heroBullets.at(i))->getIsVisible()) {
            ((GameHeroBullet *)heroBullets.at(i))->setPosition(x, y);
            ((GameHeroBullet *)heroBullets.at(i))->setIsVisible();
            break;
        }
    }
}

void GameMain::releaseEnemyBullet(int x, int y)
{
    for (int i=0; i<enemyBullets.size(); i++) {
        if (!((GameEnemyBullet *)enemyBullets.at(i))->getIsVisible()) {
            ((GameEnemyBullet *)enemyBullets.at(i))->setPosition(x, y);
            ((GameEnemyBullet *)enemyBullets.at(i))->setIsVisible();
            break;
        }
    }
}

void GameMain::update(float time)
{
    // Collision judgement
    if (!isOver) {
        // 1. Enemy & Hero's bullet
        for (int i = 0; i<enemies.capacity(); i++) {
            GameObjEnemy *enemy = ((GameObjEnemy *)enemies.at(i));
            if (enemy->isLife) {
                for (int j =0; j < heroBullets.capacity(); j++) {
                    GameHeroBullet *bullet = ((GameHeroBullet *)heroBullets.at(j));
                    if (bullet->getIsVisible()) {
                        if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
                            gamemark->addNumber(200);
                            enemy->setDie();
                            break;
                        }
                    }
                }
            }
            
            // 2. Enemy & Hero
            if (!isReduce && enemy->isLife && enemy->getBoundingBox().intersectsRect(hero->getBoundingBox())) {
                enemy->setDie();
                setHeroHurt();
            }
        }
        // 3. Hero and enemy bullet
        if (!isReduce) {
            for (int i = 0; i < enemyBullets.capacity(); i++) {
                GameEnemyBullet * enemybullet = ((GameEnemyBullet *)enemyBullets.at(i));
                if (enemybullet->getBoundingBox().intersectsRect(hero->getBoundingBox())) {
                    setHeroHurt();
                }
            }
        }
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    bg1->setPosition(Point(bg1->getPosition().x, bg1->getPosition().y - 2));
    bg2->setPosition(Point(bg2->getPosition().x, bg2->getPosition().y - 2));
    
    if (bg2->getPosition().y < 0) {
        bg2->setPosition(Point(bg2->getPosition().x, bg2->getPosition().y + winSize.height));
    }
    
    if (bg1->getPosition().y < 0) {
        bg1->setPosition(Point(bg1->getPosition().x, bg1->getPosition().y + winSize.height));
    }
}

void GameMain::setHeroHurt()
{
    hero->stopAllActions();
    
    ActionInterval *action = Blink::create(5, 10);
    hero->runAction(action);
    
    schedule(CC_SCHEDULE_SELECTOR(GameMain::resetReduce), 5.0f);
    isReduce = true;
 
    switch (blood) {
        case 3:
            blood3->setVisible(false);
            blood--;
            break;
            
        case 2:
            blood2->setVisible(false);
            blood--;
            break;
            
        case 1:
            blood1->setVisible(false);
            blood--;
            break;
            
        case 0:
            if (!isOver) {
                isOver = true;
                setOver();
            }
            
        default:
            break;
    }
    
}

void GameMain::resetReduce(float dt)
{
    isReduce = false;
}


void GameMain::setOver()
{
    Menu *pMenu = (Menu *)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    
    gameover->setVisible(true);
    gameover->setScale(0);
    
    pMenu->setScale(0);
    pMenu->runAction(ScaleTo::create(0.5, 1));
    gameover->runAction(ScaleTo::create(0.5, 0.5));
    
    hero->setVisible(false);
}


void GameMain::menuBackCallback(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GameMain::createScene());
}