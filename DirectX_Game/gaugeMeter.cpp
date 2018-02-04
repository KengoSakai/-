/******************************************************************
***
***		ゲージ処理
***
***		Gauge.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "gaugeMeter.h"
#include "input.h"
#include "gaugeBox.h"
#include "DebugFont.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_LIFE (500.0f)

/******************************************************************
構造体定義（クラス）
*******************************************************************/

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
CGaugeMeter::CGaugeMeter()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CGaugeMeter::~CGaugeMeter()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CGaugeMeter::Initialize(float m_fLife)
{

	//座標設定
	Position.x = 420.0f;
	Position.y = 605.0f;
	Position.z = 0.0f;

	//幅、高さ
	WidthHeight.x = NUM_Gauge - 40.0f;
	WidthHeight.y = 40.0f;
	WidthHeight.z = 0.0f;

	//頂点色設定
	Color.r = 0.0f;
	Color.g = 255.0f;
	Color.b = 0.0f;
	Color.a = 255.0f;

	//体力設定
	Life = m_fLife;
	LifeGauge = m_fLife;

	//ゲージが減る速度
	GaugeRate = NUM_Gauge / m_fLife;

	//頂点作成処理
	CScene2D::Initialize();
}

/******************************************************************
終了処理関数
*******************************************************************/
void CGaugeMeter::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CGaugeMeter::Update(void)
{
	//頂点色を設定
	CScene2D::SetColor(Color);

	//体力が半分以下かつ３分の１より多いなら
	if (Life <= (LifeGauge / 2) && Life > (LifeGauge / 4))
	{
		Color.r = 255.0f;
	}

	//体力が４分の１以下なら
	else if (Life <= LifeGauge / 4)
	{
		Color.g = 0.0f;
	}

	else
	{

	}

	//体力が0より多いなら
	if (Life > 0)
	{
		//Life--;
		WidthHeight.x -= GaugeRate;
	}
}

/******************************************************************
描画処理関数
*******************************************************************/
void CGaugeMeter::Draw(void)
{
	CScene2D::Draw();
	CManager::GetDebugFont()->AddDebugFont("PlayerLife:", Life, 0, 120);
}

/******************************************************************
オブジェクト作成処理関数
*******************************************************************/
CGaugeMeter *CGaugeMeter::Create(float m_fLife)
{
	//ポインタ
	CGaugeMeter *pGaugeMeter;

	//メモリの確保（インスタンスの生成）
	pGaugeMeter = new CGaugeMeter;

	//初期化処理
	pGaugeMeter->Initialize(m_fLife);

	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_GAUGEMETER);
	
	//オブジェクトの型登録関数呼び出し
	pGaugeMeter->SetObjType(OBJTYPE_GAUGE);

	//テクスチャを割り当てる
	pGaugeMeter->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_GAUGEMETER));

	return pGaugeMeter;

}

void CGaugeMeter::SubGauge(float SubLife)
{
	//Life -= SubLife;

	for (int count = 0; count < SubLife; count++)
	{
		WidthHeight.x -= GaugeRate;
		CScene2D::SetPosition();
	}
}

