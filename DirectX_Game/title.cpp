/******************************************************************
***
***		タイトル処理
***
***		title.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "baseScene.h"
#include "fade.h"
#include "title.h"
#include "scene.h"
#include "startButton.h"
#include "titleLogo.h"
#include "meshDome.h"
#include "meshField.h"
#include "game.h"
#include "particle.h"
#include "building.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CTitle::CTitle()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CTitle::~CTitle()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CTitle::Init(void)
{
	Create3D();
	Create2D();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CTitle::Uninit(void)
{
	//全オブジェクト破棄
	CScene::ReleaseAll();

	CParticleManager::ReleaseAll();
}

/******************************************************************
更新処理関数
*******************************************************************/
CBaseScene::SCENE_STATE CTitle::Update(void)
{
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_SPACE))
	{
		if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CFade::FADE_OUT);
		}
	}

	else if (CManager::GetFade()->GetFadeState() == CFade::FADE_MAX)
	{
		return CBaseScene::SCENE_GAME;
	}

	else
	{

	}

	CParticle::Create(D3DXVECTOR3((float)(rand() % 200), 10.0f, (float)(rand() % 200)));
	CParticle::Create(D3DXVECTOR3((float)(rand() % 200)*-1, 10.0f, (float)(rand() % 200)*-1));
	CParticle::Create(D3DXVECTOR3((float)(rand() % 200), 10.0f, (float)(rand() % 200)*-1));
	CParticle::Create(D3DXVECTOR3((float)(rand() % 200)*-1, 10.0f, (float)(rand() % 200)));

	return CBaseScene::SCENE_CONTINUE;
}

/******************************************************************
2Dオブジェクト生成処理関数
*******************************************************************/
void CTitle::Create2D(void)
{
	CTitleLogo::Create();

	CStartButton::Create();
}

/******************************************************************
3Dオブジェクト生成処理関数
*******************************************************************/
void CTitle::Create3D(void)
{
	//メッシュフィールドの生成
	CMeshField::Create();

	//メッシュドーム生成
	CMeshDome::Create();

	//CBuilding::Create();
}

