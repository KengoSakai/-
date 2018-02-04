#include "manager.h"
#include "cloud.h"
#include "renderer.h"

#define SIZE (10.0f)

CCloud::CCloud()
{

}

void CCloud::Initialize(void)
{
	Size = SIZE;
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 125.0f);

	CScene3D::Initialize();

	int count = 0;
	count = rand() % 4;
	if (count == 0)
	{
		Position = D3DXVECTOR3(D3DXVECTOR3((float)(rand() % 600), 300.0f, (float)(rand() % 600)));
	}

	else if (count == 1)
	{
		Position = D3DXVECTOR3((float)(rand() % 600)*-1, 200.0f, (float)(rand() % 600)*-1);
	}

	else if (count == 2)
	{
		Position = D3DXVECTOR3((float)(rand() % 600), 200.0f, (float)(rand() % 600)*-1);
	}

	else if (count == 3)
	{
		Position = D3DXVECTOR3((float)(rand() % 600)*-1, 200.0f, (float)(rand() % 600));
	}

	else
	{
		Position = D3DXVECTOR3((float)(rand() % 600)*-1, 200.0f, (float)(rand() % 600));
	}
	Rotate = D3DXVECTOR3(D3DXToRadian(270.0f), 0.0f, 0.0f);
	Scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
}

void CCloud::Uninitialize(void)
{
	CScene3D::Uninitialize();
}

void CCloud::Update(void)
{

}

void CCloud::Draw(void)
{
	//αブレンディング
	CManager::GetRenderer()->SetzBuff();

	//CManager::GetRenderer()->SetAlphaBlend();

	CScene3D::SetBillboard();
	CScene3D::Draw();


	//αブレンディング無効
	//CManager::GetRenderer()->SetDefaultBrend();
}

CCloud *CCloud::Create(void)
{
	CCloud *pCloud;
	pCloud = new CCloud;
	pCloud->Initialize();
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_PARTICLE);
	pCloud->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_PARTICLE));
	pCloud->SetObjType(OBJTYPE_CLOUD);
	return pCloud;
}
