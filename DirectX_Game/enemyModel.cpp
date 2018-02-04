#include "manager.h"
#include "enemyModel.h"
#include "particle.h"
#include "bullet.h"
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
	Uninitialize();
}
