#include "RankLayer.h"
#include<fstream>
#include<vector>
#include<algorithm>
#include "CCFileUtils.h"
using namespace std;
bool RankLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->initWithColor(Color4B(9, 6, 8, 100));
	this->setContentSize(Size(500, 500));
	this->setPosition(origin.x + visibleSize.width / 15, origin.y + visibleSize.height / 7);
	auto title = Label::createWithTTF("Player   Time    Score\n(Only 3 highest keeped)", "fonts/Marker Felt.ttf", 48);
	title->setPosition(250, 400);
	this->addChild(title);
	std::vector<Label*> scoreLabel;
	std::vector<std::string> score = getScore();
	for (auto i = 0; i < score.size(); i++)
	{
		auto temp = Label::createWithTTF("Player   Time   Score", "fonts/Marker Felt.ttf", 48);
		temp->setString(score[i]);
		temp->setPosition(250, 450 - (i + 3) * temp->getContentSize().height);
		scoreLabel.push_back(temp);
	}
	for (auto val : scoreLabel)
		this->addChild(val);

	return true;
}

std::vector<std::string> RankLayer::getScore()
{
	//enum LINE { Name, Time, Score };
	auto fileUtiles = FileUtils::getInstance();
	std::string filePath = fileUtiles->fullPathForFilename("score.txt");

	enum LINE { Name, Time, Score };


	std::ifstream infile(filePath);
	std::vector<std::string> content;//文件中所有的内容，每一行中包含0.名字，1.时间，2.分数
	std::string temporaryContent;//临时储存文件中每一行中内容（0.名字，1.时间，2.分数）
	std::vector<std::string> line;//文件中的所有内容，进行过分类
	std::vector<std::string> rank;
	std::istream_iterator<std::string> is(infile);
	std::istream_iterator<std::string> eof;
	copy(is, eof, back_inserter(content));
	std::vector<std::string>::iterator begin = content.begin();
	std::vector<std::string>::iterator end = begin;
	//分类
	std::vector<int> score;
	for (int i = 0; end != content.end(); end++, i++)
	{
		if (i % 3 == Name)
		{
			temporaryContent = content[i];
		}
		else
		{
			temporaryContent = temporaryContent + "    " + content[i];
		}
		if (i % 3 == Score)
		{
			score.push_back(atoi(content[i].c_str()));
			line.push_back(temporaryContent);
		}
	}

	if (line.size() > 3)
	{
		//选择法排序
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < line.size(); j++)
			{
				if (score[i] < score[j])
				{
					//交换分数
					int itemp;
					itemp = score[i];
					score[i] = score[j];
					score[j] = itemp;
					//交换文本内容
					std::string vctemp(line[i]);
					line[i] = line[j];
					line[j] = vctemp;
				}
			}
		}
		//输出前三的内容
		for (int i = 0; i < 3; i++)
		{
			//std::cout << line[i] << std::endl;
			rank.push_back(line[i]);
		}

	}
	else
	{
		//选择法排序
		for (int i = 0; i < line.size(); i++)
		{
			for (int j = i; j < line.size(); j++)
			{
				if (score[i] < score[j])
				{
					//交换分数
					int itemp;
					itemp = score[i];
					score[i] = score[j];
					score[j] = itemp;
					//交换文本内容
					std::string vctemp(line[i]);
					line[i] = line[j];
					line[j] = vctemp;
				}
			}
		}
		//输出前三的内容
		for (int i = 0; i < line.size(); i++)
		{
			//std::cout << line[i] << std::endl;
			rank.push_back(line[i]);
		}
	}

	return rank;

}
