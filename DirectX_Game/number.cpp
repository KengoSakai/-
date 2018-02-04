/******************************************************************
***
***		数字処理
***
***		number.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"
#include "manager.h"
#include "textureManager.h"
#include "renderer.h"
#include "number.h"
#include "score.h"

/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)

#define POLYGON_POSX (500)											//ポリゴンの表示位置X
#define POLYGON_POSY (10)											//ポリゴンの表示位置Y
#define POLYGON_WIDTH (30)											//ポリゴンの幅
#define POLYGON_HEIGHT (100)										//ポリゴンの高さ
#define POLYGON_SCALE (30.0f)
/******************************************************************
構造体定義またはクラス定義
*******************************************************************/


/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/
CRenderer *CNumber::pRenderer = NULL;

//コンストラクタ
CNumber::CNumber()
{
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_NUMBER);

	pTexture = CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_NUMBER);

}

//デストラクタ
CNumber :: ~CNumber()
{

}

//初期化処理関数
HRESULT CNumber::Init(int Digit, D3DXVECTOR3 OrderPosition)
{
	Position = OrderPosition;	//座標
	Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//角度
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0);			//拡大率

	//頂点バッファ生成
	MakeVertex(Digit);

	return S_OK;
}

//終了処理関数
void CNumber::Uninit(void)
{
	//バッファがNULLでないなら
	if (pVtxBuff != NULL)
	{
		//バッファの開放
		pVtxBuff->Release();
		pVtxBuff = NULL;
	}
}

//更新処理関数
void CNumber::Update(void)
{

}

//描画処理関数
void CNumber::Draw(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//レンダーステートの状態取得
	pRenderer = CManager::GetRenderer();

	//行列変換
	SetMatrix();

	//Zバッファの設定
	pRenderer->SetzBuff();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		pVtxBuff,
		0,						//データのオフセット
		sizeof(VERTEX_2D)		//ストライド量（バイト）
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	pRenderer->SetDefaultBrend();
}

//オブジェクト生成処理関数
CNumber *CNumber::Create(int Digit, D3DXVECTOR3 OrderPosition)
{
	//ポインタ宣言
	CNumber *pNumber;

	//インスタンスの生成
	pNumber = new CNumber;

	//初期化処理
	pNumber->Init(Digit, OrderPosition);

	
	return pNumber;
}

//表示数字設定処理関数
void CNumber::SetNumber(int Number)
{
	//テクスチャ座標の設定
	VERTEX_2D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2((float)Number / 10.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)Number / 10.0f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)Number / 10.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)Number / 10.0f + 0.1f, 1.0f);

	//バッファのアンロック
	pVtxBuff->Unlock();
}

//行列設定処理関数
void CNumber::SetMatrix(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//単位行列
	D3DXMatrixIdentity(&mtxWorld);

	//拡大行列
	D3DXMatrixScaling(&mtxScale, Scale.x, Scale.y, Scale.z);

	//平行行列
	D3DXMatrixTranslation(&mtxTrans, Position.x, Position.y, Position.z);

	//回転行列
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		D3DXToRadian(Rot.y),
		D3DXToRadian(Rot.x),
		D3DXToRadian(Rot.z));

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

//頂点バッファ生成処理関数
void CNumber::MakeVertex(int Digit)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_2D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&pVtxBuff,					//アドレスの指定
		NULL);

	VERTEX_2D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Position.x - (Digit * POLYGON_SCALE), Position.y, -10.0f);										//(X.Y.Z)
	pVtx[1].pos = D3DXVECTOR3(Position.x + POLYGON_WIDTH - (Digit * POLYGON_SCALE), Position.y, -10.0f);						//(X.Y.Z)
	pVtx[2].pos = D3DXVECTOR3(Position.x - (Digit * POLYGON_SCALE), Position.y + POLYGON_HEIGHT, -10.0f);						//(X.Y.Z)
	pVtx[3].pos = D3DXVECTOR3(Position.x + POLYGON_WIDTH - (Digit * POLYGON_SCALE), Position.y + POLYGON_HEIGHT, -10.0f);		//(X.Y.Z)

																																//頂点フラグ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点座標の色
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//バッファのアンロック
	pVtxBuff->Unlock();

}
