#include "miniMap.h"
#include "manager.h"
#include "renderer.h"

CMiniMap::CMiniMap()
{
	Position = D3DXVECTOR3(900.0f, 30.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(200.0f,200.0f,200.0f);
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 125.0f);
}

void CMiniMap::Initialize(void)
{
	CScene2D::Initialize();
	CScene2D::SetColor(Color);
}

void CMiniMap::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

void CMiniMap::Update(void)
{

}

void CMiniMap::Draw(void)
{	
	CScene2D::Draw();
}

CMiniMap *CMiniMap::Create(void)
{
	CMiniMap *pMiniMap;

	pMiniMap = new CMiniMap;

	pMiniMap->Initialize();

	pMiniMap->SetObjType(OBJTYPE_MINIMAP);

	pMiniMap->BindTexture(NULL);

	return pMiniMap;
}
