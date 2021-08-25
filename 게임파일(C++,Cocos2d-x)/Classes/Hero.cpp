#include "stdafx.h"



void CHero::Init(CCLayer* pThisScene, float fMoveSpeed, int nLayer, CCPoint stPos)
{
	CUnit::Init(pThisScene);
	setMoveSpeed(fMoveSpeed);
	setPos(stPos);
	setDerection(E_DERECTION_LEFT);

	m_nLayer = nLayer;
	m_fRotation = 0.0f;

	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].Init(getThisScene(), m_nLayer,getPos(),0.1f);
	}

	m_pAni[E_HERO_STATE_NONE].Insert("Hero_3.png");
	//m_pAni[E_HERO_STATE_NONE].setAnchorPoint(0.0f,0.0f);
	m_pAni[E_HERO_STATE_RUN].Insert("Hero_2.png");
	m_pAni[E_HERO_STATE_RUN].Insert("Hero_3.png");
	m_pAni[E_HERO_STATE_RUN].Insert("Hero_4.png");
	//m_pAni[E_HERO_STATE_NONE].setAnchorPoint(0.0f,0.0f);
	m_pAni[E_HERO_STATE_NONE].setScale(D_TILE_SCALE);
	m_pAni[E_HERO_STATE_RUN].setScale(D_TILE_SCALE);
	//m_pAni[E_HERO_STATE_NONE]
	ChangeState(E_HERO_STATE_NONE);

	

}
void CHero::Update(float dt, CMapManager* MapManager)
{
	vector<CBlokingBlock*>::iterator it;
	vector<CUnit*>::iterator it2;


	/*float fSCSpeed = 1.0f;

	float fSX = 0;
	float fSY = 0;*/
	g_CameraPoint = CCPoint(  (D_PHONE_WIDTH/2) - getPos().x, (D_PHONE_HEIGHT/2) - getPos().y );

	//(D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i))

	g_stHero.nX =( getPos().x + (D_TILE_WIDTH/2) )/D_TILE_WIDTH;
	g_stHero.nY = ((D_TILE_HEIGHT * MapManager->getCurMap()->getMapHeight()) - getPos().y + (D_TILE_HEIGHT/2))/D_TILE_HEIGHT;
	/*if((g_CameraPoint.x/60) <= fSCSpeed)
		fSX = fSCSpeed;
	if((g_CameraPoint.y/60) <= fSCSpeed)
		fSY = fSCSpeed;

	if(g_CameraPoint_Smooth.x < g_CameraPoint.x)
	{*/
	//if(g_CameraPoint_Smooth.x < abs(g_CameraPoint.x))
		/*if(g_CameraPoint_Smooth.x >= g_CameraPoint.x)
		{
			g_CameraPoint_Smooth.x = g_CameraPoint.x;
		}*/
	//}

	//if(g_CameraPoint_Smooth.y < -g_CameraPoint.y)
	//{
	//	g_CameraPoint_Smooth.y = g_CameraPoint_Smooth.y + ((fSY) * dt);
	//	if(g_CameraPoint_Smooth.y >= g_CameraPoint.y)
	//	{
	//if(g_CameraPoint_Smooth.y < abs(g_CameraPoint.y))
	//	}
	//}
	//m_pCamera.setTarget(getThisScene());


			//!< 이하 카메라가 맵 밖으로 못나가게 하는 구문

			
			//g_CameraPoint.x = //getPos().x;
			if(g_CameraPoint.x >= 0 + (D_TILE_WIDTH/2))
				g_CameraPoint.x = 0 + (D_TILE_WIDTH/2);
			else if(g_CameraPoint.x <= -(MapManager->getCurMap()->getMapWidth() * D_TILE_WIDTH)  + (D_PHONE_WIDTH) + (D_TILE_WIDTH/2))
				g_CameraPoint.x = -(MapManager->getCurMap()->getMapWidth() * D_TILE_WIDTH) + (D_PHONE_WIDTH) + (D_TILE_WIDTH/2);
			
			//g_CameraPoint.y = getPos().y;
			if(g_CameraPoint.y >= 0 - (D_TILE_HEIGHT/2))
				g_CameraPoint.y = 0 - (D_TILE_HEIGHT/2);
			else if(g_CameraPoint.y <= -(MapManager->getCurMap()->getMapHeight() * D_TILE_HEIGHT) + (D_PHONE_HEIGHT) - (D_TILE_HEIGHT/2))
				g_CameraPoint.y = -(MapManager->getCurMap()->getMapHeight() * D_TILE_HEIGHT)  + (D_PHONE_HEIGHT) - (D_TILE_HEIGHT/2);
			//else if(g_CameraPoint.y <= -(MapManager->getCurMap()->getMapHeight() * D_TILE_HEIGHT) + (D_PHONE_HEIGHT/2) + D_TILE_HEIGHT)
			//	g_CameraPoint.y = -(MapManager->getCurMap()->getMapHeight() * D_TILE_HEIGHT) + (D_PHONE_HEIGHT/2) + D_TILE_HEIGHT;




			
		g_CameraPoint_Smooth.x += (g_CameraPoint.x - g_CameraPoint_Smooth.x) * dt * D_TILE_SCALE;
		g_CameraPoint_Smooth.y += (g_CameraPoint.y - g_CameraPoint_Smooth.y) * dt * D_TILE_SCALE;
	
	//m_stTargetPos.x = 0.0000001f;
	//m_stTargetPos.y = 0.0f;
	//m_stTargetPos.z = m_pCamera.getCenter().z;

	//!< 삽질하였다;; 카메라이동이 아니라 기울기 조종이었음 (그리고 라디안 값을 사용하는지 매우 작은값만 가능)
	// m_pCamera.setEye(0,0.00000001,m_pCamera.getEye().z);
	//m_pCamera.setCenter(m_stTargetPos);
	
	CUnit::Update(dt);
	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].Update(dt);
	}
	//Run(180.0f, dt);


	
	for(int i=0; i<E_HERO_STATE_MAX; i++)
	{
		m_pAni[i].setVisible(false);
	}
	if(m_eState == E_HERO_STATE_RUN)
	{
		m_bHitTest[0] = false;
		m_bHitTest[1] = false;
		m_bHitTest[2] = false;
		m_bHitTest[3] = false;

		//stTemp1.x -= (D_TILE_WIDTH/2);
		//stTemp1.y -= (D_TILE_HEIGHT/2);

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

void CHero::ChangeState(E_HERO_STATE eState)
{
	m_eState = eState;
}

void CHero::Run(float fRotation)
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