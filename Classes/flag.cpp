#include "flag.h"
#include<string>
#include<iostream>
#include"json/document.h"
#include"json\rapidjson.h"

using namespace cocos2d;
Flag::Flag()
{
}
Flag::~Flag()
{
}
void Flag::loadData()
{	
	string str = FileUtils::getInstance()->getStringFromFile("res/test.json");
	CCLOG("%s", str.c_str());
		
}

std::vector<std::string> Flag::getColor()
{
	return color;
}

std::vector<std::vector<std::string>> Flag::getListFlag()
{
	return listFlag;
}

void Flag::setSelected(bool x)
{
	this->selected = x;
}

bool Flag::getSelected()
{
	
		return this->selected;
	
}

const std::vector<std::string> Flag::explode(const std::string& s, const char& c)
{

	
		std::string buff{ "" };
		std::vector<std::string> v;
		for (auto n : s)
		{
			if (n != c)
				buff += n;
			else if (n == c && buff != "")
			{
				v.push_back(buff);
				buff = "";
			}
		}
		if (buff != "")
			v.push_back(buff);

		return v;
	
}
