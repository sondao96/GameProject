#include "gamescene.h"
#include "SimpleAudioEngine.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"HelloWorldScene.h"
#include"gameSceneSecond.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
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
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	label = Label::createWithTTF("TIME: 60", "fonts/FredokaOne-Regular.ttf", 24);
	label->setPosition(visibleSize.width / 2,visibleSize.height-50);
	this->addChild(label,1);
	time = 10;

		this->schedule(schedule_selector(GameScene::timerMethod), 0.01);

	auto playGame = CSLoader::getInstance()->createNode("flagColor2.csb");
	this->addChild(playGame);
	auto button = playGame->getChildByName<ui::Button*>("back");
	button->setPressedActionEnabled(true);
	button->addClickEventListener([=](Ref*) {
		auto back = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.5, back, Color3B(0,255,255)));
		});
	


	for (int i = 0; i < 10; i++) {
		touchColor.push_back(playGame->getChildByName<ui::ImageView*>("Image_" + std::to_string(i)));
	}

	for (int i = 0; i < 10; i++) {
		touchColor[i]->setTouchEnabled(true);
		touchColor[i]->addTouchEventListener(CC_CALLBACK_2(GameScene::onImageTouch, this));
		touchColor[i]->setTag(i);
		if (auto checkUserPick = utils::findChild(touchColor[i], "Image_mini_" + std::to_string(i)))
		{
			checkUserPick->setVisible(false);
		}
	}
	
	return true;
}

bool GameScene::onImageTouch(Ref* sender, ui::Widget::TouchEventType evt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto userPickColor = static_cast<ui::ImageView*>(sender);
	if (evt == ui::Widget::TouchEventType::BEGAN) {
		if (auto checkUserPick = utils::findChild(userPickColor, "Image_mini_" + std::to_string(userPickColor->getTag())))
		{
			checkUserPick->setVisible(true);
		}
		if (userPickColor->getTag() == 1)
		{
			auto flagYeloow = utils::findChild(this, "flag2");
			auto userPickYellow = utils::findChild(this, "Image_16");
			flagYeloow->setOpacity(255.0f);
			userPickYellow->setOpacity(255.0f);
			countCorrect++;
			touchColor[userPickColor->getTag()]->setTouchEnabled(false);
		}
		if (userPickColor->getTag() == 2) {
			auto flagBlue = utils::findChild(this, "flag3");
			auto userPickBlue = utils::findChild(this, "Image_17");
			flagBlue->setOpacity(255);
			userPickBlue->setOpacity(255);
			countCorrect++;
			touchColor[userPickColor->getTag()]->setTouchEnabled(false);
			
		}
		if (userPickColor->getTag() != 1 && userPickColor->getTag() != 2) {
			countWrong++;
		}
	}
	if (countCorrect == 2||countWrong == 3) {
		auto winGame = CSLoader::createNode("flagColor3.csb");
		winGame->setOpacity(200);
		this->addChild(winGame);
		auto spriteFlagCorrect = Sprite::create("flag/flagCorrect.png");
		spriteFlagCorrect->setPosition(visibleSize / 2);
		spriteFlagCorrect->setScale(0.62);
		spriteFlagCorrect->setAnchorPoint(Vec2(0.2,0.2));
		addChild(spriteFlagCorrect);
		auto textSweden = Sprite::create("flag/c3.png");
		textSweden->setPosition(Vec2(20, visibleSize.height - textSweden->getContentSize().height*1.2));
		textSweden->setAnchorPoint(Vec2(0, 0));
		textSweden->setScale(0.55);
		addChild(textSweden);	
		if (countCorrect == 2) {
			label->setOpacity(0);
			auto buttonContinues = ui::Button::create("flag/continue.png");
			buttonContinues->setPosition(Vec2(20, visibleSize.height - buttonContinues->getContentSize().height * 2.1));
			buttonContinues->setScale(0.75);
			buttonContinues->setAnchorPoint(Vec2(0, 0));
			addChild(buttonContinues);
			auto textCorrect = Sprite::create("flag/game correct.png");
			textCorrect->setPosition(Vec2(visibleSize.width * 0.4, 80));
			textCorrect->setAnchorPoint(Vec2(0, 0));
			textCorrect->setScale(0.55);
			addChild(textCorrect);
			buttonContinues->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::ENDED) {
					auto next = GameSceneSecond::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, next, Color3B(0, 255, 255)));
				}
				});
		}
		else {
			label->setOpacity(0);
			auto buttonPlayAgain = ui::Button::create("flag/play again.png");
			buttonPlayAgain->setPosition(Vec2(20, visibleSize.height - buttonPlayAgain->getContentSize().height * 2.1));
			buttonPlayAgain->setScale(0.75);
			buttonPlayAgain->setAnchorPoint(Vec2(0, 0));
			addChild(buttonPlayAgain);
			auto textCorrect = Sprite::create("flag/game time out.png");
			textCorrect->setPosition(Vec2(visibleSize.width * 0.4, 80));
			textCorrect->setAnchorPoint(Vec2(0, 0));
			textCorrect->setScale(0.55);
			addChild(textCorrect);
			buttonPlayAgain->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::ENDED) {
					auto next = GameScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, next, Color3B(0, 255, 255)));
				}
				});
		}		
		auto buttonQuitGame = ui::Button::create("flag/quit.png");
		buttonQuitGame->setPosition(Vec2(20, visibleSize.height - buttonQuitGame->getContentSize().height * 3.1));
		buttonQuitGame->setScale(0.75);
		buttonQuitGame->setAnchorPoint(Vec2(0, 0));
		addChild(buttonQuitGame);		
		buttonQuitGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				auto back = HelloWorld::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, back, Color3B(0, 255, 255)));
			}
			});	
	}
	return true;
}
void GameScene::timerMethod(float dt)
{
	time -= dt;
	__String* timeToDisplay = __String::createWithFormat("%.0f", time);
	label->setString(timeToDisplay->getCString());
	
}




