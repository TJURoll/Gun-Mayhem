#include "MakeAnimation.h"

/***************************************************************************
  �������ƣ�getAnimation
  ��    �ܣ����һ������ʹ�õĶ���Ч��
  ���������std::string url(�ļ���ַ), int frameNum()(������֡��), int loops(����ѭ������), float delay(�ӳ���)
  �� �� ֵ��Animation* ��Ӧ������ָ��
  ˵    ����Ӧ�ô�����Ӧurl��plist�ļ���png�ļ�����ʱ��plist�ļ�Ӧ�ú�png�ļ�������ͬ����������ʱ���������׺��
***************************************************************************/
Animate* getAnimation(std::string url, int frameNum, float delay, int loops)
{
	std::string urlOfPlist = url + ".plist";
	std::string urlOfPng = url + ".png";
	std::string formatUrlOfPng = url + "%d.png";

	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(urlOfPlist, urlOfPng);//���뻺����
	Vector <SpriteFrame*>FrameVec;
	SpriteFrame* frame = NULL;
	auto frame_sp = Sprite::createWithSpriteFrameName(url+"1.png");//��SpriteFrameCache�������ҵ�boy1.png����ͼƬ.
	//this->addChild(frame_sp, 2);

	/*��֡ѹ��vector������*/
	for (int i = 0; i < frameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format(formatUrlOfPng.c_str(), i));
		FrameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(FrameVec);//��������Ķ���Ч��
	animation->setLoops(loops);//����ѭ������
	animation->setDelayPerUnit(delay);//������ʱ

	auto animate = Animate::create(animation);
	return animate;
}
