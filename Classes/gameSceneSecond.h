

#ifndef __GAME_SCENE_SECOND_H__
#define __GAME_SCENE_SECOND_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include"gamescene.h"
#include"HelloWorldScene.h"
using namespace cocos2d;

class GameSceneSecond : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void timerMethod(float dt);
    
    // a selector callback
    std::vector<ui::ImageView*>touchColor;
    int countCorrect = 0;
    int countWrong = 0;
    bool GameSceneSecond::onImageTouch(Ref* sender, ui::Widget::TouchEventType evt);
    GameScene* gameScene;
    Label* labelTime;
    float time;
    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneSecond);
    
};

#endif // __GAME_SCENE_SECOND_H__
