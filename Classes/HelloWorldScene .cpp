#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include"gamescene.h"
USING_NS_CC;
using  namespace  CocosDenshion;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
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
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    


    auto mainMenu = CSLoader::getInstance()->createNode("flagColor.csb");
    this->addChild(mainMenu);
    auto button = mainMenu->getChildByName<ui::Button*>("buttonPlay");
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref*) {
        auto play = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(2,play,Color3B(0,255,255)));
        
        });
    
    return true;
}



