/******************************************************************
***
***		数字処理
***
***		number.h
***
***		author: Kengo Sakai
***		date:2017/01/23
***
*******************************************************************/
#ifndef _NUMBER_H_
#define _NUMBER_H

/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"
class CRenderer;
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体もしくはクラス定義
*******************************************************************/
class CNumber
{
public:
	CNumber();								//コンストラクタ
	~CNumber();								//デストラクタ
	HRESULT Init(int Digit,D3DXVECTOR3 OrderPosition);			//初期化処理
	void Uninit (void);						//終了処理
	void Update (void);						//更新処理
	void Draw (void);						//描画処理
	void SetNumber(int nNumber);			//数字セット処理
	void SetMatrix(void);					//行列設定処理
	static CNumber *Create(int Digit,D3DXVECTOR3 OrderPosition);	//作成処理

private:
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャ格納変数
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		//バッファのポインタ
	void MakeVertex(int Digit);

	D3DXVECTOR3 Position;						//パーティクルのXY座標
	D3DXVECTOR3 Rot;					//角度
	D3DXVECTOR3 Scale;				//角度
	
	D3DXMATRIX mtxWorld;							//ワールド行列
	D3DXMATRIX mtxTrans;							//平行行列
	D3DXMATRIX mtxRot;							//回転行列
	D3DXMATRIX mtxScale;							//拡大行列
	D3DXMATRIX mtxInverse;						//逆行列

	static CRenderer *pRenderer;
	
};
/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif