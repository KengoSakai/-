#include "manager.h"
#include "renderer.h"
#include "DebugFont.h"

CDebugFont::CDebugFont()
{
	pDebugFont = NULL;

}

CDebugFont::~CDebugFont()
{

}

void CDebugFont::Initialize(void)
{
#ifdef _DEBUG
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(
		pDevice,
		18,					//幅
		0,					//高さ
		0,					//フォントの太さ
		0,					//ミップマップの太さ
		FALSE,				//斜めかどうか
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,	//品質
		DEFAULT_PITCH,
		"Terminal",			//フォントの名前
		&pDebugFont			//ポインター
	);
#endif
}

void CDebugFont::Uninitialize(void)
{
	if (pDebugFont != NULL)
	{
		pDebugFont->Release();
		pDebugFont = NULL;
	}
}

void CDebugFont::AddDebugFont( char *AddDebugFont,float ObjectValue, int PositionX, int PositionY)
{
	char aString[256];
	sprintf(&aString[0], "%s:%f\n", AddDebugFont , ObjectValue);
	RECT rect = {
		PositionX,
		PositionY,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	};

	pDebugFont->DrawText(
		NULL,
		&aString[0],			//表示する文字
		-1,
		&rect,
		DT_LEFT,						//左詰め
		D3DCOLOR_RGBA(255, 255, 0, 255)	//色
	);
}
