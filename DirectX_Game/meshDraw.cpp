/******************************************************************
***
***		メッシュフィールド処理
***
***		MeshField.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "meshDraw.h"

/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_VERTEX (4)	//頂点数
#define NUM_POLYGON (2)
#define NUM_MESH_X (150)			//横のマス数
#define NUM_MESH_Z (150)			//縦のマス数

#define NUM_MESH_VERTEX ((NUM_MESH_X+1) * (NUM_MESH_Z+1))								//頂点の総数
#define NUM_MESH_INDEX (((NUM_MESH_X +1)*2) + ((NUM_MESH_Z-1) * (NUM_MESH_X+2)*2) )
#define NUM_MESH_POLYGON (((NUM_MESH_X * NUM_MESH_Z * NUM_POLYGON) + (4 * (NUM_MESH_Z-1))))	//総ポリゴン数

#define MESH_SIZE (10.0f)

/******************************************************************
構造体またはクラス定義
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
CMeshDraw::CMeshDraw()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CMeshDraw::Initialize(void)
{
	//頂点情報作成処理
	MakeVertex();

	//インデックスバッファ設定処理
	MakeIndex();

	//ステータスの初期化
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//角度
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		//拡大率
}

/******************************************************************
終了処理関数
*******************************************************************/
void CMeshDraw::Uninitialize(void)
{
	//バッファの破棄
	if (pVertexBuffer != NULL)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}

	//インデックスバッファの破棄
	if (pIndexBuffer != NULL)
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}

	CScene::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CMeshDraw::Update(void)
{

}

/******************************************************************
描画処理関数
*******************************************************************/
void CMeshDraw::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//行列設定処理
	SetMatrix();

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0, pTexture);

	//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

	pD3DDevice->SetIndices(pIndexBuffer);

	//ポリゴンの描画
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//描画タイプ
		0,					//最初の頂点インデックス番号
		0,					//最小の頂点インデックス番号
		NUM_MESH_VERTEX,	//頂点総数
		0,					//始めのインデックス番号
		NUM_MESH_POLYGON);	//ポリゴンの総数

							//ライト設定
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/******************************************************************
頂点設定処理関数
*******************************************************************/
void CMeshDraw::MakeVertex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//変数宣言
	int nCnt = 0;	//ループカウンタ

	D3DXVECTOR2 BuffTex;
	BuffTex.x = 0.0f;
	BuffTex.y = 1.0f;

	D3DXVECTOR3 BuffPos(-(MESH_SIZE*0.5f) * NUM_MESH_X,
		0.0f,
		(MESH_SIZE*0.5f)*NUM_MESH_Z);

	//頂点構造体ポインタ
	VERTEX_3D * pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_MESH_VERTEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		FVF_VERTEX_3D,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&pVertexBuffer,					//アドレスの指定
		NULL);

	//バッファをロックして仮想アドレスを取得する
	pVertexBuffer->Lock(
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
			if (nCnt != 0 && nCnt % (NUM_MESH_X + 1) == 0)
			{
				//縦をずらす
				BuffPos.z -= MESH_SIZE;
				BuffPos.x = -(MESH_SIZE*0.5f)*NUM_MESH_X;
				BuffTex.x = 0.0f;
				BuffTex.y++;
			}
			//頂点座標の設定
			pVtx[nCnt].pos = D3DXVECTOR3(BuffPos.x, BuffPos.y, BuffPos.z);

			//法線情報
			pVtx[nCnt].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点色の設定
			pVtx[nCnt].color = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャの座標設定
			pVtx[nCnt].tex = D3DXVECTOR2(BuffTex.x, BuffTex.y);

			//横にずらす
			BuffPos.x += MESH_SIZE;
			BuffTex.x++;
		}
	}
	//バッファをアンロック
	pVertexBuffer->Unlock();
}

/******************************************************************
インデックスバッファ設定処理関数
*******************************************************************/
void CMeshDraw::MakeIndex(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//インデックスバッファ用ポインタ
	WORD *pIndex = NULL;
	int nIndex = NUM_MESH_X + 1;
	int nIndexCnt = nIndex;
	int nCntSec = 0;

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * NUM_MESH_INDEX,	//確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,				//使用方法
		D3DFMT_INDEX16,					//使用する頂点フォーマット(0でも可)
		D3DPOOL_MANAGED,				//バッファに書き込んだ物の管理方法
		&pIndexBuffer,					//アドレスの指定
		NULL);

	//バッファをロックして仮想アドレスを取得する
	pIndexBuffer->Lock(
		0,				//範囲指定
		0,
		(void**)&pIndex,	//仮想アドレスの取得
		0);

	//Ｚの数だけ繰り返す
	for (int nCnt = 0; nCnt < NUM_MESH_INDEX; nCnt += 2, nCntSec++)
	{
		//端に来たら
		if (nCntSec != 0 && nCntSec % (NUM_MESH_X + 1) == 0)
		{
			//前と同じ点を打つ
			pIndex[nCnt] = pIndex[nCnt - 1];

			nIndexCnt += NUM_MESH_X + 1;
			nIndex = nIndexCnt;
			pIndex[nCnt + 1] = nIndex;
			nCnt += 2;
		}

		//インデックスバッファを設定
		pIndex[nCnt] = nIndex;
		pIndex[nCnt + 1] = pIndex[nCnt] - (NUM_MESH_X + 1);
		nIndex++;
	}
	pIndex = NULL;
	//バッファをアンロック
	pIndexBuffer->Unlock();
}

/******************************************************************
行列設定処理関数
*******************************************************************/
void CMeshDraw::SetMatrix(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//単位行列
	D3DXMatrixIdentity(&WorldMatrix);
	
	//拡大行列
	D3DXMatrixScaling(&ScaleMatrix, Scale.x, Scale.y, Scale.z);

	//平行行列
	D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

	//回転行列
	D3DXMatrixRotationYawPitchRoll(&RotateMatrix,
		D3DXToRadian(Rotate.y),
		D3DXToRadian(Rotate.x),
		D3DXToRadian(Rotate.z));

	WorldMatrix = RotateMatrix * ScaleMatrix *   TranslationMatrix;

	pDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
}

/******************************************************************
テクスチャ読み込み処理関数
*******************************************************************/
void CMeshDraw::BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture)
{
	pTexture = pOrderTexture;
}
