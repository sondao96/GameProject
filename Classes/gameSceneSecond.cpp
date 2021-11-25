#include "gameSceneSecond.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include"HelloWorldScene.h"
#include"gamescene.h"

using namespace std;

Scene* GameSceneSecond::createScene()
{
    auto scene = Scene::create();
    auto layer = GameSceneSecond::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameSceneSecond::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    labelTime = Label::createWithTTF("TIME: 60", "fonts/FredokaOne-Regular.ttf", 24);
    labelTime->setPosition(visibleSize.width / 2, visibleSize.height - 50);
    this->addChild(labelTime, 1);
    time = 10;   
    this->schedule(schedule_selector(GameSceneSecond::timerMethod), 0.01);

    auto nextGame = CSLoader::getInstance()->createNode("flagColor3.csb");
    this->addChild(nextGame);
    auto button = nextGame->getChildByName<ui::Button*>("back");
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref*) {
        auto back = HelloWorld::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.5, back, Color3B(0, 255, 255)));
        });

    for (int i = 0; i < 10; i++) {
        touchColor.push_back(nextGame->getChildByName<ui::ImageView*>("color" + std::to_string(i)));
    }

    for (int i = 0; i < 10; i++) {
        touchColor[i]->setTouchEnabled(true);
        touchColor[i]->addTouchEventListener(CC_CALLBACK_2(GameSceneSecond::onImageTouch, this));
        touchColor[i]->setTag(i);
        if (auto checkUserPick = utils::findChild(touchColor[i], "check" + std::to_string(i)))
        {
            checkUserPick->setVisible(false);
        }
    }

    return true;
}

void GameSceneSecond::timerMethod(float dt)
{
    if (time <= 0) {
        labelTime->setOpacity(0);
        gameScene->checkLose();
    }
    else {
        time -= dt;
    }
    __String* timeToDisplay = __String::createWithFormat("%.0f", time);
    labelTime->setString(timeToDisplay->getCString());

}

bool GameSceneSecond::onImageTouch(Ref* sender, ui::Widget::TouchEventType evt)
{   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto userPickColor = static_cast<ui::ImageView*>(sender);
    int selected = userPickColor->getTag();
    if (evt == ui::Widget::TouchEventType::ENDED) {
        
        if (auto checkUserPick = utils::findChild(userPickColor, "check" + std::to_string(userPickColor->getTag()))) {
            checkUserPick->setVisible(true);
        }
        switch (selected)
        {
        case 0:
        {
            auto flagRed = utils::findChild(this, "flaga3");
            auto CheckUserHandlePickRed = utils::findChild(this, "check0");
            auto userPickedRed = utils::findChild(this, "flagcolor1");
            flagRed->setOpacity(255.0f);
            CheckUserHandlePickRed->setOpacity(255.0f);
            userPickedRed->setOpacity(255.0f);
            countCorrect++;
            touchColor[userPickColor->getTag()]->setTouchEnabled(false);
            break;
        }
            
        case 3:
        {
            auto flagGray = utils::findChild(this, "flaga4");          
            auto CheckUserHandlePickGray = utils::findChild(this, "check3");
            auto userPickedGray = utils::findChild(this, "flagcolor3");
            flagGray->setOpacity(255);            
            CheckUserHandlePickGray->setOpacity(255);
            userPickedGray->setOpacity(255);
            countCorrect++;
            touchColor[userPickColor->getTag()]->setTouchEnabled(false);
            break;
        }
            
        case 5:
        {
            auto flagGreen = utils::findChild(this, "flaga1");
            auto flagGreen2 = utils::findChild(this, "flaga5");
            auto CheckUserHandlePickGreen = utils::findChild(this, "check5");
            auto userPickedGreen = utils::findChild(this, "flagcolor2");
            flagGreen->setOpacity(255);
            flagGreen2->setOpacity(255);
            CheckUserHandlePickGreen->setOpacity(255);
            userPickedGreen->setOpacity(255);
            countCorrect++;
            touchColor[userPickColor->getTag()]->setTouchEnabled(false);
            break;
        }
        case 7:
        {
            auto flagWhile = utils::findChild(this, "flaga2");
            auto CheckUserHandlePickWhile = utils::findChild(this, "check7");
            auto userPickedWhile = utils::findChild(this, "flagcolor4");
            flagWhile->setOpacity(255);
            CheckUserHandlePickWhile->setOpacity(255);
            userPickedWhile->setOpacity(255);
            countCorrect++;
            touchColor[userPickColor->getTag()]->setTouchEnabled(false);
            break;
        }
        default:
        {
            countWrong++;
            touchColor[userPickColor->getTag()]->setTouchEnabled(false);
            break;
        }
            
        }
        if (countCorrect == 4) {
            labelTime->setOpacity(0);
            gameScene->checkWin();
            this->unscheduleAllSelectors();
        }
        if (countWrong == 3) {
            labelTime->setOpacity(0);
            gameScene->checkLose();
            this->unscheduleAllSelectors();
        }
    }
    return true;
}








