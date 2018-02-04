/******************************************************************
***
***		パーティクルのオブジェクト管理処理
***
***		particleManager.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h" 
/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_PARTICLE (1000)		//パーティクルの数	
/******************************************************************
クラス定義
*******************************************************************/
class CParticleManager
{
public:

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PARTICLE,
		OBJTYPE_FIRE,
		OBJTYPE_MAX
	}OBJTYPE;

	CParticleManager();				//コンストラクタ
	~CParticleManager();			//デストラクタ

	//純粋仮想関数
	virtual void Initialize(void) = 0;	//初期化処理
	virtual void Uninitialize(void) = 0;	//終了処理
	virtual void Update(void) = 0;	//更新処理
	virtual void Draw(void) = 0;		//描画処理

	static void UpdateAll(void);		//オブジェクト全更新処理
	static void DrawAll (void);			//オブジェクト全描画処理
	static void ReleaseAll(void);		//オブジェクト全破棄処理
	void SetObjType(OBJTYPE type);											//オブジェクトの種類格納関数

private:
	static CParticleManager *m_apParticle[NUM_PARTICLE];	//オブジェクトの最大数
	static int m_nNumParticle;			//オブジェクトの総数

	//変数宣言
	int m_nID;				//オブジェクト固有ID
	OBJTYPE ObjType;		//オブジェクトの種類格納変数

protected:
	 void Release(void);				//オブジェクト破棄処理
};
#endif
