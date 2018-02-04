/******************************************************************
***
***		テクスチャ管理処理
***
***		textureManager.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"

/******************************************************************
マクロ定義
*******************************************************************/


/******************************************************************
クラス定義
*******************************************************************/
class CTextureManager
{
public:
	typedef enum
	{
		TYPE_NONE=0,
		TYPE_MINIMAPPLAYER,
		TYPE_FIELD,
		TYPE_WALL,
		TYPE_SKY,
		TYPE_PARTICLE,
		TYPE_SCORE,
		TYPE_TIME,
		TYPE_GAUGEBOX,
		TYPE_GAUGEMETER,
		TYPE_NUMBER,
		TYPE_STARTBUTTON,
		TYPE_TREE,
		TYPE_TITLELOGO,
		TYPE_THUNDER,
		TYPE_FIRE,
		TYPE_SPLASH,
		TYPE_HITEFFECT,
		TYPE_SMOKE,
		TYPE_CLOUD,
		TYPE_BUILDING,
		TYPE_MAX
	}TEXTURE_TYPE;

	CTextureManager();				//コンストラクタ
	~CTextureManager() {}			//デストラクタ
	void Initialize(void);
	void Uninitialize(void);
	void LoadTexture(TEXTURE_TYPE TextureType);
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE TextureType);	//テクスチャ取得関数
private:
	LPDIRECT3DTEXTURE9 pTexture[TYPE_MAX];
	char *pTextureList[TYPE_MAX];
protected:
};

#endif