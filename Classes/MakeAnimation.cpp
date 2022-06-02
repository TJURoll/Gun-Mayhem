#include "MakeAnimation.h"

/***************************************************************************
  函数名称：getAnimation
  功    能：获得一个可以使用的动画效果
  输入参数：std::string url(文件地址), int frameNum()(动画的帧数), int loops(动作循环次数), float delay(延迟数)
  返 回 值：Animation* 对应动画的指针
  说    明：应该创建对应url的plist文件和png文件，此时的plist文件应该和png文件名称相同，并且输入时不用输入后缀名
***************************************************************************/
Animate* getAnimation(std::string url, int frameNum, float delay, int loops)
{
	std::string urlOfPlist = url + ".plist";
	std::string urlOfPng = url + ".png";
	std::string formatUrlOfPng = url + "%d.png";

	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(urlOfPlist, urlOfPng);//读入缓冲区
	Vector <SpriteFrame*>FrameVec;
	SpriteFrame* frame = NULL;
	auto frame_sp = Sprite::createWithSpriteFrameName(url+"1.png");//从SpriteFrameCache缓存中找到boy1.png这张图片.
	//this->addChild(frame_sp, 2);

	/*各帧压入vector容器中*/
	for (int i = 0; i < frameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format(formatUrlOfPng.c_str(), i));
		FrameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(FrameVec);//创建具体的动画效果
	animation->setLoops(loops);//设置循环次数
	animation->setDelayPerUnit(delay);//设置延时

	auto animate = Animate::create(animation);
	return animate;
}
