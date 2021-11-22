

#ifndef __GAME_SCENE_SECOND_H__
#define __GAME_SCENE_SECOND_H__

#include "cocos2d.h"

class GameSceneSecond : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback

    
    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneSecond);
    
};

#endif // __GAME_SCENE_SECOND_H__
