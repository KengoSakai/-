#pragma once
/******************************************************************
***
***		ゲージ処理
***
***		GaugeMeter.h
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#ifndef _GaugeMETER_H_
#define _GaugeMETER_H_

/******************************************************************
マクロ定義
*******************************************************************/
#include "scene2D.h"

/******************************************************************
構造体定義（クラス）
*******************************************************************/
class CGaugeMeter : public CScene2D
{
public:
	CGaugeMeter();
	~CGaugeMeter();
	void Initialize(float m_fLife);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CGaugeMeter *Create(float m_fLife);
	void SubGauge(float SubLife);
private:
	float Life;		//体力
	float LifeGauge;
	float GaugeRate;	//1ダメージに対して減っていく量
};
#endif
