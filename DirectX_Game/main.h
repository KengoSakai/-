/******************************************************************
***
***		メイン処理
***
***		main.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************
インクルードファイル
*******************************************************************/
#include "windows.h"
#include "d3dx9.h"
#include <stdio.h>

/******************************************************************
ライブラリファイル
*******************************************************************/
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XInput.h>
#include <XAudio2.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib,"dinput8.lib")

/******************************************************************
マクロ定義
*******************************************************************/
#define SCREEN_WIDTH (1280)	//ウィンドウの幅
#define SCREEN_HEIGHT (720)	//ウィンドウの高さ

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
	
//2D用頂点構造体
	typedef struct
	{
		D3DXVECTOR3 pos;	// 頂点座標
		float rhw;			// 座標変換用係数(1.0fで固定)
		D3DCOLOR col;		// 頂点カラー
		D3DXVECTOR2 tex;	// テクスチャ座標
	} VERTEX_2D;



//3D用頂点構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		
		D3DXVECTOR3 normal;
		D3DCOLOR color;
		D3DXVECTOR2 tex;
	}VERTEX_3D;
#endif
