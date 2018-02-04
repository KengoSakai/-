
#include "manager.h"
#include "target.h"
#include "targetRespawnPosition.h"
#include "game.h"
#include "score.h"
//コンストラクタ
CTarget::CTarget()
{
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_PLAYER);
}

//初期化処理関数
void CTarget::Initialize(void)
{
	CModel::Initialize();
	Position = CTargetRespawnPosition::RespawnPosition();
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Vector = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//終了処理関数
void CTarget::Uninitialize(void)
{
	CModel::Uninitialize();
}

//更新処理関数
void CTarget::Update(void)
{

}

//描画処理関数
void CTarget::Draw(void)
{
	CModel::SetMatrix();

	CModel::Draw();
}

//オブジェクト生成処理関数
CTarget *CTarget::Create(void)
{
	CTarget *pTarget;

	pTarget = new CTarget;

	pTarget->Initialize();

	pTarget->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_PLAYER));

	pTarget->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_PLAYER));

	pTarget->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_PLAYER));

	pTarget->BindTexture(NULL);

	pTarget->SetObjType(OBJTYPE_TARGET);

	return pTarget;
}

void CTarget::HitObject(OBJTYPE Type)
{
	if (Type == OBJTYPE_PLAYER)
	{
		//スコアの加算
		CGame::GetScore()->AddScore(10);
	}

	else if (Type == OBJTYPE_ENEMY)
	{
	//	CGame::GetOtherPlayerScore()->AddScore(10);
	}

	else
	{

	}

	Uninitialize();
}

D3DXVECTOR3 CTarget::GetPosition(void)
{
	return Position;
}