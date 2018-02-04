/******************************************************************
***
***		２D描画処理
***
***		scene2D.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"

/******************************************************************
マクロ定義
*******************************************************************/

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
/******************************************************************
構造体定義
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
CScene2D :: CScene2D ()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CScene2D :: ~CScene2D ()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CScene2D :: Initialize(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//初期値設定
	Scale.x = 1.0f;
	Scale.y = 1.0f;
	Scale.z = 0.0f;

	Rotate.x = 0.0f;
	Rotate.y = 0.0f;
	Rotate.z = 0.0f;
	m_pTexture = NULL;

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_2D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&m_pVtxBuff,					//アドレスの指定
		NULL);

	VERTEX_2D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Position.x, Position.y,0.0f);										//(X.Y.Z)
	pVtx[1].pos = D3DXVECTOR3(Position.x+WidthHeight.x, Position.y,0.0f);						//(X.Y.Z)
	pVtx[2].pos = D3DXVECTOR3(Position.x, Position.y+ WidthHeight.y,0.0f);					//(X.Y.Z)
	pVtx[3].pos = D3DXVECTOR3(Position.x+ WidthHeight.x, Position.y+ WidthHeight.y,0.0f);		//(X.Y.Z)

	//頂点フラグ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点座標の色
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//バッファのアンロック
	m_pVtxBuff -> Unlock();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CScene2D :: Uninitialize(void)
{
	//頂点バッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff -> Release();
		m_pVtxBuff = NULL;
	}

	//シーン破棄
	CScene::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CScene2D::Update(void)
{

}

/******************************************************************
描画処理関数
*******************************************************************/
void CScene2D :: Draw (void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//頂点バッファをデータストリームに設定
	pDevice -> SetStreamSource(
		0,
		m_pVtxBuff,
		0,						//データのオフセット
		sizeof(VERTEX_2D)		//ストライド量（バイト）
		);

	//テクスチャの設定
	pDevice -> SetTexture(0,m_pTexture);

	// ポリゴンの描画
	pDevice -> DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

/******************************************************************
テクスチャ座標設定処理関数
*******************************************************************/
void CScene2D :: SetTexPos(D3DXVECTOR3 TexPos , D3DXVECTOR3 TexWh)
{
	VERTEX_2D* pVtx;
	
	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(TexPos.x,TexPos.y);
	pVtx[1].tex = D3DXVECTOR2(TexPos.x + TexWh.x,TexPos.y);
	pVtx[2].tex = D3DXVECTOR2(TexPos.x, TexWh.y);
	pVtx[3].tex = D3DXVECTOR2(TexPos.x + TexWh.x , TexWh.y);

	//バッファのアンロック
	m_pVtxBuff -> Unlock();
}

/******************************************************************
頂点色設定処理関数
*******************************************************************/
void CScene2D :: SetColor(D3DXCOLOR OrderColor)
{
	VERTEX_2D* pVtx;
	
	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//テクスチャの座標
	pVtx[0].col = D3DCOLOR_RGBA((int)OrderColor.r,(int)OrderColor.g,(int)OrderColor.b,(int)OrderColor.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)OrderColor.r,(int)OrderColor.g,(int)OrderColor.b,(int)OrderColor.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)OrderColor.r,(int)OrderColor.g,(int)OrderColor.b,(int)OrderColor.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)OrderColor.r,(int)OrderColor.g,(int)OrderColor.b,(int)OrderColor.a);

	//バッファのアンロック
	m_pVtxBuff -> Unlock();
}

void CScene2D::SetPosition(void)
{
	VERTEX_2D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Position.x, Position.y, 0.0f);										//(X.Y.Z)
	pVtx[1].pos = D3DXVECTOR3(Position.x + WidthHeight.x, Position.y, 0.0f);						//(X.Y.Z)
	pVtx[2].pos = D3DXVECTOR3(Position.x, Position.y + WidthHeight.y, 0.0f);					//(X.Y.Z)
	pVtx[3].pos = D3DXVECTOR3(Position.x + WidthHeight.x, Position.y + WidthHeight.y, 0.0f);		//(X.Y.Z)
																									//バッファのアンロック
	m_pVtxBuff->Unlock();
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CScene2D :: BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	m_pTexture = pOrderTexture;
}
