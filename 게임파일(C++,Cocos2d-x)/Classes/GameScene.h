#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "stdafx.h"

USING_NS_CC;


class GameScene : public cocos2d::Layer
{
public:
	//!< 게임진행단계
	E_GAME_STEP m_eGameStep;
	//!< Test라벨
	LabelTTF* m_pLabel;
	//!<Test스타일 버튼
	BStyleButton m_bTestButton;
	//!<Test애니메이션
	//BAnimation 
	//BAnimation m_aTestAnimation;
	//!<Tset 텍스트 디스플레이
	BTextDisplay m_TextDisplayer;
	float m_fTimer;

	//CPartMap m_PartMap;

	//!< 히어로
	CHero* m_Hero;
	//!< 아쳐
	CArcher* m_Archer;
	//!< 마법사
	CArcher* m_Mage;
	//1< 몬스터
	CMonster m_Monster[3];
	
public:
	void SetMsg();
	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


	
	void Update(float dt);

	//virtual void onEnter();

	//!< 터치함수 정의

	virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);


	//virtual void  registerWithTouchDispatcher();
	/*
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
    */
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
