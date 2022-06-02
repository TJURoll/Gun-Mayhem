
//���д������init��

/*�������̼�����*/
auto listener = EventListenerKeyboard::create();
listener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
listener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

/*������������*/
EventListenerMouse* _mouseListener = EventListenerMouse::create();
//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
_mouseListener->onMouseDown = CC_CALLBACK_1(StartScene::onMouseDown, this);
//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

/*����ˢ����*/
scheduleUpdate();


/*������һЩ��������Ҫ���ڱ������ڣ���ʱ�Ǽ���scene���Ѿ���player�����ģ���ʱ��Ҫ��һ��ǰ�������*/
void StartScene::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = (EventMouse*)event;
	/*��ʱ���ÿ����Ҽ���ըҩ*/
	switch (mouseEvent->getMouseButton())
	{
	case EventMouse::MouseButton::BUTTON_LEFT:
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		break;
	}
}

/*
*�˶�ʹ��Ӣ���ܹ������ƶ��Ĳ��ֲο���CSDN��cocos2dx-9.�����¼�-ʵ�־���������ƶ����µ�˼·
*���ӣ�https://blog.csdn.net/weixin_44453949/article/details/110885967
*/

void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	int x = 0, y = 0;//�ƶ��ĳ���
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
	int yStep = 0;//��������y�᷽���ߵľ���
	int xStep = 0;//��������x�᷽���ߵľ���

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A])
		xStep = -1;
	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D])
		xStep = 1;

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == false && keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == true && this->hero1.getDirection() == false)
	{
		/*�����ǰӢ�����ҷ��򣬲��Ұ�����A���ɿ���D����ı䷽��*/
		this->hero1.changeTexture(true);//ͼ��ת

		this->hero1.changeDirection(true);//�������ݷ�ת
	}

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == true && keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == false && this->hero1.getDirection() == true)
	{
		/*�����ǰӢ�������򣬲��Ұ�����D���ɿ���A����ı䷽��*/
		this->hero1.changeTexture(false);//ͼ��ת

		this->hero1.changeDirection(false);//�������ݷ�ת
	}

	auto moveto = MoveTo::create(0.2f, Vec2(this->hero1.sprite->getPosition().x + xStep, this->hero1.sprite->getPosition().y + yStep));
	this->hero1.sprite->runAction(moveto);


}

void StartScene::jumpOrSquat(Player* Hero, int mod)
{
	/*��ʱmod=1��������mod=-1���¶�*/

	/*��ȡ��Ծ֮��Ŀ�����꣬���ҽ����ж�*/
	Vec2 srcPosition = Hero->sprite->getPosition();
	srcPosition.y += mod * 10;//��Ҫ����������������Ӻ�ȷ��
	if (!Hero->whetherCanMove(srcPosition))
		return;//���û����Ծ�������߽�����ϰ��ֱ�Ӳ����������ٶ���)
	//Hero->sprite->setRotation(20.0f);������Ծ�߶�
	auto moveto = MoveTo::create(0.2f, Vec2(Hero->sprite->getPosition().x, Hero->sprite->getPosition().y + mod * 15));//����ĸ߶ȿ��Ե���
	moveto->setDuration(0.3f);
	/*�˴�������������ʹ����������*/

	this->hero1.sprite->runAction(moveto);


}