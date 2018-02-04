/******************************************************************
***
***		ミニマッププレイヤー処理
***
***		miniMapPlayer.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "miniMapPlayer.h"
#include "player.h"
#include "miniMap.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CMiniMapPlayer::CMiniMapPlayer()
{

}

/******************************************************************
初期化処理
*******************************************************************/
void CMiniMapPlayer::Initialize(void)
{
	//オブジェクト数繰り返す
	for (int nCntScene = 0; nCntScene < 100; nCntScene++)
	{
		//オブジェクトの情報取得
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		//オブジェクトのポインターがNULLでないなら
		if (pScene != NULL)
		{
			//オブジェクトの型を取得
			CScene::OBJTYPE ObjType;
			ObjType = pScene->GetObjType();

			if (ObjType == CScene::OBJTYPE_MINIMAP)
			{
				//オブジェクトポインタ
				CMiniMap *pMiniMap = (CMiniMap*)pScene;
				Position.x = (pMiniMap->GetPosition().x + pMiniMap->GetWidthHeight().x*0.5f);
				Position.y = (pMiniMap->GetPosition().y + pMiniMap->GetWidthHeight().y*0.5f);
				Position.z = 0.0f;
			}
		}
	}
	WidthHeight = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	CScene2D::Initialize();
}

/******************************************************************
終了処理
*******************************************************************/
void CMiniMapPlayer::Uninitalize(void)
{
	CScene2D::Uninitialize();
}

/******************************************************************
更新処理
*******************************************************************/
void CMiniMapPlayer::Update(void)
{
	//オブジェクト数繰り返す
	for (int nCntScene = 0; nCntScene < 100; nCntScene++)
	{
		//オブジェクトの情報取得
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		//オブジェクトのポインターがNULLでないなら
		if (pScene != NULL)
		{
			//オブジェクトの型を取得
			CScene::OBJTYPE ObjType;
			ObjType = pScene->GetObjType();

			//指定したオブジェクトなら
			if (ObjType == CScene::OBJTYPE_PLAYER)
			{
				//オブジェクトポインタ
				CPlayer *pPlayer = (CPlayer*)pScene;

				//プレイヤーの座標取得
				Position.z = 0.0f;
			//	Position.x = pPlayer->GetPosition().x;
				//Position.y = -pPlayer->GetPosition().z;
			}
		}
	}
	Position.x++;
}

/******************************************************************
描画処理
*******************************************************************/
void CMiniMapPlayer::Draw(void)
{
	CScene2D::Draw();
}

/******************************************************************
オブジェクト生成処理
*******************************************************************/
CMiniMapPlayer *CMiniMapPlayer::Create(void)
{
	CMiniMapPlayer * pMiniMapPlayer;
	pMiniMapPlayer = new CMiniMapPlayer;
	pMiniMapPlayer->Initialize();
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_MINIMAPPLAYER);
	pMiniMapPlayer->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_MINIMAPPLAYER));
	pMiniMapPlayer->SetObjType(OBJTYPE_MINIMAPPLAYER);
	
	return pMiniMapPlayer;
}


