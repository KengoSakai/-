/******************************************************************
***
***		弾処理
***
***		bulet.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "player.h"
#include "collision.h"
#include "fire.h"
#include "enemyModel.h"
#include "target.h"
#include "exprode.h"
/******************************************************************
定数定義
*******************************************************************/
#define FADE_RATE (0.8f)
#define SIZE (5.0f)
#define SPEED (1.0f)

CRenderer *CBullet::m_pRenderer = NULL;
/******************************************************************
コンストラクタ
*******************************************************************/
CBullet::CBullet()
{
	State = SHOT;
}

/******************************************************************
初期化処理関数
*******************************************************************/
void CBullet::Initialize(D3DXVECTOR3 OrderPosition, D3DXVECTOR3 OrderVector)
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Size = SIZE;
	CScene3D::Initialize();
	Position = OrderPosition;
	Rotate.x = OrderVector.x;
	Rotate.z = OrderVector.z;
	Rotate.y = 0.0f;
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Color = D3DXCOLOR(255.0f, 125.0f, 5.0f, 255.0f);
}

/******************************************************************
終了処理関数
*******************************************************************/
void CBullet::Uninitialize()
{
	CScene3D::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CBullet::Update(void)
{
	Position += Rotate * SPEED;

	Color.a -= 1.0f;

	//エフェクト生成
	CFire::Create(Position);

	HitObject();

	if (Color.a < 0.0f)
	{
		Uninitialize();
	}
}

/******************************************************************
描画処理関数
*******************************************************************/
void CBullet::Draw(void)
{

}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CBullet *CBullet::Create(D3DXVECTOR3 OrderPosition, D3DXVECTOR3 OrderVector)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Initialize(OrderPosition, OrderVector);
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_PARTICLE);
	pBullet->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_PARTICLE));
	pBullet->SetObjType(OBJTYPE_BULLET);
	return pBullet;
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
void CBullet::HitObject(void)
{
	//オブジェクト数繰り返す
	for (int nCntScene = 0; nCntScene < NUM_OBJECT; nCntScene++)
	{
		//オブジェクトの情報取得
		CScene *pScene = CScene::GetScene(nCntScene);

		//オブジェクトのポインターがNULLでないなら
		if (pScene != NULL)
		{
			//オブジェクトの型を取得
			CScene::OBJTYPE ObjType = pScene->GetObjType();

			//敵に当たったら
			if (ObjType == CScene::OBJTYPE_ENEMY)
			{
				//オブジェクトポインタ
				CEnemyModel *pEnemy = (CEnemyModel*)pScene;

				//球の当たり判定
				if (CCollision::SphereCollision(Position, pEnemy->GetPosition()))
				{
					pEnemy->HitObject();
					CExprode::Create(Position);
					State = HIT;
					continue;
				}
			}

			//ターゲットに当たったら
			else if (ObjType == CScene::OBJTYPE_TARGET)
			{
				//オブジェクトポインタ
				CTarget *pTarget = (CTarget*)pScene;

				//球の当たり判定
				if (CCollision::SphereCollision(Position, pTarget->GetPosition()))
				{
					pTarget->HitObject(OBJTYPE_PLAYER);
					for (int count = 0; count < NUM_EXPRODE; count++)
					{
						CExprode::Create(Position);
					}
					State = HIT;
					continue;
				}
			}
			else
			{

			}
		}
	}

	//何かオブジェクトに当たった
	if (State == HIT)
	{
		Uninitialize();
	}
}