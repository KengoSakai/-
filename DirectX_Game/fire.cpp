/******************************************************************
***
***		炎エフェクト処理
***
***		fire.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "renderer.h"
#include "fire.h"

/******************************************************************
定数定義
*******************************************************************/
#define SIZE (5.0f)
#define FADE_RATE (5.0f)
#define SPEED (0.1f)

/******************************************************************
コンストラクタ
*******************************************************************/
CFire::CFire()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CFire::Initialize(D3DXVECTOR3 OrderPosition)
{
	//頂点バッファの初期化
	CParticleBillboard::Initialize();

	//角度
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	OrderPosition.y = 5.0f;

	//拡大率
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//サイズ
	Size = SIZE;

	//頂点バッファを再設定
	CParticleBillboard::SetRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f), Size);

	//エミッター
	EmitterPosition = OrderPosition;
	
	//角度の設定
	Rotate.x = cosf((float)rand());
	Rotate.y = sinf((float)rand());
	Rotate.z = cosf((float)rand());

	//色の初期化
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
}

/******************************************************************
終了処理関数
*******************************************************************/
void CFire::Uninitialize(void)
{
	//オブジェクトの破棄
	CParticleBillboard::Uninitialize();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CFire::Update(void)
{
	//エミッターの移動
	EmitterPosition += Rotate * SPEED;

	//α値の減算
	Color.a -= FADE_RATE;
	
	//頂点バッファの色設定
	SetColor(Color);

	if (Color.a < 0.0f)
	{
		//終了処理
		Uninitialize();
	}
}

/******************************************************************
描画処理関数
*******************************************************************/
void CFire::Draw(void)
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
CFire *CFire::Create(D3DXVECTOR3 OrderPosition)
{
	//オブジェクトポインタ
	CFire *pFire;

	//インスタンスの生成
	pFire = new CFire;

	//初期化
	pFire->Initialize(OrderPosition);

	//テクスチャ読み込み
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_PARTICLE);

	pFire->SetObjType(OBJTYPE_FIRE);

	//テクスチャを描画クラスに設定
	pFire->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_PARTICLE));

	return pFire;
}
