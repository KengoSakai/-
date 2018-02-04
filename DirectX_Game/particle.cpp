/******************************************************************
***
***		パーティクル処理
***
***		particle.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "camera.h"
#include "DebugFont.h"
/******************************************************************
マクロ定義
******************************************************************/
#define SPEED (0.1f)
#define FADE_RATE (2.0f)
#define SIZE (5.0f)
/******************************************************************
構造体またはクラス定義
*******************************************************************/

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/
CRenderer *CParticle::m_pRenderer = NULL;

/******************************************************************
コンストラクタ
*******************************************************************/
CParticle::CParticle()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CParticle :: ~CParticle()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CParticle::Initialize(D3DXVECTOR3 Pos)
{
	//パーティクル初期化
	CParticleBillboard::Initialize();

	Color = D3DXCOLOR(255.0f, 155.0f, 55.0f, 255.0f);
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Size = SIZE;
	CParticleBillboard::SetRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f), Size);

	EmitterPosition = Pos;
	Rotate.x = cosf((float)rand());
	Rotate.y = sinf((float)rand());
	Rotate.z = cosf((float)rand());
	
}

/******************************************************************
終了処理関数
*******************************************************************/
void CParticle::Uninitialize(void)
{
	//オブジェクトの破棄
	CParticleBillboard::Uninitialize();
}

/******************************************************************
更新処理関数z
*******************************************************************/
void CParticle::Update(void)
{
	EmitterPosition += Rotate * SPEED;
	//EmitterPosition.y += 0.5f;
	//α値を下げる
	Color.a -= FADE_RATE;

	CParticleBillboard::SetColor(Color);
	
	//α値が0未満になったら
	if (Color.a < 0)
	{
		//パーティクルの破棄
		Uninitialize();
	}
}

/******************************************************************
描画処理関数
*******************************************************************/
void CParticle::Draw(void)
{
	//αブレンディング
	CManager::GetRenderer()->SetAlphaBlend();

	//ビルボード設定
	CParticleBillboard::SetBillboard();
	
	//描画
	CParticleBillboard::Draw();
	
	//αブレンディング無効
	CManager::GetRenderer()->SetDefaultBrend();
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CParticle *CParticle::Create(D3DXVECTOR3 EmitterPosition)
{
	//オブジェクトポインタ
	CParticle *pParticle;

	//インスタンスの生成
	pParticle = new CParticle;

	//初期化関数呼び出し
	pParticle->Initialize(EmitterPosition);

	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_PARTICLE);

	//テクスチャを割り当てる
	pParticle->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_PARTICLE));

	pParticle->SetObjType(OBJTYPE_PARTICLE);
	return pParticle;
}
