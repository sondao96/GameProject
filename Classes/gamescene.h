

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include<time.h>
#include<random>
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;



class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    bool onImageTouch(Ref* sender, ui::Widget::TouchEventType evt);

    void checkWin();

    Node* playGame;

    //// implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void timerMethod(float dt);
    void checkLose();
    cocos2d::Label* label;
    float _time;
    
    std::vector<ui::ImageView*>colorCorrect;
    std::vector<Node*>listFlagColor;


    
    int cnt = 0;
    int countCorrect = 0;
    int countWrong = 0;
    int random(int start, int last)
    {
        int iRet;
        srand(time(NULL));
        iRet = (rand() % (last - start + 1)) + start;
        return iRet;
    }
    template<typename T>
    void shuffle(std::vector<T>& v);
    

};
#endif // __GAME_SCENE_H__