#include "manager.h"
#include "goalModel.h"

//コンストラクタ
CGoalModel::CGoalModel()
{
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_GOAL);
}

//初期化処理
void CGoalModel::Initialize(void)
{
	Position = D3DXVECTOR3(0.0, 10.0, 0.0);
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
//終了処理
void CGoalModel::Uninitialize(void)
{
	//モデルの破棄
	CModel::Uninitialize();
}

//更新処理
void CGoalModel::Update(void)
{

}

//描画処理
void CGoalModel::Draw(void)
{
	CModel::SetMatrix();

	//モデル描画
	CModel::Draw();
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CGoalModel *CGoalModel::Create(void)
{
	CGoalModel *pGoalmodel;

	//インスタンス生成
	pGoalmodel = new CGoalModel;

	//初期化処理
	pGoalmodel->Initialize();

	//コンテナクラスにオブジェクトの型を設定
	pGoalmodel->SetObjType(OBJTYPE_GOAL);

	//マテリアルバッファを送る
	pGoalmodel->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_GOAL));

	//メッシュ情報を送る
	pGoalmodel->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_GOAL));

	//マテリアルの要素数を送る
	pGoalmodel->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_GOAL));

	pGoalmodel->BindTexture(NULL);
	return pGoalmodel;
}
