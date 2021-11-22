

#ifndef __FLAG_H__
#define __FLAG_H__

#include "cocos2d.h"
#include"fstream"
#include <fstream>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Flag {
private:
	string name;
	vector<string>color;
	bool selected;
	vector<vector<string>>listFlag;
public:
	Flag();
	~Flag();
	
	void loadData();
	vector<std::string> getColor();
	vector<std::vector<string>>getListFlag();
	void setSelected(bool x);
	bool getSelected();
	const std::vector<std::string> explode(const std::string& s, const char& c);

};

#endif // __FLAG_H__
