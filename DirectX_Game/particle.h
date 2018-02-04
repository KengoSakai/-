/******************************************************************
***
***		パーティクル処理
***
***		particle.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "particleBillboard.h"
/******************************************************************
マクロ定義
*******************************************************************/
class CRenderer;
/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CParticle : public CParticleBillboard
{
public:
	CParticle();	//コンストラクタ
	~CParticle();	//デストラクタ
	void Initialize(D3DXVECTOR3 Pos);	//初期化処理
	void Uninitialize(void);			//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理
	//静的メンバー関数
	static CParticle *Create(D3DXVECTOR3 EmitterPosition);	//オブジェクト生成処理

private:
	//静的メンバー変数
	static CRenderer *m_pRenderer;
};
#endif
