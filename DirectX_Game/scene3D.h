/******************************************************************
***
***		3D描画処理
***
***		scene3D.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene.h"
#include "textureManager.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CScene3D : public CScene
{
public:
	CScene3D();				//コンストラクタ
	~CScene3D();			//デストラクタ
	void Initialize (void);							//初期化処理
	void Uninitialize(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	
	void BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture);	//テクスチャ読み込み処理	
	void SetPos(D3DXVECTOR3 OrderPosition);		//座標設定処理
	void SetMatrix(void);			//行列設定処理
	void SetBillboard(void);
	LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ

private:
	void MakeVertex(void);							//頂点作成処理
													//座標情報
	
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファポインタ
protected:

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotate;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Vector;
	D3DXCOLOR Color;
	float Size;

	D3DXMATRIX RotateMatrix;
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX InverseMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ShadowMatrix;

};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif