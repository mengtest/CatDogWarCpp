//
//  GameMenu.h
//  CatDogWarCpp
//
//  Created by fragno on 15/5/10.
//
//

#ifndef __CatDogWarCpp__GameMenu__
#define __CatDogWarCpp__GameMenu__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameMenu : public cocos2d::Layer {
public:
    GameMenu();
    virtual ~GameMenu();
    
    virtual bool init(void) override;
    static Scene *scene();
    
    CREATE_FUNC(GameMenu);
    
    void menuNewGameCallback();
};

#endif /* defined(__CatDogWarCpp__GameMenu__) */
