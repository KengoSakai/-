/******************************************************************
***
***		メッシュドーム処理
***
***		meshDome.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MESHDOME_H_
#define _MESHDOME_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene.h"
/******************************************************************
マクロ定義
*******************************************************************/
class CRenderer;
/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CMeshDome : public CScene
{
public:
	CMeshDome();		//コンストラクタ
	~CMeshDome();		//デストラクタ
	void Initialize(void);	//初期化処理
	void Uninitialize(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
	static CMeshDome *Create(void);
private:
	void MakeVertex(void);
	void MakeIndex(void);
	void SetColor(void);
	 LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファポインタ
	LPDIRECT3DINDEXBUFFER9 m_IndexBuff;	//インデックスバッファポインタ
	D3DXCOLOR Color;
	D3DXVECTOR3 m_Pos;					//座標
	D3DXVECTOR3 m_Rot;					//角度
	D3DXVECTOR3 m_Scale;				//角度

	//行列設定
	D3DXMATRIX m_mtxWorld;							//ワールド行列
	D3DXMATRIX m_mtxTrans;							//平行行列
	D3DXMATRIX m_mtxRot;							//回転行列
	D3DXMATRIX m_mtxScale;							//拡大・縮小行列

	static CRenderer *m_pRenderer;
};
/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif
