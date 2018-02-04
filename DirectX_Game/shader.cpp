/******************************************************************
***
***		シェーダ処理
***
***		shader.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "shader.h"
#include "camera.h"
/******************************************************************
マクロ定義
*******************************************************************/

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
CShader::CShader()
{
	pPixelShader = NULL;
	pVertexShader = NULL;
	ShadersConstantTable = NULL;
}

/******************************************************************
デストラクタ
*******************************************************************/
CShader::~CShader()
{

}
/******************************************************************
初期化処理関数
*******************************************************************/
void CShader::Initialize(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DVERTEXELEMENT9 VertexElem[3];
	IDirect3DVertexDeclaration9 *pDeclaration;
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX ShadersMatrix;
	D3DXMATRIX TransMatrix;
	D3DXMATRIX RotationMatrix;
	D3DXVECTOR3 Pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Rot(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Scale(1.0f, 1.0f, 1.0f);

	D3DXMatrixRotationZ(&WorldMatrix, 180.0f);
	//行列変換
	D3DXMatrixIdentity(&WorldMatrix);	//単位行列
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,
		D3DXToRadian(Rot.y),
		D3DXToRadian(Rot.x),
		D3DXToRadian(Rot.z));	//回転行列
	D3DXMatrixScaling(&ScaleMatrix, Scale.x, Scale.y, Scale.z);	//拡大行列
	D3DXMatrixTranslation(&TransMatrix, Pos.x, Pos.y, Pos.z);	//平行行列

	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &ScaleMatrix);
	WorldMatrix = RotationMatrix *ScaleMatrix *  TransMatrix;

	ShadersMatrix = WorldMatrix;//* CManager::GetCamera()->GetViewMatrix() * CManager::GetCamera()->GetProjectionMatrix();

	//頂点座標情報の宣言
	VertexElem[0].Stream = 0;
	VertexElem[0].Offset = 0;
	VertexElem[0].Type = D3DDECLTYPE_FLOAT3;
	VertexElem[0].Method = D3DDECLMETHOD_DEFAULT;
	VertexElem[0].Usage = D3DDECLUSAGE_POSITION;
	VertexElem[0].UsageIndex = 0;

	//頂点カラー情報の宣言
	VertexElem[1].Stream = 0;
	VertexElem[1].Offset = 12;
	VertexElem[1].Type = D3DDECLTYPE_D3DCOLOR;
	VertexElem[1].Method = D3DDECLMETHOD_DEFAULT;
	VertexElem[1].Usage = D3DDECLUSAGE_COLOR;
	VertexElem[1].UsageIndex = 0;

	//終端宣言
	VertexElem[2].Stream = 0xFF;
	VertexElem[2].Offset = 0;
	VertexElem[2].Type = D3DDECLTYPE_UNUSED;
	VertexElem[2].Method = 0;
	VertexElem[2].Usage = 0;
	VertexElem[2].UsageIndex = 0;

	pDevice->CreateVertexDeclaration(VertexElem, &pDeclaration);

	//頂点シェーダファイルをコンパイル
	D3DXCompileShaderFromFile(
		"VertexShader.hlsl",
		NULL,
		NULL,
		"main",
		"vs_3_0",
		0,
		&Code,		//複数用意
		&Error,
		&ShadersConstantTable);

	ShadersConstantTable->SetMatrix(pDevice, "WorldViewProjectionMatrix", &ShadersMatrix);

	//頂点シェーダを生成
	pDevice->CreateVertexShader((LPDWORD)Code->GetBufferPointer(), &pVertexShader);

	//ピクセルシェーダファイルをコンパイル
	D3DXCompileShaderFromFile(
		"PixelShader3D.hlsl",
		NULL,
		NULL,
		"main",
		"ps_3_0",
		0,
		&Code,		//複数用意
		&Error,
		&ShadersConstantTable);

	//ピクセルシェーダを生成
	pDevice->CreatePixelShader((LPDWORD)Code->GetBufferPointer(), &pPixelShader);
}

//終了処理
void CShader::Uninitialize(void)
{
	//ピクセルシェーダの開放
	if (pPixelShader != NULL)
	{
		pPixelShader->Release();
		pPixelShader = NULL;
	}

	//頂点シェーダの開放
	if (pPixelShader != NULL)
	{
		pPixelShader->Release();
		pPixelShader = NULL;
	}

	if (ShadersConstantTable != NULL)
	{
		ShadersConstantTable->Release();
		ShadersConstantTable = NULL;
	}
}

//シェーダ開始関数
void CShader::BeginShader(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点シェーダを設定
	pDevice->SetVertexShader(pVertexShader);

	//ピクセルシェーダを設定
	pDevice->SetPixelShader(pPixelShader);
}

//シェーダ終了処理
void CShader::EndShader(void)
{

}

//アセンブルシェーダー処理
void CShader::AssembleShader(void)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//	IDirect3DVertexShader9 *pVertexShaderHandler;	//頂点シェーダハンドラ
	IDirect3DPixelShader9 *pPixelShaderHandler;		//ピクセルシェーダハンドラ
	ID3DXBuffer *pShader;							//シェーダ命令格納バッファ
	ID3DXBuffer *pError;							//コンパイルエラー情報格納バッファ

													//頂点シェーダ配列の定義。
	const char VertexShader[] =
		"vs_1_1 \n"
		"dcl_position v0 \n"
		"dcl_color v1 \n"
		"m4x4 oPos, v0, c0 \n"
		"add oD0, v1, c4 \n";

	//ピクセルシェーダ配列の定義
	const char PixelShader[] =
		"ps_1_1\n"
		"def c0 , 0.2989f , 0.5866f , 0.1145f , 1.0f \n"	//彩度算出係数
		"tex t0 \n"											//テクスチャ0番使用
		"dp3 r0 , t0 , c0  \n"								//彩度Y算出（r.aに格納される）
		"mov r1 , r0.a \n"									//r0の各成分をYで埋める
		"lrp r0 , c1 , t0 , r1 \n";						//線形補間（v0+c1*(Y-v0)）

														//頂点シェーダのコンパイル命令
	D3DXAssembleShader(
		VertexShader,			//命令配列へのポインタ
		sizeof(VertexShader) - 1,	//命令文字数（-1はNULL文字を省くため）
		0,					//プリプロセッサ定義
		NULL,				//インクルード命令指定
		0,					//コンパイルオプション
		&pShader,			//シェーダバッファ
		&pError				//コンパイルエラーバッファ
	);

	//頂点シェーダの生成
	//pDevice->CreateVertexShader((DWORD*)pShader->GetBufferPointer(),&pVertexShaderHandler);

	//頂点シェーダに切り替え
	//pDevice->SetVertexShader(pVertexShaderHandler);

	//ピクセルシェーダのコンパイル命令
	D3DXAssembleShader(
		PixelShader,			//命令配列へのポインタ
		sizeof(PixelShader) - 1,	//命令文字数（-1はNULL文字を省くため）
		0,					//プリプロセッサ定義
		NULL,				//インクルード命令指定
		0,					//コンパイルオプション
		&pShader,			//シェーダバッファ
		&pError				//コンパイルエラーバッファ
	);

	//ピクセルシェーダの生成
	pDevice->CreatePixelShader((DWORD*)pShader->GetBufferPointer(), &pPixelShaderHandler);

	//ピクセルシェーダに切り替え
	pDevice->SetPixelShader(pPixelShaderHandler);

	//シェーダ命令バッファの開放
	if (pShader != NULL)
	{
		pShader->Release();
		pShader = NULL;
	}

	//エラーバッファの開放
	if (pError != NULL)
	{
		pError->Release();
		pError = NULL;
	}
}
