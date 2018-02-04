/******************************************************************
***
***		メッシュフィールド処理（ヘッダー）
***
***		MeshField.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MESHDRAW_H_
#define _MESHDRAW_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene.h"
#include "textureManager.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
クラス定義
*******************************************************************/
class CMeshDraw : public CScene
{
public:
	CMeshDraw();		//コンストラクタ
	~CMeshDraw() {}			//デストラクタ
	void Initialize(void);		//初期化処理
	void Uninitialize(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetMatrix(void);	//行列設定処理
	void BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture);				//テクスチャ読み込み処理
private:
	void MakeVertex(void);	//頂点作成処理
	void MakeIndex(void);	//インデックスバッファ設定処理

	LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;	//バッファポインタ
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;	//インデックスバッファポインタ
protected:
	D3DXVECTOR3 Position;		//座標
	D3DXVECTOR3 Rotate;			//角度
	D3DXVECTOR3 Scale;			//拡大率

	D3DXMATRIX RotateMatrix;
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX WorldMatrix;

};

#endif