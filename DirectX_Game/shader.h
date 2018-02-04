/******************************************************************
***
***		処理
***
***		.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _SHADER_H_
#define _SHADER_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define CUSTOM_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE|D3DFVF_TEX1)
/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CShader
{
public:

	typedef struct
	{
		float x, y, z;
		DWORD Color;
	}CUSTOM_VERTEX;

	typedef enum
	{
		TYPE_NONE = 0,
		PIXEEL_SHADER,
		VERTEX_SHADER
	}SHADER;

	CShader();
	~CShader();
	void Initialize(void);
	void Uninitialize(void);
	void AssembleShader(void);
	void BeginShader(void);
	void EndShader(void);

private:
	//シェーダハンドラ
	LPDIRECT3DPIXELSHADER9 pPixelShader;
	LPDIRECT3DVERTEXSHADER9 pVertexShader;

	ID3DXEffect *pEffect;
	LPD3DXBUFFER Error;
	LPD3DXBUFFER Code;
	LPD3DXCONSTANTTABLE ShadersConstantTable;
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif


