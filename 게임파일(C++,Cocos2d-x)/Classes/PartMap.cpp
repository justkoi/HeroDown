#include "stdafx.h"

void CPartMap::Init(CCLayer* pThisScene,int nIndex)
{
	
	char sWidth[256];
	char sHeight[256];

	char sTemp[256];
	

	ssize_t nfp1 = 0;
	ssize_t nfp2 = 0;
	ssize_t nfp3 = 0;

	int i=0;


	char strFilePath[256];
	

	m_pThisScene = pThisScene;
	m_nIndex = nIndex;

	m_nLayer = 0;

	string strTemp;

	
	//string strTemp = CCFileUtils::getInstance()->getWritablePath();
	//int t = 0;


	sprintf(strFilePath,"Map_Max_%d.txt", nIndex);
	strTemp = strFilePath;
	unsigned char* fp1 = CCFileUtils::getInstance()->getFileData(strFilePath,"r", &(nfp1));
	//FILE* fp1 = fopen(CCFileUtils::getInstance()->fullPathForFilename(strTemp).c_str(),"rt");
	
	sprintf(strFilePath,"Map_Tile_%d.txt",nIndex);
	strTemp = strFilePath;
	unsigned char* fp2 = CCFileUtils::getInstance()->getFileData(strFilePath,"r", &(nfp2));
	//FILE* fp2 = fopen(CCFileUtils::getInstance()->fullPathForFilename(strTemp).c_str(),"rt");

	sprintf(strFilePath,"Map_Bloking_%d.txt",nIndex);
	strTemp = strFilePath;
	unsigned char* fp3 = CCFileUtils::getInstance()->getFileData(strFilePath,"r", &(nfp3));
	//FILE* fp3 = fopen(CCFileUtils::getInstance()->fullPathForFilename(strTemp).c_str(),"rt");

	/*
	sprintf(strFilePath,"Data/Map/Map_Portal_%d.txt",nIndex);
	FILE* fp4 = fopen(strFilePath,"rt");
	sprintf(strFilePath,"Data/Map/Map_NPC_%d.txt",nIndex);
	FILE* fp5 = fopen(strFilePath,"rt");
	*/
	//int j=0;
/*
	while(1)
	{
		fp1++;
		int fR1 = (int)fp1;
		int fR2 = (int)(*fp1);
		j++;
		if((int)(*fp1) >= 129)
		{
			break;
		}
	}
	i=0;*/
	while(1)
	{
		sWidth[i] = (*fp1);
		fp1++;
		i++;
		if((*fp1) == ' ')
		{
			fp1++;
			break;
		}
	}

	
	i=0;
	while(1)
	{
		sHeight[i] = (*fp1);
		fp1++;
		i++;
		if((*fp1) == ' ')
		{
			fp1++;
			break;
		}
	}

	m_nWidth = atoi(sWidth);
	m_nHeight = atoi(sHeight);

	//fscanf(fp1,"%d %d",&m_nWidth,&m_nHeight);
	
	m_aTileMap = new stTileMap*[m_nHeight];
	for(int i=0; i<m_nHeight; i++)
	{
		m_aTileMap[i] = new stTileMap[m_nWidth];
	}

	for(int i=0; i<m_nHeight; i++)
	{
		for(int j=0; j<m_nWidth; j++)
		{
			//m_aTileMap[i][j].m_nTileMap = fgetc(fp2) - '0';
			sTemp[0] = (*fp2);
			m_aTileMap[i][j].m_nTileMap = atoi(sTemp); fp2++;

			switch(m_aTileMap[i][j].m_nTileMap)
			{
				case 1:
					m_aTileMap[i][j].m_pTileMap = CCSprite::create("Tile_1.png");
					m_aTileMap[i][j].m_pTileMap->setPosition(0.0f + (float)(D_TILE_WIDTH * j),  (D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i));
					m_aTileMap[i][j].m_pTileMap->setScale(D_TILE_SCALE);
					//m_aTileMap[i][j].m_pTileMap->setAnchorPoint(CCPoint(0.0f,0.0f));
					m_pThisScene->addChild(m_aTileMap[i][j].m_pTileMap, m_nLayer);
				break;
				case 2:
					m_aTileMap[i][j].m_pTileMap = CCSprite::create("Tile_2.png");
					m_aTileMap[i][j].m_pTileMap->setPosition(0.0f + (float)(D_TILE_WIDTH * j), (D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i));
					m_aTileMap[i][j].m_pTileMap->setScale(D_TILE_SCALE);
					//m_aTileMap[i][j].m_pTileMap->setAnchorPoint(CCPoint(0.0f,0.0f));
					m_pThisScene->addChild(m_aTileMap[i][j].m_pTileMap, m_nLayer);
					//m_aTileMap[i][j].m_pTileMap = new CEMPlane();
					//m_aTileMap[i][j].m_pTileMap->SetTexture(pThisScene, "Data/Image/Map/Tile/Tile_2.png",GL_REPEAT,GL_LINEAR,true);
					//m_aTileMap[i][j].m_pTileMap->SetSize(1.00f,1.00f);
					//m_aTileMap[i][j].m_pTileMap->SetPos(0.0f + (double)(D_TILE_WIDTH * j), 0.0f - (double)(D_TILE_HEIGHT * i));
					//m_aTileMap[i][j].m_pTileMap->SetBlend(true);
					////m_aTileMap[i][j].m_pTileMap->SetOrtho2D(true);
					////!<m_aTileMap[i][j].m_pTileMap->SetColor(1.0f,0.0f,0.0f,D_TILE_ALPHA);
					////m_aTileMap[i][j].m_pTileMap->SetFrustumShow(false);
					////m_aTileMap[i][j].m_pTileMap->SetBackFaceCulling(false);
					//m_aTileMap[i][j].m_pTileMap->SetFrustumCulling(true);
					//pThisScene->Commit(100,(i*m_nWidth)+j,"Tile", m_aTileMap[i][j].m_pTileMap);
				break;
			}
		}
		fp2++;
		fp2++; //fgetc(fp2);
	}
	for(int i=0; i<m_nHeight; i++)
	{
		for(int j=0; j<m_nWidth; j++)
		{
			
			sTemp[0] = (*fp3);
			m_aTileMap[i][j].m_nTileMap = atoi(sTemp); fp3++;//fgetc(fp3) - '0';
			if(m_aTileMap[i][j].m_nTileMap == 1)
			{
				CBlokingBlock* nTemp = new CBlokingBlock(CCPoint(0.0f + (float)(D_TILE_WIDTH * j),  (D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i)));// (float)(D_TILE_WIDTH * j), (D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i)
				nTemp->m_stIndex.x = j;
				nTemp->m_stIndex.y = i;
				m_BlokingMap.push_back(nTemp);
			}
		}
		fp3++;
		fp3++;//fgetc(fp3);
	}
	//
	//while(feof(fp4) == 0)
	//{
	//	stEMVec2 stTempPos;
	//	stEMVec2 stTempHeroPos;
	//	int		nNextMapIndex = -1;
	//	fscanf(fp4,"%f %f %d %f %f",&stTempPos.m_fX,&stTempPos.m_fY,&nNextMapIndex,&stTempHeroPos.m_fX,&stTempHeroPos.m_fY);
	//	
	//	if( nNextMapIndex != -1)
	//	{
	//		CPortal* pPortal = new CPortal(stTempPos,nNextMapIndex,stTempHeroPos);
	//		pPortal->Init(m_pThisScene);
	//		m_PortalMap.push_back(pPortal);
	//	}
	//}

	//while(feof(fp5) == 0)
	//{
	//	stEMVec2 stTempPos;
	//	int nIndex;
	//	fscanf(fp5,"%d %f %f",&nIndex, &stTempPos.m_fX,&stTempPos.m_fY);
	//	char strTemp[256];
	//	sprintf(strTemp,"Data/Image/NPC/%d.png",nIndex);
	//	CNPC* pNPC = new CNPC();
	//	pNPC->Init(pThisScene,nIndex,"NPC",strTemp,-2,stTempPos);
	//	//pNPC->m_pPlane->SetSize(0.35f,0.35f);
	//	pNPC->getPlane()->SetSize(0.25f,0.25f);
	//	m_NPCMap.push_back(pNPC);
	//}


	/*CTargetHero->setPos(stEMVec2(0.0f + (double)(D_TILE_WIDTH * j), 0.0f - (double)(D_TILE_HEIGHT * i))); 
	g_stCamPos_Stage.m_fX = CTargetHero->getPos().m_fX;
	if(g_stCamPos_Stage.m_fX <= D_SCREEN_WIDTH/2)
		g_stCamPos_Stage.m_fX = D_SCREEN_WIDTH/2;
	else if(g_stCamPos_Stage.m_fX >= (getMapWidth() * D_TILE_WIDTH) - (D_SCREEN_WIDTH/2) - D_TILE_WIDTH)
		g_stCamPos_Stage.m_fX = (getMapWidth() * D_TILE_WIDTH) - (D_SCREEN_WIDTH/2) - D_TILE_WIDTH;

	g_stCamPos_Stage.m_fY = CTargetHero->getPos().m_fY;
	if(g_stCamPos_Stage.m_fY >= -(D_SCREEN_HEIGHT/2))
		g_stCamPos_Stage.m_fY = -(D_SCREEN_HEIGHT/2);
	else if(g_stCamPos_Stage.m_fY <= -(getMapHeight() * D_TILE_HEIGHT) + (D_SCREEN_HEIGHT/2) + D_TILE_WIDTH)
		g_stCamPos_Stage.m_fY = -(getMapHeight() * D_TILE_HEIGHT) + (D_SCREEN_HEIGHT/2) + D_TILE_WIDTH;


	g_stSmoothCamPos_Stage = g_stCamPos_Stage;
	*/
	//fclose(fp1);
	//fclose(fp2);
	//fclose(fp3);
	/*fclose(fp4);
	fclose(fp5);*/

	if(m_nIndex == 3)
	{
		//D_SOUNDMNG->Play("BGM_2",false,0.55f);
	}

	/*if(m_nIndex == 1)
	{
		CObject* pObject = new CObject();
		pObject->Init(m_pThisScene,stEMVec2(50.0f,-450.0f),0,1);
		m_ObjectList.push_back(pObject);
		
		CObject* pObject2 = new CObject();
		pObject2->Init(m_pThisScene,stEMVec2(150.0f,-450.0f),0,1);
		m_ObjectList.push_back(pObject2);


		CObject* pObject3 = new CObject();
		pObject3->Init(m_pThisScene,stEMVec2(150.0f,-600.0f),1,1);
		m_ObjectList.push_back(pObject3);
		
		CObject* pObject4 = new CObject();
		pObject4->Init(m_pThisScene,stEMVec2(350.0f,-580.0f),2,1);
		m_ObjectList.push_back(pObject4);

	}
	if(m_nIndex == 3)
	{
		CObject* pObject9 = new CObject();
		pObject9->Init(m_pThisScene,stEMVec2(550.0f,-500.0f),3,1);
		m_ObjectList.push_back(pObject9);
	}*/
		
	/*if(m_nIndex == 2 && g_nQuestLevel == 3)
	{
		g_nEventLevel = 0;
		g_CChatWindow.ChatStart(-1);
	}*/

}

void CPartMap::Update(float dt)
{

	for(int i=0; i<m_nHeight; i++)
	{
		for(int j=0; j<m_nWidth; j++)
		{
			m_aTileMap[i][j].m_pTileMap->setPosition( g_CameraPoint_Smooth.x + 0.0f + (float)(D_TILE_WIDTH * j),  g_CameraPoint_Smooth.y +  (D_TILE_HEIGHT * m_nHeight) - (float)(D_TILE_HEIGHT * i));
		}
	}
	/*if(m_nIndex == 3 && g_nQuestLevel == 4)
	{
		if(g_CHero.getPos().m_fX >= 400.0f)
		{
			g_nQuestLevel++;
			g_nEventLevel = 0;
			g_CChatWindow.ChatStart(-1);
		}
	}*/
}
void CPartMap::Exit()
{

	//!< Cocos2d-x 에서는 메모리 관리를 엔진에서 하기 때문에 해제하지 않음


	//D_SOUNDMNG->Play("Portal",false,1.5f);
	if(m_nIndex == 2)
	{
		//D_SOUNDMNG->Stop("BGM_1");
	}
	else if(m_nIndex == 3)
	{
		//D_SOUNDMNG->Stop("BGM_2");
	}
	//for(int i=0; i<m_nHeight; i++)
	//{
	//	for(int j=0; j<m_nWidth; j++)
	//	{
	//		//m_pThisScene->DeletePlane(m_aTileMap[i][j].m_pTileMap);
	//		//delete m_aTileMap[i][j].m_pTileMap;
	//	}
	//}
	for(int i=0; i<m_nHeight; i++)
		delete [] m_aTileMap[i];
    delete [] m_aTileMap;

	//list<CBlokingBlock*>::iterator it;
	//for(it = m_BlokingMap.begin(); it != m_BlokingMap.end(); it++)
	//{
	//	delete (*it);
	//}
	//m_BlokingMap.clear();

	//list<CPortal*>::iterator itr;
	//for(itr = m_PortalMap.begin(); itr != m_PortalMap.end(); itr++)
	//{
	//	m_pThisScene->DeleteAnimation((*itr)->m_pPlane);
	//	delete (*itr);
	//	//!< 윗줄에서 삭제 delete (*itr);
	//}
	//m_PortalMap.clear();

	//
	//list<CNPC*>::iterator itr2;
	//for(itr2 = m_NPCMap.begin(); itr2 != m_NPCMap.end(); itr2++)
	//{
	//	m_pThisScene->DeletePlane((*itr2)->getPlane());
	//	delete (*itr2);
	//	//!< 윗줄에서 삭제 delete (*itr);
	//}
	//m_NPCMap.clear();

	//list<CObject*>::iterator itr3;
	//for(itr3 = m_ObjectList.begin(); itr3 != m_ObjectList.end(); itr3++)
	//{
	//	m_pThisScene->DeletePlane((*itr3)->m_pPlane);
	//	delete (*itr3);
	//	//!< 윗줄에서 삭제 delete (*itr);
	//}
	//m_ObjectList.clear();
}

int CPartMap::getMapWidth()
{
	return m_nWidth;
}
int CPartMap::getMapHeight()
{
	return m_nHeight;
}

int CPartMap::getIndex()
{
	return m_nIndex;
}