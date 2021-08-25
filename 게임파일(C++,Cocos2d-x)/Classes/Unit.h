#pragma once

#include "stdafx.h"

typedef enum _e_hero_derction
{
	E_DERECTION_LEFT,
	E_DERECTION_RIGHT,
	E_DERECTION_UP,
	E_DERECTION_DOWN,
	E_DERECTION_MAX
}E_DERECTION;


class CUnit
{
private:
	//!< 위치
	CCPoint m_stPos;
	//!< 소속 씬
	CCLayer* m_pThisScene;
	//!< 현재 방향
	E_DERECTION m_eDerection;

	//!< 인덱스
	int m_nIndex;

	//!< 공격력
	float m_fAttackDmg;
	//!< 체력
	float m_fNowHp;
	//!< 체력 맥스
	float m_fMaxHp;
	//!< 방어력
	float m_fDeffence;
	//!< 이동속도
	float m_fMoveSpeed;

	CCSprite* m_HpBar[3];//[3];

	//virtual int m_nLayer;

	

public:
	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();
	
public:

	void setPos(CCPoint stPos);
	CCPoint getPos();

	void setMoveSpeed(float fMoveSpeed);
	float getMoveSpeed();
	
	void setAttackDmg(float fAttackDmg);
	float getAttackDmg();
	
	void setNowHp(float fNowHp);
	float getNowHp();
	
	void setMaxHp(float fMaxHp);
	float getMaxHp();

	void setThisScene(CCLayer* pThisScene);
	CCLayer* getThisScene();

	void setDerection(E_DERECTION eDerection);
	E_DERECTION getDerection();
	
	void setIndex(int nIndex);
	int getIndex();


};