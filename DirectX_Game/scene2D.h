/******************************************************************
***
***		シーン２D処理
***
***		scene2D.h
***
***		author: Kengo Sakai
***
*******************************************************************/

#ifndef _SCENE2D_H_
#define _SCENE2D_H_
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
class CScene2D : public CScene
{
public:
	CScene2D ();			//コンストラクタ
	~CScene2D ();			//デストラクタ
	void Initialize(void);	//初期化処理
	void Uninitialize(void);		//終了処理
	void Update(void);
	void Draw (void);		//描画処理
	
	void SetTexPos(D3DXVECTOR3 TexPos , D3DXVECTOR3 TexWh);			//テクスチャ座標設定処理
	void SetColor (D3DXCOLOR OrderColor);								//頂点色設定処理
	void SetPosition(void);
	void BindTexture (LPDIRECT3DTEXTURE9 pOrderTexture);				//テクスチャ読み込み処理
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファポインタ

protected:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 WidthHeight;
	D3DXVECTOR3 Rotate;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Vector;
	D3DXCOLOR Color;
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

#endif
