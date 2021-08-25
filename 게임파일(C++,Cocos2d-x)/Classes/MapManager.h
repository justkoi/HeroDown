#pragma once

#include "stdafx.h"

class CHero;
class CPartMap;
class CMapManager
{
private:
	CPartMap* m_CNowMap;
	int		m_nNowMap;

	//CBlindManager m_BlindManager;
	//CHero* m_CTargetHero;
public:
	bool	m_bNowChange;
	CCLayer* m_pThisScene;
	CCPoint m_stNextHeroPos;

	CMapManager()
	{
		m_pThisScene = NULL;
		m_CNowMap = NULL;
		m_nNowMap = 1;
	};
	~CMapManager()
	{

	};
public:
	CPartMap* getCurMap();
public:
	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();
public:
	CPartMap* CreateMap(); //!< 새로운 맵을 만들어서 Return;
	void DeleteMap(); //!< 현재 맵을 지운다.

	void ChangeMap(int nMapIndex); //!< 맵을 바꾼다.

};