#pragma once
//


typedef enum _E_GAME_STEP
{
	E_GAME_STEP_READY,
	E_GAME_STEP_PLAY,
	E_GAME_STEP_END,
}E_GAME_STEP;


#define RadToDeg(x) (57.29577951f * x)
#define DegToRad(x) (0.017453293f * x)


#define D_HP_PAD 10

#define D_TILE_SCALE 1.0f
//
//#define D_SOUND_MAX 4
//
#define D_PHONE_WIDTH 1280
#define D_PHONE_HEIGHT 720
//
#define D_SCREEN_SCALE_WIDTH(s) ((D_PHONE_WIDTH/100) * s)
#define D_SCREEN_SCALE_HEIGHT(s) ((D_PHONE_HEIGHT/100) * s)


#define D_SOUNDMNG CocosDenshion::SimpleAudioEngine::getInstance()

#define D_HERO_WIDTH (60 * D_TILE_SCALE)
#define D_HERO_HEIGHT (60 * D_TILE_SCALE)

#define D_TILE_WIDTH (64 * D_TILE_SCALE)
#define D_TILE_HEIGHT (64 * D_TILE_SCALE)

#define D_TILE_ENTERING_SENS ((D_TILE_WIDTH) * (25/100))

#define D_HITCHECK_LEFT for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++) \
						{ \
							CCPoint stTemp1 = getPos(); \
							stTemp1.x = stTemp1.x - (getMoveSpeed() * (dt))  - 1; \
							stTemp1.y = stTemp1.y; \
							CCPoint stTemp2 = (*it)->getPos(); \
							stTemp2.x = stTemp2.x; \
							stTemp2.y = stTemp2.y; \
							newRECT rc1; \
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_LEFT] = true;\
								break;\
							};\
						}\
						for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)\
						{\
							if((*it2)->getIndex() == getIndex())\
							{\
								continue;\
							}\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x - (getMoveSpeed() * (dt))  - 1;\
							stTemp1.y = stTemp1.y;\
							CCPoint stTemp2 = (*it2)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_LEFT] = true;\
							}\
						}\
						if(m_bHitTest[E_DERECTION_LEFT] == false)\
							setPos( CCPoint( getPos().x - (getMoveSpeed() * dt) ,getPos().y) );\

#define D_HITCHECK_RIGHT 	for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)\
						{\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x + (getMoveSpeed() * (dt))  + 1;\
							stTemp1.y = stTemp1.y;\
							CCPoint stTemp2 = (*it)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_RIGHT] = true;\
								break;\
							}\
						}\
						for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)\
						{\
							if((*it2)->getIndex() == getIndex())\
							{\
								continue;\
							}\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x + (getMoveSpeed() * (dt))  + 1;\
							stTemp1.y = stTemp1.y;\
							CCPoint stTemp2 = (*it2)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_RIGHT] = true;\
							}\
						}\
						if(m_bHitTest[E_DERECTION_RIGHT] == false)\
							setPos( CCPoint(getPos().x + (getMoveSpeed() * dt) ,  getPos().y) );\


#define D_HITCHECK_UP 	for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)\
						{\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x;\
							stTemp1.y = stTemp1.y + (getMoveSpeed() * (dt))  + 1;\
							CCPoint stTemp2 = (*it)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_UP] = true;\
								break;\
							}\
						}\
						for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)\
						{\
							if((*it2)->getIndex() == getIndex())\
							{\
								continue;\
							}\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x;\
							stTemp1.y = stTemp1.y + (getMoveSpeed() * (dt))  + 1;\
							CCPoint stTemp2 = (*it2)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_UP] = true;\
							}\
						}\
						if(m_bHitTest[E_DERECTION_UP] == false)\
							setPos( CCPoint(getPos().x  ,  getPos().y + (getMoveSpeed() * dt) ) );\



#define D_HITCHECK_DOWN 	for(it = MapManager->getCurMap()->m_BlokingMap.begin(); it != MapManager->getCurMap()->m_BlokingMap.end(); it++)\
						{\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x;\
							stTemp1.y = stTemp1.y - (getMoveSpeed() * (dt))  + 1;\
							CCPoint stTemp2 = (*it)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_DOWN] = true;\
								break;\
							}\
						}\
						for(it2 = g_UnitList.begin(); it2 != g_UnitList.end(); it2++)\
						{\
							if((*it2)->getIndex() == getIndex())\
							{\
								continue;\
							}\
							CCPoint stTemp1 = getPos();\
							stTemp1.x = stTemp1.x ;\
							stTemp1.y = stTemp1.y - (getMoveSpeed() * (dt)) - 1;\
							CCPoint stTemp2 = (*it2)->getPos();\
							stTemp2.x = stTemp2.x;\
							stTemp2.y = stTemp2.y;\
							newRECT rc1;\
							rc1.left = stTemp1.x;\
							rc1.right = stTemp1.x + D_HERO_WIDTH;\
							rc1.top = stTemp1.y;\
							rc1.bottom = stTemp1.y - D_HERO_HEIGHT;\
							newRECT rc2;\
							rc2.left = stTemp2.x;\
							rc2.right = stTemp2.x + D_HERO_WIDTH;\
							rc2.top = stTemp2.y;\
							rc2.bottom = stTemp2.y - D_HERO_HEIGHT;\
							if(BHitTest::HitTest_Square(rc1,rc2) == true)\
							{\
								m_bHitTest[E_DERECTION_DOWN] = true;\
							}\
						}\
						if(m_bHitTest[E_DERECTION_DOWN] == false)\
							setPos( CCPoint(getPos().x  ,  getPos().y - (getMoveSpeed() * dt) ) );\

//!< Sensabilty //< 타일 빨려들어가는 감도 기본은 각 양쪽 25%로써 기본타일크기 x 25/100
//
//#define D_MENU_TITLE_X 240
//#define D_MENU_TITLE_Y 700
//
//#define D_BLOCK_WIDTH 64.0f
//#define D_BLOCK_HEIGHT 64.0f
//
//#define D_BLOCK_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT - 1))
//#define D_BLOCKMAP_MAX (D_BLOCKMAP_WIDTH * (D_BLOCKMAP_HEIGHT))
//
//#define D_BLOCK_SPEED 650.0f
//#define D_BLOCK_PLUSSPEED 120.0f
//
//#define	D_LINE_START_X 48.0f
//#define	D_LINE_START_Y 760.0f
////!< DevOption 696.0f 734.0f
//#define D_BLOCK_BOUNCE_FOWER 90.0f
//#define D_BLOCK_BOUNCE_FOWER_LOW 35.5f
//#define D_BLOCK_BOUNCE_HURISTIC 1.4f
//
//#define D_POP_LOOP 0
//
//#define D_BLOCKMAP_WIDTH 7
//#define D_BLOCKMAP_HEIGHT 12
//

////#define	D_LINE_START_X -192.0f
////#define	D_LINE_START_Y 340.0f
//
//#define D_SCORE_POP 10
//#define D_SCORE_POP_PLUS 10 //!< 5이상 터트리면 + 100 * 갯수
//#define D_SCORE_POP_COMBO 0.2f //!< 콤보 추가 기본 배수
//#define D_SCORE_POP_LIGHTNING 10 //!< 아이템 전기로 터트린 점수
//#define D_SCORE_POP_BOMB 10 //!< 아이템 폭탄으로 터트린 점수
//#define D_SCORE_LINE 40
//
//#define D_CAM_Z_FIXED 695.0f
//
//#define D_PHOTOSHOP_Y(value) (D_PHONE_HEIGHT - value)
//
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);
//
////#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);
//
////m_pLoading->setVisible(true); \
//	
//
//
//#define D_SCENE_CHANGE_EFFECT_UP(scene) CCScene *pScene = CCTransitionFadeUp::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//#define D_SCENE_CHANGE_EFFECT_DOWN(scene) CCScene *pScene = CCTransitionFadeDown::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//#define D_SCENE_CHANGE_EFFECT_FADE(scene) CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,scene); //m_pLoading->setVisible(true);
//
//
//
#define D_BASIC_PHONE_WIDTH 800
#define D_BASIC_PHONE_HEIGHT 480
//
#define D_SCALE_WIDTH (g_PhoneSize.width/D_BASIC_PHONE_WIDTH)
#define D_SCALE_HEIGHT (g_PhoneSize.height/D_BASIC_PHONE_HEIGHT)
//
//#define D_POPTIME_MAX 1.0f
//
//
//#define D_STAGEMENU_START_X - 150.0f
//#define D_STAGEMENU_START_Y   300.0f
//
//#define D_STAGEMENU_DISTANCE 150.0f
//#define D_STAGEMENU_WIDTH_NUMBER 3
//
//#define D_STAGEMENU_WIDTH 140
//#define D_STAGEMENU_HEGIHT 140
//
//#define D_STAGE_MAX 33
//
//#define D_BUTTON_SOUND "StageStart.mp3"