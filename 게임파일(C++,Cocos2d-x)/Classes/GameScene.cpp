#include "stdafx.h"



USING_NS_CC;

Point g_MousePoint;

char strTemp[256] = "";

unsigned char* strBuffer;
int m_nWidth = 0;
int m_nHeight = 0;
char sWidth[256];
char sHeight[256];

CMapManager g_MapManager;

ssize_t nBufferSize = 0;

//!< 실제 Real 포인트
CCPoint g_CameraPoint = CCPoint(0.0f,0.0f);

//!< 보여지는 포인트
CCPoint g_CameraPoint_Smooth = CCPoint(0.0f,0.0f);

//!< 한글출력 문제해결을 위한 UTF8인코딩 (cocos2d-x는 내부적으로 UTF8인코딩을 사용)
//!< ==> 모든 파일 UTF8인코딩 CCImage내의 WiteCharToMultiByte 수정하여 해결(첫번째 인자를 CP_UTF8로 변경)
//wchar_t wstrTemp[128];
//
//void GameScene::SetMsg()
//{
//	WideCharToMultiByte(CP_UTF8,0,wstrTemp,-1,strTemp,128,0,0);
//}
//	

vector<CUnit*> g_UnitList;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
//
//void GameScene::onEnter()
//{
//	//!< 멀티터치 리스너
//	//...
// 
//    auto listener = EventListenerTouchAllAtOnce::create();
//    //listener->setSwallowTouches(true); //멀티터치이기 때문에 삼키면 안된다
// 
//    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
// 
//    //...
//
//	
//	this->scheduleUpdate();
//
//}
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	D_SOUNDMNG->setBackgroundMusicVolume(1.0f);
	D_SOUNDMNG->setEffectsVolume(1.0f);
	D_SOUNDMNG->preloadEffect("Select.mp3");

	D_SOUNDMNG->playBackgroundMusic("bgm.mp3");


	//!< 멀티터치 리스너
//	//...
 
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true); //멀티터치이기 때문에 삼키면 안된다
 
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
//    //...
//

	g_MousePoint.x = 0;
	g_MousePoint.y = 0;

	m_eGameStep = E_GAME_STEP_READY;


	m_bTestButton.Init(this,2,"Button_Test_1.png","Button_Test_3.png",CCPoint(150,150),3.3f,1.0f,0.9f);
	//m_bTestButton.m_fSpecScale = 2.0f;
	//m_bTestButton.setScal
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(GameScene::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Point::ZERO);
 //   this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    //
    m_pLabel = LabelTTF::create("Hello World", "Arial", 24);
    //
    //// position the label on the center of the screen
    m_pLabel->setPosition(Point(200, 100));
	m_pLabel->setAnchorPoint(CCPoint(0.0f,0.0f));
	//m_pLabel->set
    //// add the label as a child to this layer

	//swprintf(wstrTemp, L"좌표 (%d,%d)", g_MousePoint.x, g_MousePoint.y);
	//SetMsg();
	

	sprintf(strTemp,"좌표 (%f,%f)", g_MousePoint.x, g_MousePoint.y);
	m_pLabel->setString(strTemp);

    this->addChild(m_pLabel, 1);


	CCSprite* pSprite = CCSprite::create("Tile_1.png");
	pSprite->setPosition(0.0f,0.0f);
	pSprite->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(pSprite, 0);


	//string strNew = "아주대학교";
	//string strTemp2 = strNew;

	//string strTemp3;
	////sprintf(strTemp2.+c_str,"%c%c",strNew[0],steNew[1]);

	//strTemp3.push_back(strNew[0]);
	//strTemp3.push_back(strNew[1]);
	//strTemp3.push_back(strNew[2]);

	//CCLabelTTF* m_pLabel_1 = LabelTTF::create("", "Arial", 24);
 //   m_pLabel_1->setPosition(Point(800, 200));
	//m_pLabel_1->setString(strTemp3);
 //   this->addChild(m_pLabel_1, 1);
	//
	////strTemp2.push_back(strNew[0]);
	////strTemp2.push_back(strNew[1]);

	//
	//strTemp3.push_back(strNew[3]);
	//strTemp3.push_back(strNew[4]);
	//strTemp3.push_back(strNew[5]);

	//CCLabelTTF* m_pLabel_2 = LabelTTF::create("", "Arial", 24);
 //   m_pLabel_2->setPosition(Point(800, 250));
	//m_pLabel_2->setString(strTemp3);
 //   this->addChild(m_pLabel_2, 1);
	//
	////strTemp2.push_back(strNew[2]);

	//
	//strTemp3.push_back(strNew[6]);
	//strTemp3.push_back(strNew[7]);
	//strTemp3.push_back(strNew[8]);
	//
	//CCLabelTTF* m_pLabel_3 = LabelTTF::create("", "Arial", 24);
 //   m_pLabel_3->setPosition(Point(800, 300));
	//m_pLabel_3->setString(strTemp3);
 //   this->addChild(m_pLabel_3, 1);
	//
	////strTemp2.push_back(strNew[3]);
	//

	//CCLabelTTF* m_pLabel_4 = LabelTTF::create("", "Arial", 24);
 //   m_pLabel_4->setPosition(Point(800, 350));
	//m_pLabel_4->setString(strTemp3);
 //   this->addChild(m_pLabel_4, 1);
	//
	//CCLabelTTF* m_pLabel_5 = LabelTTF::create("", "Arial", 24);
 //   m_pLabel_5->setPosition(Point(800, 400));
	//m_pLabel_5->setString(strTemp3);
 //   this->addChild(m_pLabel_5, 1);

 //   // add "GameScene" splash screen"
	//auto sprite = Sprite::create("StageMenu_1.png");
 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Point(400,240));
	//sprite->setRotation(90.0f);
 //   // add the sprite as a child to this layer
 //   this->addChild(sprite, 0);

	 


	this->schedule(schedule_selector(GameScene::Update), 0.0);
	
	g_MapManager.Init(this);
	//D_SOUNDMNG->preloadBackgroundMusic("bgm.mp3");
	//D_SOUNDMNG->playEffect("bgm.mp3");

	/*m_aTestAnimation.Init(this,0,CCPoint(400,500),0.07f);
	for(int i=0; i<10; i++)
	{
		sprintf(strTemp,"Block_Pop_1_%d.png",i+1);
		m_aTestAnimation.Insert(strTemp);
	}*/

	m_TextDisplayer.Init(this,2,Point(0.0f,0.0f),"Commit Name으로서 Cocos2dx엔진에서 사용안함",100,550,40,23,20,ccColor3B(255,255,255));
	m_TextDisplayer.SetText("아주대학교 게임제작 소학회 브레인스톰/게임구성요소 설명/PartMap : 각각의 부분 맵/MapManager : 맵을 담아 보관하며 (맵을 씬처럼 체인지 해줌)/Hero : 플레이어가 조종하는 캐릭터/BlokingBlock : 충돌객체(통과불가)");
	m_TextDisplayer.SetProgressTime(0.03f);

	m_Hero = new CHero();
	m_Archer = new CArcher();
	m_Mage = new CArcher();

	m_Hero->Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 3,(D_TILE_HEIGHT) * 15));
	m_Archer->Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 2,(D_TILE_HEIGHT) * 15));
	m_Mage->Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 4,(D_TILE_HEIGHT) * 15));
	m_Monster[0].Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 4,(D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * (14)) ));
	m_Monster[1].Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 4,(D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * (9)) ));
	m_Monster[2].Init(this,200.0f * D_TILE_SCALE,1,CCPoint((D_TILE_WIDTH) * 4,(D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * (18)) ));
	
	g_UnitList.push_back((CUnit*)m_Hero);
	g_UnitList.push_back((CUnit*)m_Archer);
	g_UnitList.push_back((CUnit*)m_Mage);
	//g_UnitList.push_back((CUnit*)&m_Monster[0]);
//	g_UnitList.push_back((CUnit*)&m_Monster[1]);
	//g_UnitList.push_back((CUnit*)&m_Monster[2]);
	
	//m_PartMap.Init(this,3);


	//m_aTestAnimation.Insert("Block_Pop_1_1.png");
	m_fTimer = 0.0f;


    return true;
}




void GameScene::Update(float dt)
{

	//swprintf(wstrTemp, L"좌표 (%f,%f)",  g_MousePoint.x,  g_MousePoint.y);4
	//m_PartMap.Update(dt);
	g_MapManager.Update(dt);
	//SetMsg();
	m_TextDisplayer.Update(dt);
	m_fTimer+=dt;
	/*if(m_fTimer >= 8.0f)
	{
		m_fTimer = 0.0f;
		m_TextDisplayer.SetText("아주대학교 게임제작 소학회 브레인스톰/현재까지 완성된 라이브러리는/Sound : CocosDenshion/Sprite : CCSprite/Animation :BAnimation(제작)/TextDisplay : BTextDisplay(기존에 제작한거 포팅)/Button : BStyleButton(기존에 제작한거 Cocos2d-x용으로 포팅/ ");
	}*/

	m_Hero->Update(dt, &g_MapManager);
	m_Archer->Update(dt, &g_MapManager);
	m_Mage->Update(dt, &g_MapManager);
	m_Monster[0].Update(dt, &g_MapManager);
	m_Monster[1].Update(dt, &g_MapManager);
	m_Monster[2].Update(dt, &g_MapManager);
	//string strPath;
	//CCFileUtils::getInstance()->fullPathForFilename("Map_Max_1.txt");

	//CCFileUtils::getInstance()->fullPathForFilename("Map_Max_1.txt").c_str()
//	fscanf(fp1,"%d %d",&m_nWidth,&m_nHeight);
	
	int i=0;

	strBuffer = CCFileUtils::getInstance()->getFileData("Map_Max_1.txt","r", &(nBufferSize));

	while(1)
	{
		sWidth[i] = (*strBuffer);
		strBuffer++;
		i++;
		if((*strBuffer) == ' ')
		{
			strBuffer++;
			break;
		}
	}

	i=0;
	while(1)
	{
		sHeight[i] = (*strBuffer);
		strBuffer++;
		i++;
		if((*strBuffer) == ' ')
		{
			strBuffer++;
			break;
		}
	}
	m_nWidth = atoi(sWidth);
	m_nHeight = atoi(sHeight);
	
	sprintf(strTemp,"좌표 (%f,%f) %s 맵 %d %d", g_MousePoint.x, g_MousePoint.y, CCFileUtils::getInstance()->fullPathForFilename("Map_Max_1.txt").c_str(),m_nWidth,m_nHeight);
	m_pLabel->setString(strTemp);

	if(m_bTestButton.CheckAction() == true)
	{
		m_TextDisplayer.SetText("아주대학교 게임제작 소학회 브레인스톰/게임구성요소 설명/PartMap : 각각의 부분 맵/MapManager : 맵을 담아 보관하며 (맵을 씬처럼 체인지 해줌)/Hero : 플레이어가 조종하는 캐릭터/BlokingBlock : 충돌객체(통과불가)");
		m_bTestButton.Reset();
	}

	if(m_eGameStep == E_GAME_STEP_READY)
	{
		m_bTestButton.Update(dt);
//		m_aTestAnimation.Update(dt);
	}
	else if(m_eGameStep == E_GAME_STEP_PLAY)
	{

	}

	else if(m_eGameStep == E_GAME_STEP_END)
	{

	}



}
void GameScene::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{
 
    //...
 
    for (auto iter = touches.begin(); iter != touches.end(); iter++){
		g_MousePoint.x = (*iter)->getLocation().x;
		g_MousePoint.y = (*iter)->getLocation().y;
		if(m_bTestButton.TouchBegan(CCPoint((*iter)->getLocation().x,(*iter)->getLocation().y)) == true)
		{

			float m_fY = (*iter)->getLocation().y;
			m_Hero->Run(RadToDeg(atan2( m_fY - m_bTestButton.m_CPoint.y,(*iter)->getLocation().x - m_bTestButton.m_CPoint.x)));
		}
      //Point location = (*iter)->getLocation();
      //addNewSpriteAtPosition(location);
    }
 
    //...
 
}
 
void GameScene::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event)
{
	bool bJoySticking = false;

	  for (auto iter = touches.begin(); iter != touches.end(); iter++){
		g_MousePoint.x = (*iter)->getLocation().x;
		g_MousePoint.y = (*iter)->getLocation().y;
		if(m_bTestButton.m_bTouched == true && m_bTestButton.TouchMoved(CCPoint((*iter)->getLocation().x,(*iter)->getLocation().y)) == true)
		{
			float m_fY = (*iter)->getLocation().y;
			m_Hero->Run(RadToDeg(atan2( m_fY - m_bTestButton.m_CPoint.y,(*iter)->getLocation().x - m_bTestButton.m_CPoint.x)));
			bJoySticking = true;
		}
		/*else if(bJoySticking != true)
		{
			
		}*/
      //Point location = (*iter)->getLocation();
      //addNewSpriteAtPosition(location);
    }

	  if(bJoySticking == false)
	  {
		  m_bTestButton.m_bTouched = false;
		  m_bTestButton.ChangeState(E_BUTTON_WAIT);
		  m_Hero->ChangeState(E_HERO_STATE_NONE);
	  }
}
 
void GameScene::onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event)
{

}
 
void GameScene::onTouchesEnded(const std::vector<Touch*>&touches, Event* unused_event)
{
	  for (auto iter = touches.begin(); iter != touches.end(); iter++){
		g_MousePoint.x = (*iter)->getLocation().x;
		g_MousePoint.y = (*iter)->getLocation().y;
		m_bTestButton.TouchEnded(CCPoint((*iter)->getLocation().x,(*iter)->getLocation().y));
		m_Hero->ChangeState(E_HERO_STATE_NONE);
		//m_bTestButton.ChangeState(E_BUTTON_WAIT);
		//m_bTestButton.m_bTouched = false;

		//m_bTestButton.setPositionY(0.0f);
      //Point location = (*iter)->getLocation();
      //addNewSpriteAtPosition(location);
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_INRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
