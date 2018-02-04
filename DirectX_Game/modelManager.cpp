/******************************************************************
***
***		モデル管理処理
***
***		modelManager.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "modelManager.h"

/******************************************************************
コンストラクタ
*******************************************************************/
CModelManager::CModelManager()
{
	for (int count = 0; count < TYPE_MAX; count++)
	{
		pModelList[count] = NULL;
		pMesh[count] = NULL;
		pMatBuff[count] = NULL;
		NumMaterials[count] = NULL;
	}
}
/******************************************************************
初期化処理関数
*******************************************************************/
void CModelManager::Initialize(void)
{
	//モデルリストを初期化
	pModelList[TYPE_PLAYER] = "data/Model/a.x";
	pModelList[TYPE_ENEMY] = "data/Model/incect_face_RED.x";
	pModelList[TYPE_GOAL] = "data/Model/goal.x";
	pModelList[TYPE_TREE] = "data/Model/tree_02.x";
	pModelList[TYPE_ITEM] = "data/Model/a.x";
	pModelList[TYPE_BUILDING] = "data/Model/building002.x";
}

/******************************************************************
終了処理関数
*******************************************************************/
void CModelManager::Unitialize(void)
{
	for (int count = 0; count < TYPE_MAX; count++)
	{
		//モデルリストを破棄
		if (pModelList[count] != NULL)
		{
			pModelList[count] = NULL;
		}

		//メッシュの破棄
		if (pMesh[count] != NULL)
		{
			pMesh[count]->Release();
			pMesh[count] = NULL;
		}
		
		//マテリアルバッファの破棄
		if (pMatBuff[count] != NULL)
		{
			pMatBuff[count]->Release();
			pMatBuff[count] = NULL;
		}
	}
}

/******************************************************************
モデル取得関数
*******************************************************************/
void CModelManager::LoadModel(MODEL_TYPE OrderModelType)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if (pMatBuff[OrderModelType] == NULL && NumMaterials[OrderModelType] == NULL&&pMesh[OrderModelType]==NULL)
	{
		//モデル読み込み
		if (FAILED(D3DXLoadMeshFromX(pModelList[OrderModelType], D3DXMESH_MANAGED, pDevice, NULL, &pMatBuff[OrderModelType], NULL, &NumMaterials[OrderModelType], &pMesh[OrderModelType])))
		{
			MessageBox(NULL, "モデルが読み込めませんでした", "エラーメッセージ", MB_OK);
			PostQuitMessage(0);
		}
	}
}

LPD3DXMESH CModelManager::GetMesh(MODEL_TYPE OrderModelType) 
{ return pMesh[OrderModelType]; }

DWORD CModelManager::GetNumMaterials(MODEL_TYPE OrderModelType) 
{ return NumMaterials[OrderModelType]; }

LPD3DXBUFFER CModelManager::GetMaterialBuffer(MODEL_TYPE OrderModelType) 
{ return pMatBuff[OrderModelType]; }
