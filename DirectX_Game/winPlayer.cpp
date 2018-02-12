#include "manager.h"
#include "winPlayer.h"

CWinPlayer::CWinPlayer()
{
	Position = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(600.0f, 300.0f, 0.0f);
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
}

void CWinPlayer::Initialize(void)
{
	CScene2D::Initialize();
}

void CWinPlayer::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

void CWinPlayer::Update(void)
{

}

void CWinPlayer::Draw(void)
{
	CScene2D::Draw();
}

CWinPlayer *CWinPlayer::Create(OBJTYPE WinObjtype)
{
	CWinPlayer *pWinPlayer;

	pWinPlayer = new CWinPlayer;

	pWinPlayer->Initialize();

	pWinPlayer->SetObjType(OBJTYPE_WINPLAYER);

	if (WinObjtype==OBJTYPE_PLAYER)
	{
		CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_PLAYERWIN);
		pWinPlayer->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_PLAYERWIN));
	}

	else
	{
		CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_ENEMYWIN);
		pWinPlayer->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_ENEMYWIN));
	}
	return pWinPlayer;
}