#pragma once
/******************************************************************
***
***		処理
***
***		.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene2D.h"

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CTitleLogo : public CScene2D
{
public:
	~CTitleLogo() {}	//デストラクタ
	void Initialize(void);		//初期化処理
	void Uninitialize(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static CTitleLogo *Create(void);

private:
	CTitleLogo();			//コンストラクタ
protected:

};

#endif
