/******************************************************************
***
***		メッシュドーム処理
***
***		meshDome.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "meshDome.h"
#include "textureManager.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_VERTEX (4)	//頂点数
#define NUM_POLYGON (2)
#define NUM_MESH_X (20)			//横のマス数
#define NUM_MESH_Z (4)			//縦のマス数
#define NUM_Y (100.0f)
#define NUM_MESH_VERTEX ((NUM_MESH_X+1) * (NUM_MESH_Z+1))								//頂点の総数
#define NUM_MESH_INDEX (((NUM_MESH_X +1)*2) + ((NUM_MESH_Z-1) * (NUM_MESH_X+2)*2) )
#define NUM_MESH_POLYGON (((NUM_MESH_X * NUM_MESH_Z * NUM_POLYGON) + (4 * (NUM_MESH_Z-1))))	//総ポリゴン数
#define NUM_ROT ((360.0f/(NUM_MESH_X-2)))
#define NUM_LENGTH (500.0f)
#define POS_Y ((NUM_Y*NUM_MESH_Z)*2) 

/******************************************************************
グローバル変数
*******************************************************************/
CRenderer *CMeshDome::m_pRenderer = NULL;
/******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CMeshDome::CMeshDome()
{
	/*CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_SKY);
	pTexture = CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_SKY);
*/
	pTexture = NULL;
}

/******************************************************************
デストラクタ
*******************************************************************/
CMeshDome::~CMeshDome()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CMeshDome::Initialize(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報作成処理
	MakeVertex();

	//インデックスバッファ設定処理
	MakeIndex();

	//ステータスの初期化
	m_Pos = D3DXVECTOR3(0.0f,POS_Y,0.0f);		//座標
	m_Rot = D3DXVECTOR3(180.0f,0.0f,0.0f);	//角度
	m_Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);		//拡大率
	Color = D3DXCOLOR(255.0f,255.0f,255.0f,255.0f);
}

/******************************************************************
終了処理関数
*******************************************************************/
void CMeshDome::Uninitialize(void)
{
	//バッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if(m_IndexBuff != NULL)
	{
		m_IndexBuff->Release();
		m_IndexBuff = NULL;
	}
	
	CScene::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CMeshDome::Update(void)
{
	m_Rot.y +=0.01f;
	//Color.r = 0.0f;
	//Color.g = 0.0f;
	//Color.b = 0.0f;
	//SetColor();
}

/******************************************************************
描画処理関数
*******************************************************************/
void CMeshDome::Draw(void)
{
	//レンダーステートの状態取得
	m_pRenderer = CManager::GetRenderer();

	//Zバッファの設定
	m_pRenderer->SetzBuff();

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice =  CManager::GetRenderer()->GetDevice();

	//単位行列
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//拡大行列
	D3DXMatrixScaling(&m_mtxScale,m_Scale.x,m_Scale.y,m_Scale.z);
	
	//平行行列
	D3DXMatrixTranslation(&m_mtxTrans,m_Pos.x,m_Pos.y,m_Pos.z);
	
	//回転行列
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot,
		D3DXToRadian(m_Rot.y),
		D3DXToRadian(m_Rot.x),
		D3DXToRadian(m_Rot.z));
	
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&m_mtxScale);
	
	//ワールド変換
	m_mtxWorld = m_mtxScale * m_mtxRot * m_mtxTrans;

	//ワールド座標に設定
	pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);



	//頂点フォーマットの設定
	pD3DDevice -> SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0,NULL);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING,false);

	//頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_3D));

	pD3DDevice->SetIndices(m_IndexBuff);

	//ポリゴンの描画
	pD3DDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//描画タイプ
		0,					//最初の頂点インデックス番号
		0,					//最小の頂点インデックス番号
		NUM_MESH_VERTEX,	//頂点総数
		0,					//始めのインデックス番号
		NUM_MESH_POLYGON);	//ポリゴンの総数

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING,true);
}

/******************************************************************
頂点設定処理関数
*******************************************************************/
void CMeshDome::MakeVertex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice =  CManager::GetRenderer()->GetDevice();

	//変数宣言
	int nCnt = 0;	//ループカウンタ
	int nCntSec = 0;
	float fRot=0.0f;
	D3DXVECTOR2 BuffTex;
	BuffTex.x = 0.0f;
	BuffTex.y = 1.0f;

	D3DXVECTOR3 BuffPos(NUM_LENGTH*cosf(D3DXToRadian(0.0f))-sinf(D3DXToRadian(0.0f))
		,0.0f
		,NUM_LENGTH*sinf(D3DXToRadian(fRot))+cosf(D3DXToRadian(fRot)));

	//頂点構造体ポインタ
	VERTEX_3D * pVtx;

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_MESH_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_3D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&m_pVtxBuff,					//アドレスの指定
		NULL);

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//縦のポリゴン数分繰り返す
	for(int z = 0 ; z < NUM_MESH_Z+1 ; z++)
	{
		//横のポリゴン数分繰り返す
		for(int x = 0 ; x < NUM_MESH_X+1 ; x++,nCnt++)
		{
			if(nCnt != 0 && nCnt %(NUM_MESH_X+1)==0)
			{
				//横をずらす
				BuffPos.x = NUM_LENGTH*z*cosf(D3DXToRadian(fRot))-sinf(D3DXToRadian(fRot));
				BuffPos.z = NUM_LENGTH*z*sinf(D3DXToRadian(fRot))+cosf(D3DXToRadian(fRot));
				BuffPos.y +=z*NUM_Y;

				BuffTex.x = 0.0f;
				BuffTex.y+=(1.0f/NUM_MESH_Z);
			}
			//頂点座標の設定
			pVtx[nCnt].pos = D3DXVECTOR3(BuffPos.x,BuffPos.y,BuffPos.z);

			//法線情報
			pVtx[nCnt].normal = D3DXVECTOR3(0.0f,1.0f,0.0f);

			//頂点色の設定
			pVtx[nCnt].color = D3DCOLOR_RGBA(105,155,255,255);

			//テクスチャの座標設定
			pVtx[nCnt].tex = D3DXVECTOR2(BuffTex.x,BuffTex.y);

			//横にずらす
			BuffPos.x = z*NUM_LENGTH*cosf(D3DXToRadian(fRot))-sinf(D3DXToRadian(fRot));
			BuffPos.z = z*NUM_LENGTH*sinf(D3DXToRadian(fRot))+cosf(D3DXToRadian(fRot));

			fRot+=NUM_ROT;
			BuffTex.x+=(1.0f/NUM_MESH_X);
		}
		fRot=0.0f;
	}
	//バッファをアンロック
	m_pVtxBuff -> Unlock();
}

/******************************************************************
インデックスバッファ設定処理関数
*******************************************************************/
void CMeshDome::MakeIndex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice =  CManager::GetRenderer()->GetDevice();

	//インデックスバッファ用ポインタ
	WORD *pIndex = NULL;
	int nIndex = NUM_MESH_X+1;
	int nIndexCnt = nIndex;
	int nCntSec = 0;

	//インデックスバッファの生成
	pDevice ->CreateIndexBuffer(
		sizeof(WORD) * NUM_MESH_INDEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		D3DFMT_INDEX16,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&m_IndexBuff,					//アドレスの指定
		NULL);

	//バッファをロックして仮想アドレスを取得する
	m_IndexBuff -> Lock(
		0,				//範囲指定
		0,
		(void**)&pIndex,	//仮想アドレスの取得
		0);

	//Ｚの数だけ繰り返す
	for(int nCnt = 0 ; nCnt <NUM_MESH_INDEX  ; nCnt +=2 , nCntSec++)
	{		
		//端に来たら
		if(nCntSec !=0 && nCntSec % (NUM_MESH_X+1) == 0)
		{
			//前と同じ点を打つ
			pIndex[nCnt] = pIndex[nCnt-1];
			
			nIndexCnt += NUM_MESH_X+1;
			nIndex = nIndexCnt;
			pIndex[nCnt+1] = nIndex;
			nCnt += 2;
		}

		//インデックスバッファを設定
		pIndex[nCnt] = nIndex;
		pIndex[nCnt+1] = pIndex[nCnt] - (NUM_MESH_X + 1);
		nIndex++;
	}

	//pIndex=NULL;

	//バッファをアンロック
	m_IndexBuff -> Unlock();
}

/******************************************************************
オブジェクト作成関数
*******************************************************************/
CMeshDome *CMeshDome::Create(void)
{
	//オブジェクトポインタ
	CMeshDome *pMeshField;

	//インスタンスの生成
	pMeshField = new CMeshDome;

	//初期化処理
	pMeshField -> Initialize();

	//オブジェクトの型登録関数呼び出し
	pMeshField->SetObjType(OBJTYPE_DOME);

	return pMeshField;
}

void CMeshDome::SetColor(void)
{
	int nCnt = 0;	//ループカウンタ

	//頂点構造体ポインタ
	VERTEX_3D * pVtx;

	//バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(
		0,				//範囲指定
		0,
		(void**)&pVtx,	//仮想アドレスの取得
		0);

	//縦のポリゴン数分繰り返す
	for (int z = 0; z < NUM_MESH_Z + 1; z++)
	{
		//横のポリゴン数分繰り返す
		for (int x = 0; x < NUM_MESH_X + 1; x++, nCnt++)
		{
			//頂点色の設定
			pVtx[nCnt].color = Color;
		}
	}
	//バッファをアンロック
	m_pVtxBuff->Unlock();

}