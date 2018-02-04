/******************************************************************
***
***		メイン処理
***
***		main.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"
#include "manager.h"
#include "DebugFont.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"3d"	// ウインドウのキャプション名

/******************************************************************
プロトタイプ宣言
*******************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/******************************************************************
グローバル変数
*******************************************************************/
CManager *pManager = NULL;
/******************************************************************
メイン関数
*******************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//メモリを確保
	pManager = new CManager;

	//初期化処理
	pManager ->Init(hInstance,hWnd,TRUE);

	//分解能を設定
	timeBeginPeriod(1);

	//フレームカウント初期化
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime = 
		dwFPSLastTime = timeGetTime();

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	//0.5秒ごとに実行
			{
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//更新処理
				pManager -> Update();

				//描画処理
				pManager -> Draw();

				dwFrameCount++;
			}
		}
	}

	//レンダラーの破棄
	if(pManager != NULL)
	{
		//終了処理
		pManager -> Uninit();
		delete pManager;
		pManager = NULL;
	}
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

/******************************************************************
ウィンドウプロシージャ
*******************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		//ウィンドウが作られたとき
	case WM_CREATE:
		break;

		//ウィンドウが破棄されたとき
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//キー入力があったとき
	case WM_KEYDOWN:

		switch(wParam)
		{
			//ESCキーが押されたら
		case VK_ESCAPE:			
			DestroyWindow(hWnd);	//ウィンドウを破棄
			break;

		case VK_F5:

			break;
		}
		break;

		//上記に該当しない場合
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
