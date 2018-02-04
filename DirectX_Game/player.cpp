/******************************************************************
***
***		処理
***
***		.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "camera.h"
#include "player.h"
#include "particle.h"
#include "DebugFont.h"
#include "gaugeBox.h"
#include "gaugeMeter.h"
#include "score.h"
#include "collision.h"
#include "cubeCollider.h"
#include "physics.h"
#include "item.h"
#include "bullet.h"
#include "startPosition.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_PARTS (10)
/******************************************************************
構造体またはクラス定義
*******************************************************************/

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CPlayer::CPlayer()
{
	CGauge::Create();
	pGauge = CGaugeMeter::Create(300.0f);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_PLAYER);
	//	CCubeCollider::Create();
}

/******************************************************************
初期化処理関数
*******************************************************************/
void CPlayer::Initialize(void)
{
	Position = CStartPosition::SetPosition();
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Speed = 0.0f;
	State = WALK;
	Vector = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/******************************************************************
終了処理関数
*******************************************************************/
void CPlayer::Uninitialize(void)
{
	CModel::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CPlayer::Update(void)
{
	CameraVector = CManager::GetCamera()->GetPosView();
	CameraVector.y = 0.0f;
	Vector = Position - CameraVector;
	D3DXVec3Normalize(&Vector, &Vector);
	
	//移動処理
	Move();
	
	//オブジェクト当たり判定処理
	HitObject();

	//待機状態の場合
	Speed *= 0.96f;
	
	//移動状態の場合
	if (State == WALK && Speed < 3.0f)
	{
		Speed += 0.1f;
	}
}

/******************************************************************
描画処理関数
*******************************************************************/
void CPlayer::Draw(void)
{
	CModel::SetMatrix();
	CModel::Draw();

#ifdef _DEBUG
	CManager::GetDebugFont()->AddDebugFont("Player:Position.x", Position.x, 0, 0);
	CManager::GetDebugFont()->AddDebugFont("Player:Position.y", Position.y, 0, 20);
	CManager::GetDebugFont()->AddDebugFont("Player:Position.z", Position.z, 0, 40);
	CManager::GetDebugFont()->AddDebugFont("Player:Speed", Speed, 0, 60);
	//CManager::GetDebugFont()->AddDebugFont("Player:State", State, 0, 80);
#endif
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer;

	//インスタンス生成
	pPlayer = new CPlayer;

	//初期化処理
	pPlayer->Initialize();

	//コンテナクラスにオブジェクトの型を設定
	pPlayer->SetObjType(OBJTYPE_PLAYER);

	//マテリアルバッファを送る
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_PLAYER));

	//メッシュ情報を送る
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_PLAYER));

	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_PLAYER));

	pPlayer->BindTexture(NULL);

	return pPlayer;
}

/******************************************************************
移動処理関数
*******************************************************************/
void CPlayer::Move(void)
{
	State = NONE;

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_W))
	{
		State = WALK;
		CParticle::Create(Position);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_S))
	{
		Vector *= -1;
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_A))
	{
		//回転行列
		D3DXMatrixRotationYawPitchRoll(&RotateMatrix,
			D3DXToRadian(-90.0f),
			D3DXToRadian(0.0f),
			D3DXToRadian(0.0f));

		D3DXVec3TransformCoord(&Vector, &Vector, &RotateMatrix);
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_D))
	{
		//回転行列
		D3DXMatrixRotationYawPitchRoll(&RotateMatrix,
			D3DXToRadian(90.0f),
			D3DXToRadian(0.0f),
			D3DXToRadian(0.0f));

		D3DXVec3TransformCoord(&Vector, &Vector, &RotateMatrix);
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		CBullet::Create(Position, Vector);
	}

	if (State == WALK)
	{
		Position = CPhysics::AddForce(Position, Speed * Vector);
	}
}

/******************************************************************
オブジェクトの当たり判定処理関数
*******************************************************************/
void CPlayer::HitObject(void)
{
	//オブジェクト数繰り返す
	for (int nCntScene = 0; nCntScene < 1000; nCntScene++)
	{
		//オブジェクトの情報取得
		CScene *pScene = CScene::GetScene(nCntScene);

		//オブジェクトのポインターがNULLでないなら
		if (pScene != NULL)
		{
			//オブジェクトの型を取得
			CScene::OBJTYPE ObjType = pScene->GetObjType();

			if (ObjType == CScene::OBJTYPE_ITEM)
			{
				//オブジェクトポインタ
				CItem *pItem = (CItem*)pScene;

				if (CCollision::SphereCollision(Position, pItem->GetPosition()))
				{
					pItem->Hit(OBJTYPE_PLAYER);
					pScore->AddScore(10);
				}
			}

		}
	}
}