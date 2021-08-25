#pragma once
#include "stdafx.h"

//class CBlokingBlock;
//class CPortal;
//class CObject;

typedef struct
{
	int m_nTileMap;
	CCSprite* m_pTileMap;
}stTileMap;
//
//class CHero;
//class CNPC;
class CPartMap
{
private:
	int m_nIndex; //!< 맵 번호
	int m_nWidth;
	int m_nHeight;

	int m_nLayer;
	
	stTileMap** m_aTileMap; //!< 타일맵 2차원배열 동적할당.
public:
	CCLayer* m_pThisScene;
	vector<CBlokingBlock*> m_BlokingMap; //!< 블로킹 블록 보관

	//vector<CPortal*>		m_PortalMap; //!< 포탈 보관
	//list<CNPC*>		m_NPCMap; //!< NPC 보관
	//list<CObject*> m_ObjectList; //!< Object 보관

	int getMapWidth();
	int getMapHeight();

	int getIndex();

public:
	void Init(CCLayer* pThisScene, int nIndex); //!< 타일맵을 읽어들입니다.
	void Update(float dt); //!< 할거없는듯.
	void Exit(); //!< 동적메모리해제

public:

};