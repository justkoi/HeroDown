#pragma once

#include "stdafx.h"

typedef struct _sthPos
{
	int nX;
	int nY;
	int f;
	_sthPos(int x, int y)
	{
		nX = x;
		nY = y;
		f = 0;
	}
}stHPos;

class CArcher : public CUnit
{
private:
	//!< 히어로 애니메이션
	BAnimation m_pAni[E_HERO_STATE_MAX];

	//!< 레이어
	int m_nLayer;


	//!< 상태
	E_HERO_STATE m_eState;

	float m_fRotation;
	float m_fRecentDt;

	//Camera m_pCamera;

	bool m_bHitTest[E_DERECTION_MAX];

	kmVec3 m_stTargetPos;

	float m_fSearchTimer;
	float m_fSearchTime;

	CCPoint m_stTargetCommandPoint;
	//!< 주위로 왔는가 판정하는 지역 해당 점으로 부터 각 사각형까지의 반지름 거리
	float m_fJudgmentArea;
	//!< 주변 해당 범위안에 히어로가 없을경우 SearchPath시작
	int m_nAroundArea;

	int m_nNowPath;

public:
	//!< A*관련 내부변수
	
	int nClose;
	vector<stHPos*> m_OpenList;
	vector<stHPos*> m_NewOpenList;
	vector<stHPos*> m_PathList;

	int** m_PathMap; //!< 타일맵 2차원배열 동적할당.
	int** m_Huristic;

public:
	//!< 초기화 함수
	virtual void Init(CCLayer* pThisScene, float fMoveSpeed, int nLayer, CCPoint stPos);
	//!< 업데이트 함수
	virtual void Update(float dt, CMapManager* MapManager);
	// virtual void Exit();

public:
	void ChangeState(E_HERO_STATE eState);

public:
	//!< A* 알고리즘 관련 내부함수
	void SetHuristic(stHPos* sPos, stHPos ePos);
	void Start(stHPos sPos);
	void ListCounting();
	void NextStep();
	bool Ended();
	void AddPath(stHPos sPos, int minh);

public:
	//!< 명령(Command) 함수

	//!< 달리게 하는 함수 (어느 방향으로 달릴건지) [상태변경 Run]
	void Run(float fRotation);
	//!< 멈춤, 명령 즉시 [상태변경 None]
	void Stop();
	//!< 길찾기 알고리즘 시작
	void SearchPath();
	//!< 특정지점까지 이동명령
	void Command_Move(CCPoint stPos);
	//!< 무조건 멈춤 명령
	void Command_Stop();


};