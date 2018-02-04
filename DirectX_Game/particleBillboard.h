/******************************************************************
***
***		パーティクルビルボード処理
***
***		particleBillboard.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _PARTICLEBILLBORD_H_
#define _PARTICLEBILLBORD_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "particleManager.h"
#include "textureManager.h"
/******************************************************************
マクロ定義
*******************************************************************/


/******************************************************************
構造体定義
*******************************************************************/
class CParticleBillboard : public CParticleManager
{
public:
	CParticleBillboard();				//コンストラクタ
	~CParticleBillboard();			//デストラクタ
	void Initialize(void);	//初期化処理
	void Uninitialize(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetBillboard(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ読み込み処理	
	void SetColor(D3DXCOLOR Color);

	LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ

private:
	void MakeVertex(void);							//頂点作成処理

	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファポインタ
protected:
	void SetRotate(D3DXVECTOR3 Position,float Size);

	D3DXMATRIX RotateMatrix;
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX InverseMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX WorldMatrix;

	D3DXCOLOR Color;
	float Velocity;
	float Size;
	D3DXVECTOR3 Rotate;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Normal;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 EmitterPosition;
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif
