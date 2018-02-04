/******************************************************************
***
***		爆破処理
***
***		exprode.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "exprode.h"
#include "manager.h"
#include "renderer.h"

/******************************************************************
定数定義
*******************************************************************/
#define SIZE (5.0f)
#define FADE_RATE (2.0f)
#define SPEED (0.5f)

/******************************************************************
コンストラクタ
*******************************************************************/
CExprode::CExprode()
{

}

/******************************************************************
初期化処理
*******************************************************************/
void CExprode::Initialize(D3DXVECTOR3 OrderPosition)
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
終了処理
*******************************************************************/
void CExprode::Uninitialize(void)
{
	//オブジェクトの破棄
	CParticleBillboard::Uninitialize();
}

/******************************************************************
更新処理
*******************************************************************/
void CExprode::Update(void)
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
描画処理
*******************************************************************/
void CExprode::Draw(void)
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
オブジェクト生成処理
*******************************************************************/
CExprode *CExprode::Create(D3DXVECTOR3 OrderPosition)
{
	CExprode *pExprode;


	//インスタンス生成
	pExprode = new CExprode;

	//初期化
	pExprode->Initialize(OrderPosition);

	//テクスチャ設定
	pExprode->BindTexture(NULL);

	pExprode->SetObjType(OBJTYPE_PARTICLE);

	return pExprode;
}