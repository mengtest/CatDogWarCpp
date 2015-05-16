//
//  GameMark.cpp
//  CatDogWarCpp
//
//  Created by fragno on 15/5/10.
//
//

#include "GameMark.h"

GameMark::GameMark()
{
    
}


GameMark::~GameMark()
{
    
}

void GameMark::onEnter()
{
    Layer::onEnter();
    
    Size winSize = Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    bits = Vector<Sprite *>(5);
    
    Sprite *title = Sprite::create("score.png");
    title->setPosition(Point(winSize.width/2 + 40, winSize.height - 15));
    title->setScale(0.5);
    addChild(title);
    
    for (int i=0; i<bits.capacity(); i++) {
        Sprite *number = Sprite::create("shu.png");
        ui = number->getTexture();
        number->setScale(0.5);
        number->setTextureRect(Rect(234, 0, 26, 31));
        number->setPosition(Point(winSize.width - (i+1)*15, winSize.height - 15));
        bits.pushBack(number);
        addChild(number);
    }
    
    mark = 0;
}

void GameMark::onExit()
{
    Layer::onExit();
}

void GameMark::addNumber(int var)
{
    // score, set number by position
    mark += var;
    int temp = mark % 10;
    
    // set singe
    if (temp > 0) {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(0)) -> setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else
    {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(0)) -> setTextureRect(Rect(234, 0, 26, 31));
    }
    
    // set tens
    temp = (mark % 100) / 10;
    if (temp > 0) {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(1)) -> setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else
    {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(1)) -> setTextureRect(Rect(234, 0, 26, 31));
    }
    
    // set hundreds
    temp = (mark % 1000) / 100;
    if (temp > 0) {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(2)) -> setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else
    {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(2)) -> setTextureRect(Rect(234, 0, 26, 31));
    }
    
    // set thousand
    temp = (mark % 10000) / 1000;
    if (temp > 0) {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(3)) -> setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else
    {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(3)) -> setTextureRect(Rect(234, 0, 26, 31));
    }
    
    // set ten thousand
    temp = mark / 10000;
    if (temp > 0) {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(4)) -> setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else
    {
        ((Sprite *)bits.at(0)) -> setTexture(ui);
        ((Sprite *)bits.at(4)) -> setTextureRect(Rect(234, 0, 26, 31));
    }
}