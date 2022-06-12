#pragma once
#include<string>
#include<vector>
#include<fstream>
#include "CCFileUtils.h"
using namespace std;
USING_NS_CC;
struct scoreData
{
	string name;
	string time;
	int score;
};

vector<string> getScore() {
	auto fileUtiles = FileUtils::getInstance();
	std::string filePath = fileUtiles->fullPathForFilename("score.txt");
	fstream dataTest("score.txt", ios_base::in);
	vector<scoreData> Data;
	vector<string>result;
	scoreData top3Data[3] = { {"","",0},{"","",0}, {"","",0} };

	while (!dataTest.fail())
	{
		scoreData tempSave;
		dataTest >> tempSave.name >> tempSave.time >> tempSave.score;
		if (tempSave.name != "")
			Data.push_back(tempSave);
	}

	for (int iTemp = 0; iTemp < static_cast<int>(Data.size()); iTemp++)
	{
		if (Data[iTemp].score > top3Data[0].score)
		{
			top3Data[2] = top3Data[1];
			top3Data[1] = top3Data[0];
			top3Data[0] = Data[iTemp];
		}
		else if (Data[iTemp].score > top3Data[1].score)
		{
			top3Data[2] = top3Data[1];
			top3Data[1] = Data[iTemp];
		}
		else if (Data[iTemp].score > top3Data[2].score)
			top3Data[2] = Data[iTemp];
	}

	for (int iTemp = 0; iTemp < 3; iTemp++)
	{
		/*需要调整格式输出看这！*/
		string s = top3Data[iTemp].name + "    " + top3Data[iTemp].time + "    " + to_string(top3Data[iTemp].score);
		result.push_back(s);
	}

	dataTest.close();
	return result;
}
