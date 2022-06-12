#include "cocos2d.h"
USING_NS_CC;
class RankLayer :public LayerColor
{
private:
	std::vector<std::string> getScore();
public:
	CREATE_FUNC(RankLayer);
	virtual bool init();
};