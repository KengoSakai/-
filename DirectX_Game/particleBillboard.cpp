/******************************************************************
***
***		パーティクルビルボード処理
***
***		particleBillboard.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "particleBillboard.h"
#include "camera.h"
//#include "shader.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_VERTEX (4)	//頂点数
#define NUM_POLYGON (2)	//ポリゴン数
/*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/*******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CParticleBillboard::CParticleBillboard()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/******************************************************************
デストラクタ
*******************************************************************/
CParticleBillboard::~CParticleBillboard()
{

}

/******************************************************************
初期化処理処理関数
*******************************************************************/
void CParticleBillboard::Initialize(void)
{
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	//頂点作成処理
	MakeVertex();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CParticleBillboard::Uninitialize(void)
{

	//3Dポリゴンのバッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//シーン破棄
	CParticleManager::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CParticleBillboard::Update(void)
{

}

/******************************************************************
ポリゴン描画処理関数
*******************************************************************/
void CParticleBillboard::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	
	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0, m_pTexture);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/******************************************************************
頂点作成処理関数
*******************************************************************/
void CParticleBillboard::MakeVertex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_3D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&m_pVtxBuff,					//アドレスの指定
		NULL);

	//頂点構造体ポインタ
	VERTEX_3D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

	//法線情報
	pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点座標の色
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CParticleBillboard::BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	m_pTexture = pOrderTexture;
}

/******************************************************************
頂点色設定処理関数
*******************************************************************/
void CParticleBillboard::SetColor(D3DXCOLOR OrderColor)
{
	VERTEX_3D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//テクスチャの座標
	pVtx[0].color = D3DCOLOR_RGBA((int)OrderColor.r, (int)OrderColor.g, (int)OrderColor.b, (int)OrderColor.a);
	pVtx[1].color = D3DCOLOR_RGBA((int)OrderColor.r, (int)OrderColor.g, (int)OrderColor.b, (int)OrderColor.a);
	pVtx[2].color = D3DCOLOR_RGBA((int)OrderColor.r, (int)OrderColor.g, (int)OrderColor.b, (int)OrderColor.a);
	pVtx[3].color = D3DCOLOR_RGBA((int)OrderColor.r, (int)OrderColor.g, (int)OrderColor.b, (int)OrderColor.a);

	//バッファのアンロック
	m_pVtxBuff->Unlock();
}

/******************************************************************
回転処理関数
*******************************************************************/
void CParticleBillboard::SetRotate(D3DXVECTOR3 Position, float Size)
{
	VERTEX_3D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Position.x- Size, Position.y + Size, Position.z);
	pVtx[1].pos = D3DXVECTOR3(Position.x+ Size, Position.y + Size, Position.z);
	pVtx[2].pos = D3DXVECTOR3(Position.x - Size, Position.y - Size, Position.z);
	pVtx[3].pos = D3DXVECTOR3(Position.x + Size, Position.y - Size, Position.z);

	//バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CParticleBillboard::SetBillboard(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////単位行列
	D3DXMatrixIdentity(&WorldMatrix);

	InverseMatrix = CManager::GetCamera()->GetViewMatrix();

	//転置行列
	D3DXMatrixTranspose(&WorldMatrix, &InverseMatrix);
	WorldMatrix._14 = 0.0f;
	WorldMatrix._24 = 0.0f;
	WorldMatrix._34 = 0.0f;

	//拡大行列
	D3DXMatrixScaling(&ScaleMatrix, Scale.x, Scale.y, Scale.z);

	//平行行列
	D3DXMatrixTranslation(&TranslationMatrix, EmitterPosition.x, EmitterPosition.y, EmitterPosition.z);

	WorldMatrix = WorldMatrix * ScaleMatrix*TranslationMatrix;
	//ワールド変換
	pDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
}

