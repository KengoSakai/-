/******************************************************************
***
***		3Dモデル処理
***
***		model.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MODEL_H_
#define _MODEL_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene.h"
#include "modelManager.h"
#include "textureManager.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CModel : public CScene
{
public:
	CModel();					//コンストラクタ
	~CModel();					//デストラクタ
	void Initialize(void);
	void Uninitialize(void);	//終了処理
	void Update(void);
	void Draw(void);			//描画処理
	void DrawShadow(void);
	void BindBuff(LPD3DXBUFFER pOrderMatBuff);						//バッファ情報読み込み処理
	void BindMesh(LPD3DXMESH pOrderMesh);
	void BindMaterials(DWORD OrderNumMaterials);					//要素数読み込み処理
	void BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture);
	void SetMatrix(void);

private:
	LPD3DXMESH pMesh;			//メッシュ
	LPD3DXBUFFER pMaterialBuffer;	//バッファポインタ
	DWORD NumMaterials;	//要素数
	LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ
	void SetModel(void);

protected:
	//座標情報
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotate;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Vector;

	D3DXMATRIX RotateMatrix;
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX InverseMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ShadowMatrix;

};
#endif