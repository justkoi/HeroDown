#include "stdafx.h"



stHPos g_stArcher(0,0);
stHPos g_stHero(6,6);


void CArcher::SetHuristic(stHPos* sPos, stHPos ePos)
{
	int f = 0;
	int g = 10; //!< 임의의 가중치 (한칸)
	int h = 0;

	h = (abs(ePos.nX - sPos->nX) * 10) + (abs(ePos.nY - sPos->nY) * 10);
	f = sPos->f + g + h;

	sPos->f = f;
	m_Huristic[sPos->nX][sPos->nY] = f;
}

void CArcher::Start(stHPos sPos)
{
	int nNowPosX = 0;
	int nNowPosY = 0;
	//!< 자신을 닫힌 노드에 추가
	//g_MapManager.getCurMap()->m_BlokingMap[
	nClose++;
	//!< 4방향 검사


	nNowPosX = sPos.nX - 1;
	nNowPosY = sPos.nY;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 열린노드라면
		if(m_PathMap[nNowPosX][nNowPosY] == 0)
		{
			stHPos* newPos = new stHPos(nNowPosX,nNowPosY);
			//!< 해당노드를 OpenList에 추가
			newPos->f = sPos.f;
	m_PathMap[nNowPosX][nNowPosY] = 1;
			m_NewOpenList.push_back(newPos);
			SetHuristic(newPos,g_stHero);
			
		}
	}

	nNowPosX = sPos.nX + 1;
	nNowPosY = sPos.nY;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 열린노드라면
		if(m_PathMap[nNowPosX][nNowPosY] == 0)
		{
			stHPos* newPos = new stHPos(nNowPosX,nNowPosY);
			//!< 해당노드를 OpenList에 추가
			newPos->f = sPos.f;
	m_PathMap[nNowPosX][nNowPosY] = 1;
			m_NewOpenList.push_back(newPos);
			SetHuristic(newPos,g_stHero);
		}
	}
	
	nNowPosX = sPos.nX;
	nNowPosY = sPos.nY-1;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 열린노드라면
		if(m_PathMap[nNowPosX][nNowPosY] == 0)
		{
			stHPos* newPos = new stHPos(nNowPosX,nNowPosY);
			//!< 해당노드를 OpenList에 추가
			newPos->f = sPos.f;
	m_PathMap[nNowPosX][nNowPosY] = 1;
			m_NewOpenList.push_back(newPos);
			SetHuristic(newPos,g_stHero);
		}
	}
	
	nNowPosX = sPos.nX;
	nNowPosY = sPos.nY+1;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 열린노드라면
		if(m_PathMap[nNowPosX][nNowPosY] == 0)
		{
			stHPos* newPos = new stHPos(nNowPosX,nNowPosY);
			//!< 해당노드를 OpenList에 추가
			newPos->f = sPos.f;
	m_PathMap[nNowPosX][nNowPosY] = 1;
			m_NewOpenList.push_back(newPos);
			SetHuristic(newPos,g_stHero);
		}
	}
	
	
}
void CArcher::ListCounting()
{
	for(int i=0; i<m_NewOpenList.size(); i++)
	{
		m_OpenList.push_back(m_NewOpenList[i]);
	}
	m_NewOpenList.clear();
}
void CArcher::NextStep()
{
	
	vector<stHPos*>::iterator it;
	for(it = m_OpenList.begin(); it != m_OpenList.end(); it++)
	{
		//if(map[(*it)->nX][(*it)->nY] != 1)
		//{
			Start( *(*it) );
			delete (*it);
			//it = m_OpenList.erase(it);
			//it++;
			//it--;
		//}
	}
	m_OpenList.clear();
}

bool CArcher::Ended()
{
	vector<stHPos*>::iterator it;
	for(it = m_OpenList.begin(); it != m_OpenList.end(); it++)
	{
		if( (*it)->nX == g_stHero.nX && (*it)->nY == g_stHero.nY )
		{
			return true;
		}
	}
	return false;
}


void CArcher::AddPath(stHPos sPos, int minh)
{
	stHPos* newPos = new stHPos(sPos.nX,sPos.nY);
	m_PathList.push_back(newPos);

	int nNowPosX = 0;
	int nNowPosY = 0;

	int nMinPosX = 0;
	int nMinPosY = 0;

	int nMinh = minh;

	//!< 4방향 검사
	nNowPosX = sPos.nX - 1;
	nNowPosY = sPos.nY;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 가중치비교
		if(m_Huristic[nNowPosX][nNowPosY] < nMinh)
		{
			nMinPosX = nNowPosX;
			nMinPosY = nNowPosY;
			nMinh = m_Huristic[nNowPosX][nNowPosY];
		}
	}
	//!< 4방향 검사
	nNowPosX = sPos.nX + 1;
	nNowPosY = sPos.nY;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 가중치비교
		if(m_Huristic[nNowPosX][nNowPosY] < nMinh)
		{
			nMinPosX = nNowPosX;
			nMinPosY = nNowPosY;
			nMinh = m_Huristic[nNowPosX][nNowPosY];
		}
	}

	//!< 4방향 검사
	nNowPosX = sPos.nX;
	nNowPosY = sPos.nY - 1;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 가중치비교
		if(m_Huristic[nNowPosX][nNowPosY] < nMinh)
		{
			nMinPosX = nNowPosX;
			nMinPosY = nNowPosY;
			nMinh = m_Huristic[nNowPosX][nNowPosY];
		}
	}

	//!< 4방향 검사
	nNowPosX = sPos.nX;
	nNowPosY = sPos.nY + 1;
	//!< 범위안에 있고
	if(nNowPosX >= 0 && nNowPosX <= (g_MapManager.getCurMap()->getMapWidth()-1) && nNowPosY >= 0 && nNowPosY <= (g_MapManager.getCurMap()->getMapHeight()-1))
	{
		//!< 가중치비교
		if(m_Huristic[nNowPosX][nNowPosY] < nMinh)
		{
			nMinPosX = nNowPosX;
			nMinPosY = nNowPosY;
			nMinh = m_Huristic[nNowPosX][nNowPosY];
		}
	}
	if(nMinPosX == g_stArcher.nX && nMinPosY == g_stArcher.nY)
		return;

	AddPath(stHPos(nMinPosX, nMinPosY), nMinh);

}
void CArcher::Init(CCLayer* pThisScene, float fMoveSpeed, int nLayer, CCPoint stPos)
{
	CUnit::Init(pThisScene);
	nClose = 0;

	m_fSearchTimer = 0.0f;
	m_fSearchTime = 0.5f;

	m_fJudgmentArea = 8.0f;
	m_stTargetCommandPoint = CCPoint(0,0);

	m_PathMap = new int*[g_MapManager.getCurMap()->getMapHeight()];
	for(int i=0; i<g_MapManager.getCurMap()->getMapHeight(); i++)
	{
		m_PathMap[i] = new int[g_MapManager.getCurMap()->getMapWidth()];
	}
	
	m_Huristic = new int*[g_MapManager.getCurMap()->getMapHeight()];
	for(int i=0; i<g_MapManager.getCurMap()->getMapHeight(); i++)
	{
		m_Huristic[i] = new int[g_MapManager.getCurMap()->getMapWidth()];
	}


	setMoveSpeed(fMoveSpeed);
	setPos(stPos);
	setDerection(E_DERECTION_LEFT);

	m_nLayer = nLayer;
	m_fRotation = 0.0f;

	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].Init(getThisScene(), m_nLayer,getPos(),0.1f);
	}

	m_pAni[E_HERO_STATE_NONE].Insert("Archer_3.png");
	//m_pAni[E_HERO_STATE_NONE].setAnchorPoint(0.0f,0.0f);
	m_pAni[E_HERO_STATE_RUN].Insert("Archer_2.png");
	m_pAni[E_HERO_STATE_RUN].Insert("Archer_3.png");
	m_pAni[E_HERO_STATE_RUN].Insert("Archer_4.png");
	//m_pAni[E_HERO_STATE_NONE].setAnchorPoint(0.0f,0.0f);
	m_pAni[E_HERO_STATE_NONE].setScale(D_TILE_SCALE);
	m_pAni[E_HERO_STATE_RUN].setScale(D_TILE_SCALE);
	//m_pAni[E_HERO_STATE_NONE]
	ChangeState(E_HERO_STATE_NONE);
	
	m_nNowPath = 0;
	m_nAroundArea = 3;
	
	//Command_Move(CCPoint(0.0f + (float)(D_TILE_WIDTH * 5),  (D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * 14)));
	
}
void CArcher::Update(float dt, CMapManager* MapManager)
{
	
	g_stArcher.nX =( getPos().x + (D_TILE_WIDTH/2) )/D_TILE_WIDTH;
	g_stArcher.nY = ((D_TILE_HEIGHT * MapManager->getCurMap()->getMapHeight()) - getPos().y + (D_TILE_HEIGHT/2))/D_TILE_HEIGHT;

	m_fSearchTimer += dt;

	if(m_fSearchTimer >= m_fSearchTime)
	{
		if( !(g_stArcher.nX >= g_stHero.nX - m_nAroundArea && g_stArcher.nX <= g_stHero.nX + m_nAroundArea &&
			g_stArcher.nY >= g_stHero.nY - m_nAroundArea && g_stArcher.nY <= g_stHero.nY + m_nAroundArea ))
		{
			m_fSearchTimer -= m_fSearchTime;
			SearchPath();
		}
	}


	
	vector<CBlokingBlock*>::iterator it;
	vector<CUnit*>::iterator it2;

	
	//g_stArcher.nX = getPos().x/D_TILE_WIDTH;
	//g_stArcher.nY = ((D_TILE_HEIGHT * MapManager->getCurMap()->getMapHeight()) - getPos().y)/D_TILE_HEIGHT;
	
	CUnit::Update(dt);
	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].Update(dt);
	}


	
	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].setVisible(false);
	}
	if(m_eState == E_HERO_STATE_RUN)
	{
		
			//Command_Move(CCPoint(0.0f + (float)(D_TILE_WIDTH * 5),  (D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * 14)));
	
			if( ! ( getPos().x  <= m_stTargetCommandPoint.x + m_fJudgmentArea && (getPos().x ) >= m_stTargetCommandPoint.x - m_fJudgmentArea) )
			{
				if( getPos().x  <= m_stTargetCommandPoint.x  )
				{
					setDerection(E_DERECTION_RIGHT);
				}
				if( getPos().x  >= m_stTargetCommandPoint.x  )
				{
					setDerection(E_DERECTION_LEFT);
				}
			}
			else
			{
				if( ! ( getPos().y  <= m_stTargetCommandPoint.y + m_fJudgmentArea && getPos().y  >= m_stTargetCommandPoint.y - m_fJudgmentArea) )
				{
					if( getPos().y  <= m_stTargetCommandPoint.y  )
					{
						setDerection(E_DERECTION_UP);
					}
					if( getPos().y  >= m_stTargetCommandPoint.y  )
					{
						setDerection(E_DERECTION_DOWN);
					}
				}
				else
				{
					m_nNowPath--;
					if(m_nNowPath >= 1)
					{
						Command_Move(CCPoint(0.0f + (float)(D_TILE_WIDTH * m_PathList[m_nNowPath]->nX),  (D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * m_PathList[m_nNowPath]->nY)));
					}
					else
					{
						Command_Stop();
					}
				}
			}
		
	}
	if(m_eState == E_HERO_STATE_RUN)
	{
		m_bHitTest[0] = false;
		m_bHitTest[1] = false;
		m_bHitTest[2] = false;
		m_bHitTest[3] = false;

		//!< 이하 구문 이동 & 충돌처리 & 빨려들어가기 처리
		if(getDerection() == E_DERECTION_RIGHT)
		{
			for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
			{
				
				CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x + (getMoveSpeed() * (dt))  + 1;//  //
				stTemp1.y = stTemp1.y; //

				CCPoint stTemp2 = (*it)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //

				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;


				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_RIGHT] = true;
					if(stTemp1.y >= stTemp2.y + D_TILE_ENTERING_SENS) //!< 충돌객체 위 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x && (*it)->m_stIndex.y == stBlockIndex.y-1) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_UP
						}
					}
					else if(stTemp1.y <= stTemp2.y - D_TILE_ENTERING_SENS) //!< 충돌객체 아래 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x && (*it)->m_stIndex.y == stBlockIndex.y+1) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_DOWN
						}
					}
					break;
				}
			}
			//!< 이하 유닛테스트
			for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)
			{
				//!< 본인 검사안함
				if((*it2)->getIndex() == getIndex())
				{
					continue;
				}

				//CCPoint stBlockIndex = (*it2)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x + (getMoveSpeed() * (dt))  + 1;//  //
				stTemp1.y = stTemp1.y; //

				CCPoint stTemp2 = (*it2)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //

				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;

				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_RIGHT] = true;
				}
			}
			if(m_bHitTest[E_DERECTION_RIGHT] == false)
				setPos( CCPoint(getPos().x + (getMoveSpeed() * dt) ,  getPos().y) ); // + getMoveSpeed() * dt
		}
		else if(getDerection() == E_DERECTION_UP)
		{
			
			for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
			{
				
				CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x ;//  //
				stTemp1.y = stTemp1.y + (getMoveSpeed() * (dt))  + 1; //

				CCPoint stTemp2 = (*it)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;


				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_UP] = true;
					if(stTemp1.x >= stTemp2.x + D_TILE_ENTERING_SENS) //!< 충돌객체 오른쪽 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x+1 && (*it)->m_stIndex.y == stBlockIndex.y) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_RIGHT
						}
					}
					else if(stTemp1.x <= stTemp2.x - D_TILE_ENTERING_SENS) //!< 충돌객체 왼쪽 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x-1 && (*it)->m_stIndex.y == stBlockIndex.y) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_LEFT
						}
					}
					break;
				}
			}
			//!< 이하 유닛테스트
			for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)
			{
				//!< 본인 검사안함
				if((*it2)->getIndex() == getIndex())
				{
					continue;
				}

				//CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x ;//  //
				stTemp1.y = stTemp1.y + (getMoveSpeed() * (dt))  + 1; //

				CCPoint stTemp2 = (*it2)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;

				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_UP] = true;
				}
			}
			if(m_bHitTest[E_DERECTION_UP] == false)
				setPos( CCPoint(getPos().x  , getPos().y + getMoveSpeed() * dt) ); // + getMoveSpeed() * dt
		}
		else if(getDerection() == E_DERECTION_LEFT)
		{
			for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
			{
				
				CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x - (getMoveSpeed() * (dt))  - 1;//  //
				stTemp1.y = stTemp1.y; //

				CCPoint stTemp2 = (*it)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;


				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_LEFT] = true;
					if(stTemp1.y >= stTemp2.y + D_TILE_ENTERING_SENS) //!< 충돌객체 위 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x && (*it)->m_stIndex.y == stBlockIndex.y-1) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_UP
						}
					}
					else if(stTemp1.y <= stTemp2.y - D_TILE_ENTERING_SENS) //!< 충돌객체 아래 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x && (*it)->m_stIndex.y == stBlockIndex.y+1) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_DOWN
						}
					}
					break;
				}
			}
			//!< 이하 유닛테스트
			for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)
			{
				//!< 본인 검사안함
				if((*it2)->getIndex() == getIndex())
				{
					continue;
				}

				//CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x - (getMoveSpeed() * (dt))  - 1;//  //
				stTemp1.y = stTemp1.y; //

				CCPoint stTemp2 = (*it2)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;

				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_LEFT] = true;
				}
			}
			if(m_bHitTest[E_DERECTION_LEFT] == false)
				setPos( CCPoint( getPos().x - (getMoveSpeed() * dt) ,getPos().y) ); // + getMoveSpeed() * dt
		}
		else if(getDerection() == E_DERECTION_DOWN)
		{
			
			for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
			{
				
				CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x ;//  //
				stTemp1.y = stTemp1.y - (getMoveSpeed() * (dt)) - 1; //

				CCPoint stTemp2 = (*it)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;


				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_DOWN] = true;

					
					if(stTemp1.x >= stTemp2.x + D_TILE_ENTERING_SENS) //!< 충돌객체 오른쪽 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x+1 && (*it)->m_stIndex.y == stBlockIndex.y) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_RIGHT
						}
					}
					else if(stTemp1.x <= stTemp2.x - D_TILE_ENTERING_SENS) //!< 충돌객체 왼쪽 (1/4) 이상으로 축이 넘어갈경우
					{
						bool bSpaced = true;
						for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)
						{
							if( (*it)->m_stIndex.x == stBlockIndex.x-1 && (*it)->m_stIndex.y == stBlockIndex.y) //!< 옆에 블록이 있으면 패스
							{
								bSpaced = false;
								break;
							}
						}
						if(bSpaced == true)
						{
							D_HITCHECK_LEFT
						}
					}
					break;
				}
			}
			//!< 이하 유닛테스트
			for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)
			{
				//!< 본인 검사안함
				if((*it2)->getIndex() == getIndex())
				{
					continue;
				}

				//CCPoint stBlockIndex = (*it)->m_stIndex;

				CCPoint stTemp1 = getPos();
				stTemp1.x = stTemp1.x ;//  //
				stTemp1.y = stTemp1.y - (getMoveSpeed() * (dt)) - 1; //

				CCPoint stTemp2 = (*it2)->getPos();
				stTemp2.x = stTemp2.x;//  //
				stTemp2.y = stTemp2.y; //
				
				newRECT rc1;
				rc1.left = stTemp1.x;
				rc1.right = stTemp1.x + D_HERO_WIDTH;
				rc1.top = stTemp1.y;
				rc1.bottom = stTemp1.y - D_HERO_HEIGHT;

				newRECT rc2;
				rc2.left = stTemp2.x;
				rc2.right = stTemp2.x + D_HERO_WIDTH;
				rc2.top = stTemp2.y;
				rc2.bottom = stTemp2.y - D_HERO_HEIGHT;

				if(BHitTest::HitTest_Square(rc1,rc2) == true)
				{
					m_bHitTest[E_DERECTION_DOWN] = true;
				}
			}
			if(m_bHitTest[E_DERECTION_DOWN] == false)
				setPos( CCPoint( getPos().x , getPos().y - getMoveSpeed() * dt) ); // + getMoveSpeed() * dt
		}
	}
	m_pAni[(int)m_eState].setVisible(true);
	m_pAni[(int)m_eState].setPosition(CCPoint( g_CameraPoint_Smooth.x + getPos().x,  g_CameraPoint_Smooth.y + getPos().y));


	if(getDerection() == E_DERECTION_RIGHT)
		m_pAni[(int)m_eState].setRotation(0.0f);
	else if(getDerection() == E_DERECTION_UP)
		m_pAni[(int)m_eState].setRotation(270.0f);
	else if(getDerection() == E_DERECTION_LEFT)
		m_pAni[(int)m_eState].setRotation(180.0f);
	else if(getDerection() == E_DERECTION_DOWN)
		m_pAni[(int)m_eState].setRotation(90.0f);
}

void CArcher::ChangeState(E_HERO_STATE eState)
{
	m_eState = eState;
}

void CArcher::Command_Move(CCPoint stPos)
{
	m_eState = E_HERO_STATE_RUN;
	m_stTargetCommandPoint = stPos;
}
void CArcher::Command_Stop()
{
	m_eState = E_HERO_STATE_NONE;
}
void CArcher::Run(float fRotation)
{
	if(m_eState != E_HERO_STATE_RUN)
		ChangeState(E_HERO_STATE_RUN);

	if(fRotation < 0)
		fRotation += 360.0f;
	
	m_fRotation = fRotation;

	if(m_fRotation > 315.0f || m_fRotation <= 45.0f)
		setDerection(E_DERECTION_RIGHT);
	else if(m_fRotation > 45.0f && m_fRotation <= 135.0f)
		setDerection(E_DERECTION_UP);
	else if(m_fRotation > 135.0f && m_fRotation <= 225.0f)
		setDerection(E_DERECTION_LEFT);
	else if(m_fRotation > 225.0f && m_fRotation <= 315.0f)
		setDerection(E_DERECTION_DOWN);


}

void CArcher::SearchPath()
{
	m_nNowPath = 0;
	nClose = 0;
	//!< 초기화
	vector<stHPos*>::iterator it;
	for(it = m_PathList.begin(); it != m_PathList.end(); it++)
	{
		delete (*it);
	}
	m_PathList.clear();

	vector<stHPos*>::iterator it2;
	for(it2 = m_OpenList.begin(); it2 != m_OpenList.end(); it2++)
	{
		delete (*it2);
	}
	m_OpenList.clear();
	
	vector<stHPos*>::iterator it3;
	for(it3 = m_NewOpenList.begin(); it3 != m_NewOpenList.end(); it3++)
	{
		delete (*it3);
	}
	m_NewOpenList.clear();
	int nMaxClose = g_MapManager.getCurMap()->getMapWidth() * g_MapManager.getCurMap()->getMapHeight();

	for(int x = 0; x < g_MapManager.getCurMap()->getMapWidth(); x++)
	{
		for(int y = 0; y < g_MapManager.getCurMap()->getMapHeight(); y++)
		{
			m_PathMap[x][y] = 0;
			m_Huristic[x][y] = 9999999;
		}
	}

	for(int i=0; i<g_MapManager.getCurMap()->m_BlokingMap.size(); i++)
	{
		m_PathMap[(int)g_MapManager.getCurMap()->m_BlokingMap[i]->m_stIndex.x][(int)g_MapManager.getCurMap()->m_BlokingMap[i]->m_stIndex.y] = 1;
		m_Huristic[(int)g_MapManager.getCurMap()->m_BlokingMap[i]->m_stIndex.x][(int)g_MapManager.getCurMap()->m_BlokingMap[i]->m_stIndex.y] = 9999999;
		nClose++;

	}
	m_Huristic[g_stArcher.nX][g_stArcher.nY] = 0;
	Start(g_stArcher);
	m_PathMap[g_stArcher.nX][g_stArcher.nY] = 1;
	ListCounting();

	while(1)
	{
		NextStep();
		ListCounting();

		if(Ended() == true)
		{
			AddPath(g_stHero, 9999999);
			
			break;
		}
		if(nClose >= nMaxClose)
			break;
	}
	if(m_PathList.size() >= 1)
	{
		m_nNowPath = m_PathList.size() - 1;
		Command_Move(CCPoint(0.0f + (float)(D_TILE_WIDTH * m_PathList[m_nNowPath]->nX),  (D_TILE_HEIGHT * g_MapManager.getCurMap()->getMapHeight()) - (float)(D_TILE_HEIGHT * m_PathList[m_nNowPath]->nY)));
	}
					

}