/******************************************************************
***
***		3D描画処理
***
***		scene3d.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_VERTEX (4)	//頂点数
#define NUM_POLYGON (2)	//ポリゴン数
#define POLYGON_POSX (300)//ポリゴンの表示位置X
#define POLYGON_POSY (100)//ポリゴンの表示位置Y
#define POLYGON_WIDTH (243)//ポリゴンの幅
#define POLYGON_HEIGHT (432)//ポリゴンの高さ
/*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/*******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CScene3D::CScene3D()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CScene3D::~CScene3D()
{

}

/******************************************************************
初期化処理処理関数
*******************************************************************/
void CScene3D::Initialize(void)
{
	//頂点作成処理
	MakeVertex();

}

/******************************************************************
終了処理関数
*******************************************************************/
void CScene3D::Uninitialize(void)
{
	//3Dポリゴンのバッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CScene3D::Update (void)
{

}

/******************************************************************
ポリゴン描画処理関数
*******************************************************************/
void CScene3D::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice =  CManager::GetRenderer()->GetDevice();

	//頂点フォーマットの設定
	pD3DDevice -> SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0, m_pTexture);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING,false);

	//頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_3D));

	//ポリゴンの描画
	pD3DDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING,true);
}

/******************************************************************
頂点作成処理関数
*******************************************************************/
void CScene3D::MakeVertex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice =  CManager::GetRenderer()->GetDevice();
	
	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_3D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&m_pVtxBuff,					//アドレスの指定
		NULL);

	//頂点構造体ポインタ
	VERTEX_3D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Position.x - Size, Position.y + Size, Position.z);
	pVtx[1].pos = D3DXVECTOR3(Position.x + Size, Position.y + Size, Position.z);
	pVtx[2].pos = D3DXVECTOR3(Position.x - Size, Position.y - Size, Position.z);
	pVtx[3].pos = D3DXVECTOR3(Position.x + Size, Position.y - Size, Position.z);

	//法線情報
	pVtx[0].normal = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].normal = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].normal = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].normal = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//頂点座標の色
	pVtx[0].color = D3DCOLOR_RGBA((int)Color.r, (int)Color.g, (int)Color.b, (int)Color.a);
	pVtx[1].color = D3DCOLOR_RGBA((int)Color.r, (int)Color.g, (int)Color.b, (int)Color.a);
	pVtx[2].color = D3DCOLOR_RGBA((int)Color.r, (int)Color.g, (int)Color.b, (int)Color.a);
	pVtx[3].color = D3DCOLOR_RGBA((int)Color.r, (int)Color.g, (int)Color.b, (int)Color.a);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	m_pVtxBuff -> Unlock();
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CScene3D :: BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	m_pTexture = pOrderTexture;
}

/******************************************************************
座標設定処理
*******************************************************************/
void CScene3D :: SetPos(D3DXVECTOR3 Pos)
{
	VERTEX_3D* pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-Pos.x,Pos.y,Pos.z);
	pVtx[1].pos = D3DXVECTOR3(Pos.x,Pos.y,Pos.z);
	pVtx[2].pos = D3DXVECTOR3(-Pos.x,Pos.y,-Pos.z);
	pVtx[3].pos = D3DXVECTOR3(Pos.x,Pos.y,-Pos.z);

	//バッファをアンロック
	m_pVtxBuff -> Unlock();
}

/******************************************************************
行列設定処理
*******************************************************************/
void CScene3D ::SetMatrix(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice =  CManager::GetRenderer()->GetDevice();

	//行列変換
	D3DXMatrixIdentity(&WorldMatrix);	//単位行列
	D3DXMatrixScaling(&ScaleMatrix,Scale.x,Scale.y,Scale.z);	//拡大行列
	D3DXMatrixTranslation(&TranslationMatrix,Position.x, Position.y, Position.z);	//平行行列
	D3DXMatrixRotationYawPitchRoll(&RotateMatrix,Rotate.y,Rotate.x,Rotate.z);	//回転行列
	
	D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&ScaleMatrix);
	WorldMatrix = ScaleMatrix * RotateMatrix * TranslationMatrix;

	pDevice->SetTransform(D3DTS_WORLD,&WorldMatrix);
}

void CScene3D::SetBillboard(void)
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
	D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

	WorldMatrix = WorldMatrix * ScaleMatrix*TranslationMatrix;
	//ワールド変換
	pDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);

}
