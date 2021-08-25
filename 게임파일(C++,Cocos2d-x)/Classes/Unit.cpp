#include "stdafx.h"

int nNowIndex = 0;

//!< 초기화 함수
void CUnit::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;
	setIndex(nNowIndex);
	nNowIndex++;

	m_HpBar[0] = CCSprite::create("Hp_1.png");
	
	m_HpBar[0]->setPosition(CCPoint( g_CameraPoint_Smooth.x + getPos().x,  g_CameraPoint_Smooth.y + getPos().y + (D_TILE_HEIGHT/2) + D_HP_PAD));
	m_pThisScene->addChild(m_HpBar[0],0);

	m_HpBar[1] = CCSprite::create("Hp_2.png");
	m_HpBar[1]->setPosition(CCPoint( g_CameraPoint_Smooth.x + getPos().x,  g_CameraPoint_Smooth.y + getPos().y + (D_TILE_HEIGHT/2) + D_HP_PAD));
	m_pThisScene->addChild(m_HpBar[1],2);

	m_HpBar[2] = CCSprite::create("Hp_3.png");
	m_HpBar[2]->setPosition(CCPoint( g_CameraPoint_Smooth.x + getPos().x,  g_CameraPoint_Smooth.y + getPos().y + (D_TILE_HEIGHT/2) + D_HP_PAD));
	m_pThisScene->addChild(m_HpBar[2],3);
}

void CUnit::Update(float dt)
{
	m_HpBar[1]->setTextureRect(Rect(0,0,D_TILE_WIDTH * (m_fNowHp/m_fMaxHp),10));

	for(int i=0; i<3; i++)
	{
		m_HpBar[i]->setPosition(CCPoint( g_CameraPoint_Smooth.x + getPos().x,  g_CameraPoint_Smooth.y + getPos().y + (D_TILE_HEIGHT/2) + D_HP_PAD));//+ (D_TILE_HEIGHT/2) + D_HP_PAD
	}
}
void CUnit::Exit()
{

}



// =====> 이하 변수 set get구문 <=====

void CUnit::setPos(CCPoint stPos)
{
	m_stPos = stPos;
}

CCPoint CUnit::getPos()
{
	return m_stPos;
}
void CUnit::setMoveSpeed(float fMoveSpeed)
{
	m_fMoveSpeed = fMoveSpeed;
}
float CUnit::getMoveSpeed()
{
	return m_fMoveSpeed;
}


void CUnit::setAttackDmg(float fAttackDmg)
{
	m_fAttackDmg = fAttackDmg;
}
float CUnit::getAttackDmg()
{
	return m_fAttackDmg;
}
	
void CUnit::setNowHp(float fNowHp)
{
	m_fNowHp = fNowHp;
}
float CUnit::getNowHp()
{
	return m_fNowHp;
}
	
void CUnit::setMaxHp(float fMaxHp)
{
	m_fMaxHp = fMaxHp;
}
float CUnit::getMaxHp()
{
	return m_fMaxHp;
}


void CUnit::setThisScene(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;
}
CCLayer* CUnit::getThisScene()
{
	return m_pThisScene;
}
void CUnit::setDerection(E_DERECTION eDerection)
{
	m_eDerection = eDerection;
}
E_DERECTION CUnit::getDerection()
{
	return m_eDerection;
}
void CUnit::setIndex(int nIndex)
{
	m_nIndex = nIndex;
}
int CUnit::getIndex()
{
	return m_nIndex;
}