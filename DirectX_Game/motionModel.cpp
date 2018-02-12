/******************************************************************
***
***		3Dモデル処理
***
***		model.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "motionModel.h"
#include "light.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CMotionModel::CMotionModel()
{
	pTexture = NULL;
	for (int PartsCount = 0; PartsCount < PARTS_MAX; PartsCount++)
	{
		pMesh[PartsCount] = NULL;
		pMaterialBuffer[PartsCount] = NULL;
		NumMaterials[PartsCount] = 0;
		Rotate[PartsCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


/******************************************************************
初期化処理関数
*******************************************************************/
void CMotionModel::Initialize(void)
{

}

/******************************************************************
モデル終了処理関数
*******************************************************************/
void CMotionModel::Uninitialize(void)
{
	CScene::Release();
}

/******************************************************************
モデル更新処理関数
*******************************************************************/
void CMotionModel::Update(void)
{

}

/******************************************************************
モデル描画処理関数
*******************************************************************/
void CMotionModel::Draw(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CManager::GetLight()->SetModelLight();
	D3DMATERIAL9 Matdef;

	for (int Count = 0; Count < PARTS_MAX; Count++)
	{
		//単位行列
		D3DXMatrixIdentity(&WorldMatrix[Count]);

		//拡大行列
		D3DXMatrixScaling(&ScaleMatrix[Count], Scale.x, Scale.y, Scale.z);

		//平行行列
		D3DXMatrixTranslation(&TranslationMatrix[Count], PartsPosition[Count].x, PartsPosition[Count].y, PartsPosition[Count].z);


		//回転行列
		D3DXMatrixRotationYawPitchRoll(&RotateMatrix[Count],
			D3DXToRadian(Rotate[Count].y),
			D3DXToRadian(Rotate[Count].x),
			D3DXToRadian(Rotate[Count].z));

		//ワールド変換
		WorldMatrix[Count] = ScaleMatrix[Count] * RotateMatrix[Count] * TranslationMatrix[Count];

		//ワールド座標に設定
		pDevice->SetTransform(D3DTS_WORLD, &WorldMatrix[Count]);


		pDevice->GetMaterial(&Matdef);
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)pMaterialBuffer[Count]->GetBufferPointer();

		//マテリアル数分繰り返す
		for (DWORD count = 0; count < NumMaterials[Count]; count++)
		{
			//モデルをセット
			pDevice->SetMaterial(&pMat[count].MatD3D);
			pDevice->SetTexture(0, pTexture);

			//描画関数呼び出し
			pMesh[Count]->DrawSubset(count);
		}
		pDevice->SetMaterial(&Matdef);
		DrawShadow();
	}
}

void CMotionModel::SetMatrix(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	for (int Count = 0; Count < PARTS_MAX; Count++)
	{
		//単位行列
		D3DXMatrixIdentity(&WorldMatrix[Count]);

		//拡大行列
		D3DXMatrixScaling(&ScaleMatrix[Count], Scale.x, Scale.y, Scale.z);

		//平行行列
		D3DXMatrixTranslation(&TranslationMatrix[Count], PartsPosition[Count].x, PartsPosition[Count].y, PartsPosition[Count].z);

		Rotate[Count].y += Rotate[ParentParts[Count]].y;
		Rotate[Count].x += Rotate[ParentParts[Count]].x;
		Rotate[Count].z += Rotate[ParentParts[Count]].z;

		//回転行列
		D3DXMatrixRotationYawPitchRoll(&RotateMatrix[Count],
			D3DXToRadian(Rotate[Count].y),
			D3DXToRadian(Rotate[Count].x),
			D3DXToRadian(Rotate[Count].z));

		//ワールド変換
		WorldMatrix[Count] = ScaleMatrix[Count] * RotateMatrix[Count] * TranslationMatrix[Count];

		//ワールド座標に設定
		pD3DDevice->SetTransform(D3DTS_WORLD, &WorldMatrix[Count]);
	}
}
/******************************************************************
マテリアルバッファ情報読み込み処理関数
*******************************************************************/
void CMotionModel::BindBuff(LPD3DXBUFFER pOrderMatBuff, PARTS ModelParts)
{
	pMaterialBuffer[ModelParts] = pOrderMatBuff;
}

/******************************************************************
要素数情報読み込み処理関数
*******************************************************************/
void CMotionModel::BindMaterials(DWORD OrderNumMaterials, PARTS ModelParts)
{
	NumMaterials[ModelParts] = OrderNumMaterials;
}

/******************************************************************
メッシュ情報読み込み処理関数
*******************************************************************/
void CMotionModel::BindMesh(LPD3DXMESH pOrderMesh, PARTS ModelParts)
{
	pMesh[ModelParts] = pOrderMesh;
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CMotionModel::BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	pTexture = pOrderTexture;
}

void CMotionModel::DrawShadow(void)
{
	////デバイス情報の取得
	//LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	//D3DXVECTOR3 LightVector;
	//D3DXVECTOR3 Light;
	//D3DXMatrixIdentity(&ShadowMatrix);
	//LightVector = Position - CManager::GetLight()->GetPosition();

	//ShadowMatrix._21 = -LightVector.x / LightVector.y;
	//ShadowMatrix._22 = 0.0f;
	//ShadowMatrix._23 = -LightVector.z / LightVector.y;
	//ShadowMatrix._42 = 0.5f;
	//WorldMatrix = WorldMatrix * ShadowMatrix;

	////ワールド座標に設定
	//pD3DDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);

	//CManager::GetLight()->SetShadowLight();

	//D3DMATERIAL9 Matdef;

	//pD3DDevice->GetMaterial(&Matdef);
	//D3DXMATERIAL* pMat = (D3DXMATERIAL*)pMaterialBuffer->GetBufferPointer();

	////マテリアル数分繰り返す
	//for (DWORD count = 0; count < NumMaterials; count++)
	//{
	//	//モデルをセット
	//	pD3DDevice->SetMaterial(&pMat[count].MatD3D);
	//	//pDevice->SetTexture(0,pTexture);//m_pTexture[nCnt]);
	//	pD3DDevice->SetTexture(0, NULL);//m_pTexture[nCnt]);

	//									//描画関数呼び出し
	//	pMesh->DrawSubset(count);
	//}
	//pD3DDevice->SetMaterial(&Matdef);
}

