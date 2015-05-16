//
//  GameMenu.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/10.
//
//

#include "GameMenu.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

GameMenu::GameMenu()
{
    
}


GameMenu::~GameMenu()
{
    
}


bool GameMenu::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite *bg = Sprite::create("bg.png");
    bg->setScale(2);
    bg->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(bg);
    
    Sprite *bgStar = Sprite::create("moon.png");
    bgStar->setAnchorPoint(Point(0.5, 0));
    bgStar->setScale(0.5);
    bgStar->setPosition(Point(winSize.width/3*2, 0));
    this->addChild(bgStar);
    
    Node *title = Node::create();
    title->setContentSize(Size(winSize.width - 40, 50));
    Sprite *ptmLabel = Sprite::create("meowstar.png");
    ptmLabel->setScale(1);
    ptmLabel->setPosition(Point(0, 30));
    title->addChild(ptmLabel);

    Sprite * ptbLable = Sprite::create("battle.png");
    ptbLable -> setScale(1);
    ptbLable -> setPosition(0, -100);
    title -> addChild(ptbLable);
    
    title -> setPosition(winSize.width / 2, winSize.height/6*5);
    this -> addChild(title, 2, 2);
    
    // 1. New game
    MenuItemImage * newGameItem = MenuItemImage::create("newgameA.png", "newgameB.png", CC_CALLBACK_0(GameMenu::menuNewGameCallback, this));
    newGameItem -> setScale(1);
    newGameItem -> setPosition(winSize.width/2, winSize.height/2 - 20);
    newGameItem -> setEnabled(true);
    
    // use button to build menu
    Menu * mainMenu = Menu::create(newGameItem, NULL);
    mainMenu -> setPosition(0, 0);
    this -> addChild(mainMenu, 1, 3);
    
    // init sound part
    SimpleAudioEngine::getInstance() -> preloadBackgroundMusic("background.mp3");
    SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::getInstance() ->playBackgroundMusic("background.mp3", true);
    
    return true;
    
}

Scene* GameMenu::scene()
{
    Scene *scene = Scene::create();
    GameMenu *menu = GameMenu::create();
    scene->addChild(menu);
    return scene;
}

void GameMenu::menuNewGameCallback()
{
    Director::getInstance()->replaceScene(GameMain::createScene());
}
