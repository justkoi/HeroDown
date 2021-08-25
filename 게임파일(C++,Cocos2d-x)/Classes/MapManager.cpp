#include "stdafx.h"

void CMapManager::Init(CCLayer* pThisScene)
{
	m_bNowChange = false;
	m_stNextHeroPos = CCPoint(90.0f,90.0f);
	//m_BlindManager.Init(pThisScene);
	//m_CTargetHero = CTargetHero;
	m_pThisScene = pThisScene;
	ChangeMap(3);
}
void CMapManager::Update(float dt)
{
	m_CNowMap->Update(dt);
	//m_BlindManager.Update(dt);

	if(m_bNowChange == true)
	{
		//if( m_BlindManager.m_bAction == true )
		//{
			m_CNowMap->Exit();
			delete m_CNowMap;
			m_CNowMap = NULL;
			m_CNowMap = CreateMap();
			//m_BlindManager.StartBlind(1,E_BLINDSTATE_FADE_IN,1.0f,true);
			m_bNowChange = false;
			//m_CTargetHero->m_bMapChangeAble = true;
			//m_CTargetHero->setPos(m_stNextHeroPos);

			//!< 카메라 위치조종
			//g_stSmoothCamPos_Stage = g_stCamPos_Stage;
		//}
	}
	//if(m_BlindManager.m_eState == E_BLINDSTATE_FADE_IN)
	//{
		//if( m_BlindManager.m_bAction == true )
		//{
			//m_CTargetHero->m_bMapChangeAble = true;
			//m_BlindManager.m_bAction = false;
		//}
	//}
}
void CMapManager::Exit()
{
	
	m_CNowMap->Exit();
	delete m_CNowMap;
}
CPartMap* CMapManager::getCurMap()
{
	return m_CNowMap;
}
CPartMap* CMapManager::CreateMap()
{
	CPartMap* CNewMap = new CPartMap();
	CNewMap->Init(m_pThisScene,m_nNowMap);
	return CNewMap;
}
void CMapManager::ChangeMap(int nMapIndex)
{
	//if(m_bNowChange == false)
	//{
		if(m_CNowMap == NULL)
		{
			m_nNowMap = nMapIndex;
			m_CNowMap = CreateMap();
			//m_BlindManager.StartBlind(1,E_BLINDSTATE_FADE_IN,1.0f);
			//CTargetHero->m_bMapChangeAble = false;
		}
		else
		{
			//if(m_bNowChange == false)
			//{
				//m_BlindManager.StartBlind(1,E_BLINDSTATE_FADE_OUT,1.0f);
				m_bNowChange = true;
			//	m_CTargetHero = CTargetHero;
				m_nNowMap = nMapIndex;
			//	CTargetHero->m_bMapChangeAble = false;
			//}
		}
	//}
}