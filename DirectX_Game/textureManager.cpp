/******************************************************************
***
***		テクスチャ管理処理
***
***		textureManager.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "textureManager.h"

/******************************************************************
コンストラクタ
*******************************************************************/
CTextureManager::CTextureManager()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//リストの初期化
		pTextureList[nCnt] = NULL;

		//ポインタの初期化
		pTexture[nCnt] = NULL;
	}
}

/******************************************************************
初期化処理
*******************************************************************/
void CTextureManager::Initialize(void)
{
	//テクスチャリスト
	pTextureList[TYPE_MINIMAPPLAYER] = "data/TEXTURE/particle002.png";
	pTextureList[TYPE_PARTICLE] = "data/TEXTURE/particle002.png";
	pTextureList[TYPE_SKY] = "data/TEXTURE/sky001.jpg";
	pTextureList[TYPE_FIELD] = "data/TEXTURE/field000.png";
	pTextureList[TYPE_GAUGEMETER] = "data/TEXTURE/gauge001.png";
	pTextureList[TYPE_GAUGEBOX] = "data/TEXTURE/gauge002.png";
	pTextureList[TYPE_NUMBER] = "data/TEXTURE/score_000.png";
	pTextureList[TYPE_STARTBUTTON] = "data/TEXTURE/startButton000.png";
	pTextureList[TYPE_TREE] = "data/TEXTURE/Tree.jpg";
	pTextureList[TYPE_TITLELOGO] = "data/TEXTURE/TitleLogo.png";
}

/******************************************************************
終了処理関数
******************************************************************/
void CTextureManager::Uninitialize(void)
{
	for (int TextureCount = 0; TextureCount < TYPE_MAX; TextureCount++)
	{
		if (pTexture[TextureCount] != NULL)
		{
			//テクスチャインターフェースの開放
			pTexture[TextureCount]->Release();
			pTexture[TextureCount] = NULL;
		}
	}
}

/******************************************************************
テクスチャ読み込み処理関数
******************************************************************/
void CTextureManager::LoadTexture(TEXTURE_TYPE TextureType)
{
	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//一度でも読み込まれたか
	if (pTexture[TextureType] == NULL)
	{
		// テクスチャの生成
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pTextureList[TextureType], &pTexture[TextureType])))	//エラーの場合
		{
			pTexture[TextureType] = NULL;

			MessageBox(NULL, "画像を読み込めませんでした。%s,&TextureType", "エラーメッセージ", MB_OK);					//起動時に表示するタイトルとメッセージ
			//PostQuitMessage(0);
		}
	}
}

/******************************************************************
テクスチャ取得処理関数
******************************************************************/
LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(TEXTURE_TYPE TextureType)
{
	return pTexture[TextureType];
}


