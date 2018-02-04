#include "manager.h"
#include "sceneManager.h"
#include "title.h"
#include "game.h"
#include "result.h"

/******************************************************************
コンストラクタ
*******************************************************************/
CSceneManager::CSceneManager()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CSceneManager::Initialize(void)
{
	pBaseScene = new CGame;
	pBaseScene->Init();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CSceneManager::Uninitalize(void)
{
	//シーンの破棄
	if (pBaseScene != NULL)
	{
		pBaseScene->Uninit();
		delete pBaseScene;
		pBaseScene = NULL;
	}
}

/******************************************************************
更新処理関数
*******************************************************************/
void CSceneManager::Update(void)
{
	//現在のシーンの状態を取得
	pBaseScene->SceneState = pBaseScene->Update();

	//フェードアウトが終わったら
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_MAX)
	{
		//次のシーンがタイトルなら
		if (pBaseScene->SceneState == CBaseScene::SCENE_TITLE)
		{
			Uninitalize();
			pBaseScene->SetMode(pBaseScene = new CTitle);
			return;
		}

		//次のシーンがゲームなら
		else if (pBaseScene->SceneState == CBaseScene::SCENE_GAME)
		{
			Uninitalize();
			pBaseScene->SetMode(pBaseScene = new CGame);
			return;
		}

		//次のシーンがリザルトなら
		else if (pBaseScene->SceneState == CBaseScene::SCENE_RESULT)
		{
			Uninitalize();
			pBaseScene->SetMode(pBaseScene = new CResult);
			return;
		}

		//例外処理
		else
		{

		}
	} 
}
