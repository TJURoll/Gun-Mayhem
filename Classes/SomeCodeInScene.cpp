
//下列代码放在init中

/*创建键盘监视器*/
auto listener = EventListenerKeyboard::create();
listener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
listener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

/*创建鼠标监视器*/
EventListenerMouse* _mouseListener = EventListenerMouse::create();
//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
_mouseListener->onMouseDown = CC_CALLBACK_1(StartScene::onMouseDown, this);
//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

/*定义刷新器*/
scheduleUpdate();


/*接下来一些函数，需要放在背景类内，此时是假设scene中已经有player类对象的，此时需要改一下前面的类名*/
void StartScene::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = (EventMouse*)event;
	/*此时调用开火，右键放炸药*/
	switch (mouseEvent->getMouseButton())
	{
	case EventMouse::MouseButton::BUTTON_LEFT:
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		break;
	}
}

/*
*此段使得英雄能够连续移动的部分参考了CSDN中cocos2dx-9.键盘事件-实现精灵的连续移动文章的思路
*链接：https://blog.csdn.net/weixin_44453949/article/details/110885967
*/

void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	int x = 0, y = 0;//移动的长度
	keyMap.clear();
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		jumpOrSquat(&this->hero1, 1);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		jumpOrSquat(&this->hero1, -1);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
		break;
	default:
		break;
	}

	//this->update();
}
void  StartScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
		break;
	}
	//this->update();
}

void StartScene::update(float delta)
{
	int yStep = 0;//定义沿着y轴方向走的距离
	int xStep = 0;//定义沿着x轴方向走的距离

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A])
		xStep = -1;
	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D])
		xStep = 1;

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == false && keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == true && this->hero1.getDirection() == false)
	{
		/*如果先前英雄向右方向，并且按下了A，松开了D，则改变方向*/
		this->hero1.changeTexture(true);//图像翻转

		this->hero1.changeDirection(true);//储存数据翻转
	}

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == true && keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == false && this->hero1.getDirection() == true)
	{
		/*如果先前英雄向左方向，并且按下了D，松开了A，则改变方向*/
		this->hero1.changeTexture(false);//图像翻转

		this->hero1.changeDirection(false);//储存数据翻转
	}

	auto moveto = MoveTo::create(0.2f, Vec2(this->hero1.sprite->getPosition().x + xStep, this->hero1.sprite->getPosition().y + yStep));
	this->hero1.sprite->runAction(moveto);


}

void StartScene::jumpOrSquat(Player* Hero, int mod)
{
	/*此时mod=1是上跳，mod=-1是下蹲*/

	/*获取跳跃之后目标坐标，并且进行判断*/
	Vec2 srcPosition = Hero->sprite->getPosition();
	srcPosition.y += mod * 10;//需要与具体物理引擎连接后确定
	if (!Hero->whetherCanMove(srcPosition))
		return;//如果没法跳跃（遇到边界或者障碍物，直接不动或者坐假动作)
	//Hero->sprite->setRotation(20.0f);设置跳跃高度
	auto moveto = MoveTo::create(0.2f, Vec2(Hero->sprite->getPosition().x, Hero->sprite->getPosition().y + mod * 15));//具体的高度可以调整
	moveto->setDuration(0.3f);
	/*此处调用物理引擎使得其能上升*/

	this->hero1.sprite->runAction(moveto);


}