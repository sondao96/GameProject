#include "gamescene.h"
#include "SimpleAudioEngine.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include<string>
#include <algorithm>
#include<iostream>
#include<set>
using namespace std;

USING_NS_CC;

static std::vector<std::string>sumFlag = { "sweden","mexico", "austria"};
static int section;
static std::set<int>v;
static int numberSection = 1;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	scene->setName("scene");
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
	playGame = CSLoader::getInstance()->createNode("flagColor3.csb");
	auto button = playGame->getChildByName<ui::Button*>("back");
	button->setPressedActionEnabled(true);
	button->addClickEventListener([=](Ref*) {
		numberSection = 1;
		auto back = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.5, back, Color3B(0, 255, 255)));
		});
	auto timePlus = playGame->getChildByName<ui::Button*>("Button_1");
	timePlus->setPressedActionEnabled(true);
	timePlus->addClickEventListener([=](Ref*) {
		_time += 20;
		});
	auto countLabel = Label::createWithTTF(std::to_string(numberSection)+"/50", "fonts/FredokaOne-Regular.ttf", 24);
	countLabel->setPosition(visibleSize.width / 2, visibleSize.height - 25);
	playGame->addChild(countLabel);
	label = Label::createWithTTF("TIME: 20", "fonts/FredokaOne-Regular.ttf", 24);
	label->setPosition(visibleSize.width / 2, visibleSize.height - 80);
	label->setScale(1.2);
	label->setColor(Color3B(255, 0, 255));
	playGame->addChild(label);
	_time = 20;
	this->schedule(schedule_selector(GameScene::timerMethod), 0.01);
	addChild(playGame);

	std::vector<int> listString;
	std::string str = FileUtils::getInstance()->getStringFromFile("res/flag.json");
	rapidjson::Document document;
	document.Parse<0>(str.c_str());
	rapidjson::Value& flagName = document["FLAGCOLOR"];
	bool checkDoublicate = true;
	while (checkDoublicate)
	{
		section = random(0, (int)sumFlag.size() - 1);
		v.insert(section);
		for (set<int>::iterator it = v.begin(); it !=v.end(); it++) {
			if (*it != section)
			{
				checkDoublicate = false;
			}
		}		
		if (v.size() >= sumFlag.size()) {
			checkDoublicate = false;
		}
	}
	auto icolor = flagName[section][sumFlag[section].c_str()]["color"].GetArray();
	auto name = flagName[section][sumFlag[section].c_str()]["csb_flag"].GetString();
	image = playGame->getChildByName<ui::ImageView*>(name);
	image->setVisible(true);
	cnt = icolor.Size();
	for (int i = 0; i < 14; i++) {
		listString.push_back(i);
	}
	for (int j = 0; j < icolor.Size(); j++) {
		listNumber.push_back(listString[icolor[j].GetInt()]);
		listColor.push_back(ui::ImageView::create("1x/" + std::to_string(listNumber[j]) + ".png"));
		listColor[j]->setTag(icolor[j].GetInt());
	}
	for (auto number : listNumber) {
		listString.erase(std::remove_if(listString.begin(), listString.end(), [number](int b)
		{
			return number == b;
		}), listString.end());
	}
	shuffle(listString);
	for (int i = 0; i < 10 - icolor.Size(); i++) {
		listColor.push_back(ui::ImageView::create("1x/" + std::to_string(listString[i]) + ".png"));
	}
	shuffle(listColor);
	for (int i = 0; i < 10; i++) {
		if (i < listColor.size())
		{
			if (i < 5) {
				listColor[i]->setScale(0.5);
				listColor[i]->setPosition(Vec2(visibleSize.width * 0.1 + listColor[i]->getContentSize().width * (i) / 1.6, visibleSize.width * 0.25));
				addChild(listColor[i]);
			}
			else {
				listColor[i]->setScale(0.5);
				listColor[i]->setPosition(Vec2(visibleSize.width * 0.1 + listColor[i]->getContentSize().width * (i - 5) / 1.6, visibleSize.width * 0.25 - listColor[i]->getContentSize().height / 2 - 20));
				addChild(listColor[i]);
			}
			listColor[i]->addTouchEventListener(CC_CALLBACK_2(GameScene::onImageTouch, this));
			listColor[i]->setTouchEnabled(true);
		}
	}
	return true;
}

bool GameScene::onImageTouch(Ref* sender, ui::Widget::TouchEventType evt) {
	if (evt == ui::Widget::TouchEventType::BEGAN) {
		auto touchColor = static_cast<ui::ImageView*>(sender);
		auto flagColor = utils::findChild<ui::ImageView*>(image, "flaga" + std::to_string(touchColor->getTag()));
		if (flagColor) {
			auto img = ui::ImageView::create("images/correct.png");
			img->setAnchorPoint(Vec2(0.5, 0.5));
			img->setPosition(touchColor->getBoundingBox().size);
			touchColor->addChild(img, 100);
			flagColor->setVisible(true);
			countCorrect++;
		}
		else {
			auto img = ui::ImageView::create("images/wrong.png");
			img->setAnchorPoint(Vec2(0.5, 0.5));
			img->setPosition(touchColor->getBoundingBox().size);
			touchColor->addChild(img, 100);
			countWrong++;
		}
		if (countCorrect == cnt) {			
			checkWin();
			label->setOpacity(0);

			this->unscheduleAllSelectors();
		}
		if (countWrong == 3) {
			label->setOpacity(0);
			checkLose();
			this->unscheduleAllSelectors();
		}

	}
	return true;
}

void GameScene::checkWin() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto winGame = CSLoader::createNode("flagColor4.csb");
	winGame->setOpacity(200);
	this->addChild(winGame);

	auto spriteFlagCorrect = Sprite::create("flag/flagCorrect" + std::to_string(section) + ".png");
	spriteFlagCorrect->setPosition(visibleSize / 2);
	spriteFlagCorrect->setScale(0.62);
	spriteFlagCorrect->setAnchorPoint(Vec2(0.2, 0.2));
	addChild(spriteFlagCorrect);

	auto textFlag = Sprite::create("flag/c"+std::to_string(section) + ".png");
	textFlag->setPosition(Vec2(20, visibleSize.height - textFlag->getContentSize().height * 1.2));
	textFlag->setAnchorPoint(Vec2(0, 0));
	textFlag->setScale(0.55);
	addChild(textFlag);

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
			if (numberSection < sumFlag.size()) {
				numberSection++;	
				auto next = GameScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, next, Color3B(0, 255, 255)));
			}
			else {
				v.clear();
				numberSection = 1;
				auto back = HelloWorld::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, back, Color3B(0, 255, 255)));
			}
		}
		});

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

void GameScene::checkLose() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto winGame = CSLoader::createNode("flagColor4.csb");
	winGame->setOpacity(200);
	this->addChild(winGame);

	auto spriteFlagCorrect = Sprite::create("flag/flagCorrect" + std::to_string(section) + ".png");
	spriteFlagCorrect->setPosition(visibleSize / 2);
	spriteFlagCorrect->setScale(0.62);
	spriteFlagCorrect->setAnchorPoint(Vec2(0.2, 0.2));
	addChild(spriteFlagCorrect);

	auto textFlag = Sprite::create("flag/c" + std::to_string(section) + ".png");
	textFlag->setPosition(Vec2(20, visibleSize.height - textFlag->getContentSize().height * 1.2));
	textFlag->setAnchorPoint(Vec2(0, 0));
	textFlag->setScale(0.55);
	addChild(textFlag);

	auto textCorrect = Sprite::create("flag/game time out.png");
	textCorrect->setPosition(Vec2(visibleSize.width * 0.4, 80));
	textCorrect->setAnchorPoint(Vec2(0, 0));
	textCorrect->setScale(0.55);
	addChild(textCorrect);
	
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


void GameScene::timerMethod(float dt)
{
	if (_time <= 0) {
		label->setOpacity(0);
		unscheduleAllSelectors();
		checkLose();
	}
	else {
		_time -= dt;
	}
	__String* timeToDisplay = __String::createWithFormat("%.0f", _time);
	label->setString(timeToDisplay->getCString());

}

template<typename T>
void GameScene::shuffle(std::vector<T>& v) {
	static std::random_device mj_rd;
	static std::mt19937 mj_g(mj_rd());
	std::shuffle(v.begin(), v.end(), mj_g);
}


