/******************************************************************
***
***		ゲーム処理
***
***		manager.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MANAGER_H_
#define _MANAGER_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"
#include "input.h"
#include "xBoxInput.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
前方宣言
*******************************************************************/
class CRenderer;
class CInputKeyboard;
class CCamera;
class CDebugFont;
class CLight;
class CSceneManager;
class CModelManager;
class CTextureManager;
class CFade;
class CShader;
/******************************************************************
構造体定義（クラス）
*******************************************************************/
class CManager
{
public:
	CManager ();			//コンストラクタ
	~CManager ();			//デストラクタ
	HRESULT Init (HINSTANCE hInstance,
		HWND hWnd,
		BOOL bWindow);		//初期化処理
	void Uninit (void);		//終了処理
	void Update (void);		//更新処理
	void Draw (void);		//描画処理

	//インライン関数
	static CRenderer *GetRenderer(void){return m_pRenderer;}
	static CInputKeyboard *GetInputKeyboard(void){return m_pInputKeyboard;}
	static CCamera *GetCamera(void){return m_pCamera;}
	static CDebugFont *GetDebugFont(void) { return pDebugFont; }
	static CModelManager *GetModelManager(void) { return pModelManager; }
	static CTextureManager *GetTextureManager(void) { return pTextureManager; }
	static CLight *GetLight(void) { return m_pLight; }
	static CSceneManager *GetSceneManager(void) { return pSceneManager; }
	static CFade *GetFade(void) { return pFade; }
	static CXBoxInput *GetXBoxInput(void) { return pXBoxInput; }
	static CShader *GetShader(void) { return pShader; }
private:

protected:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CSceneManager *pSceneManager;
	static CDebugFont *pDebugFont;
	static CModelManager *pModelManager;
	static CTextureManager *pTextureManager;
	static CFade *pFade;
	static CXBoxInput *pXBoxInput;
	static CShader *pShader;
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif