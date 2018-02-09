/******************************************************************
***
***		ゲージ処理
***
***		timeBox.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _TIMEBOX_H_
#define _TIMEBOX_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "scene2D.h"

/******************************************************************
クラス定義
*******************************************************************/
class CTimeBox :public CScene2D
{
public:
	~CTimeBox() {}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CTimeBox *Create(void);

private:
	CTimeBox();
};
#endif
