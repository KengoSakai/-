/******************************************************************
***
***		ゲーム処理
***
***		game.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "game.h"
#include "scene.h"
#include "miniMapPlayer.h"
#include "meshField.h"
#include "meshDome.h"
#include "particle.h"

#include "player.h"
#include "enemyModel.h"
#include "goalModel.h"
#include "gaugeBox.h"
#include "gaugeMeter.h"
#include "modelManager.h"
#include "miniMap.h"
#include "building.h"
#include "time.h"
#include "item.h"
#include "pause.h"
#include "cloud.h"
#include "target.h"
#include "score.h"

CScore *CGame::pScore = NULL;
/******************************************************************
コンストラクタ
*******************************************************************/
CGame::CGame()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CGame::~CGame()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CGame::Init(void)
{
	//3Dオブジェクト生成
	Create3D();

	//2Dオブジェクト生成
	Create2D();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CGame::Uninit(void)
{
	//全オブジェクト破棄
	CScene::ReleaseAll();

	CParticleManager::ReleaseAll();
}

/******************************************************************
更新処理関数
*******************************************************************/
CBaseScene::SCENE_STATE CGame::Update(void)
{
	//時間切れなら
	if (pTime->GetTime() < 0 )
	{
		//フェードしていないなら
		if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
		{
			//フェードアウトを設定
			CManager::GetFade()->SetFade(CFade::FADE_OUT);
		}

		//フェードアウトが終了したら
		else if (CManager::GetFade()->GetFadeState() == CFade::FADE_MAX)
		{
			//次のシーンへ
			return CBaseScene::SCENE_RESULT;
		}

		//例外処理
		else
		{

		}
	}

	else
	{
		//１秒毎にオブジェクトを生成
		if (pTime->GetTime()%60==0)
		{
			/*CItem::Create(D3DXVECTOR3((float)(rand() % 200), 10.0f, (float)(rand() % 200)));
			CItem::Create(D3DXVECTOR3((float)(rand() % 200)*-1, 10.0f, (float)(rand() % 200)*-1));
			CItem::Create(D3DXVECTOR3((float)(rand() % 200), 10.0f, (float)(rand() % 200)*-1));
			CItem::Create(D3DXVECTOR3((float)(rand() % 200)*-1, 10.0f, (float)(rand() % 200)));*/
			CTarget::Create();
		}

		//ポーズボタンが入力されたら
		/*if ()
		{
			//ポーズ画面を表示

		}
*/
	}
	return CBaseScene::SCENE_CONTINUE;
}

/******************************************************************
2Dオブジェクト生成処理関数
*******************************************************************/
void CGame::Create2D(void)
{
	CMiniMap::Create();

	CMiniMapPlayer::Create();

	pScore = CScore::Create(CScene::OBJTYPE_SCORE);

	pTime = CTime::Create();
}

/******************************************************************
3Dオブジェクト生成処理関数
*******************************************************************/
void CGame::Create3D(void)
{
	//メッシュフィールドの生成
	CMeshField::Create();

	//メッシュドーム生成
	CMeshDome::Create();

	//プレイヤーの生成
	CPlayer::Create();

	//CGoalModel::Create();

	CEnemyModel::Create();

	CBuilding::Create();

	for (int Count = 0; Count < 200; Count++)
	{
		//CCloud::Create();
	}
}
