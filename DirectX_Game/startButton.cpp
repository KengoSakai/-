/******************************************************************
***
***		処理
***
***		.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "startButton.h"
/******************************************************************
マクロ定義
*******************************************************************/
#define FADE_RATE (2.0f)

CStartButton::CStartButton()
{

}

CStartButton::~CStartButton()
{

}

void CStartButton::Initialize(void)
{
	Position = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	FadeState = FADE_IN;
	CScene2D::Initialize();
}

void CStartButton::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

void CStartButton::Update(void)
{
	CScene2D::SetColor(Color);

	if (FadeState == FADE_NONE)
	{
		return;
	}

	if (FadeState == FADE_IN)
	{
		//α値を下げていく
		Color.a -= FADE_RATE;

		//フェード終了
		if (Color.a <= 0.0f)
		{
			//α値を0にする
			Color.a = 0.0f;

			//フェードアウトの状態へ
			FadeState = FADE_OUT;
			return;
		}
	}

	else if (FadeState == FADE_OUT)
	{
		Color.a += FADE_RATE;

		if (Color.a > 255.0f)
		{
			Color.a = 255.0f;
			FadeState = FADE_IN;
			return;
		}

	}

	else
	{
		return;
	}

}

void CStartButton::Draw(void)
{
	CScene2D::Draw();
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CStartButton *CStartButton::Create(void)
{
	//ポインタ宣言
	CStartButton *pStartButton;

	//インスタンス生成
	pStartButton = new CStartButton;

	//初期化処理
	pStartButton->Initialize();

	pStartButton->SetObjType(OBJTYPE_TITLEBUTTON);
	
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_STARTBUTTON);
	
	pStartButton->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_STARTBUTTON));

	return pStartButton;
}
