#include "manager.h"
#include "enemyModel.h"
#include "particle.h"
#include "bullet.h"
#include "physics.h"
#include "target.h"
#include "collision.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CEnemyModel::CEnemyModel()
{
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_ENEMY);
}

/******************************************************************
初期化処理関数
*******************************************************************/
void CEnemyModel::Initialize(void)
{
	Position = D3DXVECTOR3(0.0f,10.0f,20.0f);
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Vector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	Speed = 0.0f;
	State = WALK;
}

/******************************************************************
終了処理関数
*******************************************************************/
void CEnemyModel::Uninitialize(void)
{
	CModel::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CEnemyModel::Update(void)
{
	//移動処理
	Move();

	SearchObject();
	
	//オブジェクト当たり判定処理
	//HitObject();

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
void CEnemyModel::Draw(void)
{
	CModel::SetMatrix();
	CModel::Draw();
}

/******************************************************************
オブジェクト生成処理
*******************************************************************/
CEnemyModel *CEnemyModel::Create(void)
{
	//オブジェクトポインタ
	CEnemyModel *pEnemyModel;

	//インスタンス生成
	pEnemyModel = new CEnemyModel;

	//初期化処理
	pEnemyModel->Initialize();

	//コンテナクラスにオブジェクトの型を設定
	pEnemyModel->SetObjType(OBJTYPE_ENEMY);

	//マテリアルバッファを送る
	pEnemyModel->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_ENEMY));

	//メッシュ情報を送る
	pEnemyModel->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_ENEMY));

	//マテリアルの要素数を送る
	pEnemyModel->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_ENEMY));
	
	//テクスチャの設定
	pEnemyModel->BindTexture(NULL);

	return pEnemyModel;
}

void CEnemyModel::HitObject(void)
{
	//Uninitialize();
}

/******************************************************************
移動処理関数
*******************************************************************/
void CEnemyModel::Move(void)
{
	//ステートを移動に変更
	State = WALK;

	//ターゲット方向のベクトルを求める
	Vector = TargetPosition - Position;
	
	//法線を正規化
	D3DXVec3Normalize(&Vector,&Vector);

	if (CCollision::Distance(Position, TargetPosition) < 5000)
	{
		CBullet::Create(Position, Vector, OBJTYPE_ENEMY);
	}

	if (State == WALK)
	{
		Position = CPhysics::AddForce(Position, Speed * Vector);
	}
}

/******************************************************************
オブジェクト探査処理関数
*******************************************************************/
void CEnemyModel::SearchObject(void)
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

			if (ObjType == CScene::OBJTYPE_TARGET)
			{
				//オブジェクトポインタ
				CTarget *pTarget = (CTarget*)pScene;

				//if (TargetPosition = pTarget->GetPosition())
				{
					TargetPosition = pTarget->GetPosition();
					break;
				}
			}
		}
	}
}
