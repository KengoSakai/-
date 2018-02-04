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
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene2D.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CStartButton : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	~CStartButton();
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CStartButton *Create(void);
private:
	CStartButton();
	FADE FadeState;
protected:
};

#endif
