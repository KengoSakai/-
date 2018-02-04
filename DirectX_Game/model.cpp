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
#include "model.h"
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
CModel::CModel()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CModel::~CModel()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CModel::Initialize(void)
{
	pTexture = NULL;
	pMesh = NULL;
	pMaterialBuffer = NULL;
	NumMaterials = 0;
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/******************************************************************
モデル終了処理関数
*******************************************************************/
void CModel::Uninitialize(void)
{
	CScene::Release();
}

/******************************************************************
モデル更新処理関数
*******************************************************************/
void CModel::Update(void)
{

}

/******************************************************************
モデル描画処理関数
*******************************************************************/
void CModel::Draw(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CManager::GetLight()->SetModelLight();
	D3DMATERIAL9 Matdef;

	pDevice->GetMaterial(&Matdef);
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pMaterialBuffer->GetBufferPointer();

	//マテリアル数分繰り返す
	for(DWORD count = 0 ; count < NumMaterials ; count++ )
	{
		//モデルをセット
		pDevice->SetMaterial(&pMat[count].MatD3D);
		pDevice->SetTexture(0,pTexture);

		//描画関数呼び出し
		pMesh->DrawSubset(count);
	}
	pDevice->SetMaterial(&Matdef);
	DrawShadow();
}

void CModel::SetMatrix(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice =  CManager::GetRenderer()->GetDevice();

	//単位行列
	D3DXMatrixIdentity(&WorldMatrix);
	
	//拡大行列
	D3DXMatrixScaling(&ScaleMatrix,Scale.x,Scale.y,Scale.z);
	
	//平行行列
	D3DXMatrixTranslation(&TranslationMatrix,Position.x, Position.y, Position.z);
	
	//回転行列
	D3DXMatrixRotationYawPitchRoll(&RotateMatrix,
		D3DXToRadian(Rotate.y),
		D3DXToRadian(Rotate.x),
		D3DXToRadian(Rotate.z));

	//ワールド変換
	WorldMatrix = ScaleMatrix * RotateMatrix * TranslationMatrix;

	//ワールド座標に設定
	pD3DDevice->SetTransform(D3DTS_WORLD,&WorldMatrix);

}
/******************************************************************
マテリアルバッファ情報読み込み処理関数
*******************************************************************/
void CModel::BindBuff(LPD3DXBUFFER pOrderMatBuff)
{
	pMaterialBuffer = pOrderMatBuff;
}

/******************************************************************
要素数情報読み込み処理関数
*******************************************************************/
void CModel::BindMaterials(DWORD OrderNumMaterials)
{
	NumMaterials = OrderNumMaterials;
}

/******************************************************************
メッシュ情報読み込み処理関数
*******************************************************************/
void CModel::BindMesh(LPD3DXMESH pOrderMesh)
{
	pMesh = pOrderMesh;
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CModel :: BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	pTexture = pOrderTexture;
}

void CModel::DrawShadow(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 LightVector;
	D3DXVECTOR3 Light;
	D3DXMatrixIdentity(&ShadowMatrix);
	LightVector = Position - CManager::GetLight()->GetPosition();

	ShadowMatrix._21 = -LightVector.x/ LightVector.y;
	ShadowMatrix._22 = 0.0f;
	ShadowMatrix._23 = -LightVector.z / LightVector.y;
	ShadowMatrix._42 = 0.5f;
	WorldMatrix = WorldMatrix * ShadowMatrix;

	//ワールド座標に設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);

	CManager::GetLight()->SetShadowLight();
	
	D3DMATERIAL9 Matdef;

	pD3DDevice->GetMaterial(&Matdef);
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pMaterialBuffer->GetBufferPointer();

	//マテリアル数分繰り返す
	for (DWORD count = 0; count < NumMaterials; count++)
	{
		//モデルをセット
		pD3DDevice->SetMaterial(&pMat[count].MatD3D);
		//pDevice->SetTexture(0,pTexture);//m_pTexture[nCnt]);
		pD3DDevice->SetTexture(0, NULL);//m_pTexture[nCnt]);

									 //描画関数呼び出し
		pMesh->DrawSubset(count);
	}
	pD3DDevice->SetMaterial(&Matdef);
}

void CModel::SetModel(void)
{

}