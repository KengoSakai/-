#include "manager.h"
#include "gameEnd.h"

CGameEnd::CGameEnd()
{
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_GAMEFINISH);

	Position = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(600.0f, 200.0f, 0.0f);
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
}

void CGameEnd::Initialize(void)
{
	CScene2D::Initialize();
}

void CGameEnd::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

void CGameEnd::Update(void)
{

}

void CGameEnd::Draw(void)
{
	CScene2D::Draw();
}

CGameEnd *CGameEnd::Create(void)
{
	CGameEnd *pGameEnd;

	pGameEnd = new CGameEnd;

	pGameEnd->Initialize();

	pGameEnd->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_GAMEFINISH));

	pGameEnd->SetObjType(OBJTYPE_GAMEEND);

	return pGameEnd;
}
