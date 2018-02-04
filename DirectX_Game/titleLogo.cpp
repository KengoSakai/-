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
#include "titleLogo.h"

CTitleLogo::CTitleLogo()
{

}


void CTitleLogo::Initialize(void)
{
	Position = D3DXVECTOR3(400.0f, 100.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
	CScene2D::Initialize();
}

void CTitleLogo::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

void CTitleLogo::Update(void)
{
}

void CTitleLogo::Draw(void)
{
	CScene2D::Draw();
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CTitleLogo *CTitleLogo::Create(void)
{
	//ポインタ宣言
	CTitleLogo *pTitleLogo;

	//インスタンス生成
	pTitleLogo = new CTitleLogo;

	//初期化処理
	pTitleLogo->Initialize();

	pTitleLogo->SetObjType(OBJTYPE_TITLELOGO);
	
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_TITLELOGO);

	pTitleLogo->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_TITLELOGO));

	return pTitleLogo;
}
