#include "gameSceneSecond.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include"gamescene.h"
USING_NS_CC;

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
    
    
    return true;
}





