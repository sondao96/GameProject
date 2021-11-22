
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"flag.h"
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    bool onImageTouch(Ref* sender, ui::Widget::TouchEventType evt);
    std::vector<ui::ImageView*> touchColor;
    std::vector<ui::ImageView*> touchColorMini;

    int countCorrect = 0;
    int countWrong = 0;
    

    // a selector callback

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void timerMethod(float dt);
    cocos2d::Label* label;
    float time;
};

#endif // __GAME_SCENE_H__