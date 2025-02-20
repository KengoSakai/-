/******************************************************************
***
***		ミニマップ処理
***
***		miniMapPlayer.cpp
***
***		author: Kengo Sakai
***u************************************************************
インクルードファイル
*******************************************************************/
#include "scene2D.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CMiniMapPlayer : public CScene2D
{
public:
	CMiniMapPlayer();
	~CMiniMapPlayer(){}
	void Initialize(void);
	void Uninitalize(void);
	void Update(void);
	void Draw(void);
	static CMiniMapPlayer *Create(void);
private:

};
