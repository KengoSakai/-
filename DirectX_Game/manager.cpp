/******************************************************************
***
***		ゲーム処理
***
***		manager.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "DebugFont.h"
#include "camera.h"
#include "fade.h"
#include "light.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "modelManager.h"
#include "textureManager.h"

/******************************************************************
グローバル変数
*******************************************************************/
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CSceneManager *CManager::pSceneManager = NULL;
CModelManager *CManager::pModelManager = NULL;
CTextureManager *CManager::pTextureManager = NULL;
#ifdef _DEBUG
	CDebugFont *CManager::pDebugFont = NULL;
#endif
	CFade *CManager::pFade = NULL;
/******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CManager :: CManager ()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CManager :: ~CManager ()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
HRESULT CManager :: Init (HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	//レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer -> Init(hWnd , bWindow);

	//キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard -> Init(hInstance , hWnd);

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera -> Init();

	//ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

#ifdef _DEBUG

	//デバッグフォントの生成
	pDebugFont = new CDebugFont;
	pDebugFont->Initialize();
#endif

	//モデル管理クラスの生成
	pModelManager = new CModelManager;
	pModelManager->Initialize();

	//テクスチャ管理クラスの生成
	pTextureManager = new CTextureManager;
	pTextureManager->Initialize();

	//シーンの生成
	pSceneManager = new CSceneManager;
	pSceneManager->Initialize();

	//フェードの生成
	pFade = pFade->Create();

	return S_OK;
}

/******************************************************************
終了処理関数
*******************************************************************/
void CManager :: Uninit (void)
{
	//ライトの破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//モデル管理クラスの破棄
	if(pModelManager!=NULL)
	{
		pModelManager->Unitialize();
		delete pModelManager;
		pModelManager = NULL;
	}

	//テクスチャ管理クラスの破棄
	if (pTextureManager!=NULL)
	{
		pTextureManager->Uninitialize();
		delete  pTextureManager;
		pTextureManager = NULL;
	}

	//キーボードの破棄
	if(m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//カメラの破棄
	if(m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

#ifdef _DEBUG

	//デバッグフォントの破棄
	if (pDebugFont != NULL)
	{
		pDebugFont->Uninitialize();
		delete pDebugFont;
		pDebugFont = NULL;
	}
#endif

	//シーンの破棄
	if(pSceneManager != NULL)
	{
		pSceneManager->Uninitalize();
		delete pSceneManager;
		pSceneManager = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

/******************************************************************
更新処理関数
*******************************************************************/
void CManager :: Update (void)
{
#ifdef _DEBUG

#endif
	//オブジェクトの更新
	m_pRenderer-> Update();

	//キーボードの更新
	m_pInputKeyboard -> Update();
	
	//カメラの更新
	m_pCamera->Update();
	
	//ライトの更新
	m_pLight->Update();
	
	//シーンの更新
	pSceneManager->Update();
}

/******************************************************************
描画処理関数
*******************************************************************/
void CManager :: Draw (void)
{
	//オブジェクト描画
	m_pRenderer -> Draw();	
#ifdef _DEBUG
	
#endif
}


