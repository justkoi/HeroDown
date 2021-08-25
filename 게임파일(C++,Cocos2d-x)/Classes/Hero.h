#pragma once

#include "stdafx.h"

typedef enum _e_hero_state
{
	E_HERO_STATE_NONE,
	E_HERO_STATE_RUN,
	E_HERO_STATE_MAX

}E_HERO_STATE;


class CHero : public CUnit
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

public:
	//!< 초기화 함수
	virtual void Init(CCLayer* pThisScene, float fMoveSpeed, int nLayer, CCPoint stPos);
	//!< 업데이트 함수
	virtual void Update(float dt, CMapManager* MapManager);
	// virtual void Exit();

public:
	void ChangeState(E_HERO_STATE eState);

public:
	//!< 달리게 하는 함수 (어느 방향으로 달릴건지) [상태변경 Run]
	void Run(float fRotation);
	//!< 멈춤, 명령 즉시 [상태변경 None]
	void Stop();
};