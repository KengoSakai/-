/******************************************************************
***
***		プレイヤー処理
***
***		player.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "item.h"
#include "input.h"
#include "particle.h"
#include "score.h"

/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_GRAVITY (4.9f)	//重力

/******************************************************************
コンストラクタ
*******************************************************************/
CItem::CItem()
{
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_ITEM);
}

/******************************************************************
デストラクタ
*******************************************************************/
CItem::~CItem()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CItem::Initialize(D3DXVECTOR3 OrderPosition)
{
	//モデルの初期化
	CModel::Initialize();

	//初期のステータス
	Position = OrderPosition;	//座標
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//拡大率
}

/******************************************************************
終了処理関数
*******************************************************************/
void CItem::Uninitialize(void)
{
	CModel::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CItem::Update(void)
{

}

/******************************************************************
描画処理関数
*******************************************************************/
void CItem::Draw(void)
{
	//行列を設定
	SetMatrix();

	CModel::Draw();
}

/******************************************************************
オブジェクト作成関数
*******************************************************************/
CItem *CItem::Create(D3DXVECTOR3 OrderPosition)
{
	//オブジェクトポインタ
	CItem *pItem;

	//インスタンスの生成
	pItem = new CItem;

	//初期化処理
	pItem->Initialize(OrderPosition);

	//オブジェクトの型登録関数呼び出し
	pItem->SetObjType(OBJTYPE_ITEM);

	//バッファ情報を送る
	pItem->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_ITEM));

	//要素数を送る
	pItem->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_ITEM));

	//メッシュ情報を送る
	pItem->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_ITEM));

	pItem->BindTexture(NULL);

	return pItem;
}


/******************************************************************
位置情報取得関数
*******************************************************************/
D3DXVECTOR3 CItem::GetPosition(void)
{
	return Position;
}

void CItem::Hit(OBJTYPE Type)
{
	for (int a = 0; a < 20; a++)
	{
		CParticle::Create(Position);
	}

	if (Type == OBJTYPE_PLAYER)
	{
		//スコアの加算
	//	CGame::GetScore()->AddScore(10);
	}

	else if (Type == OBJTYPE_ENEMY)
	{
	//	CGame::GetOtherPlayerScore()->AddScore(10);
	}

	else
	{

	}
	//アイテムの破棄
	Uninitialize();
}
