/******************************************************************
***
***		オブジェクト管理処理
***
***		scene.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
/******************************************************************
インクルードファイル
*******************************************************************/
#include "main.h"

/******************************************************************
マクロ定義
*******************************************************************/
#define NUM_OBJECT (1000)

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0 ,
		OBJTYPE_PARTICLE ,
		OBJTYPE_PLAYER,
		OBJTYPE_MINIMAPPLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BG,
		OBJTYPE_FIELD,
		OBJTYPE_WALL,
		OBJTYPE_DOME,
		OBJTYPE_GAUGE,
		OBJTYPE_START,
		OBJTYPE_GOAL,
		OBJTYPE_FADE,
		OBJTYPE_TITLELOGO,
		OBJTYPE_TITLEBUTTON,
		OBJTYPE_MINIMAP,
		OBJTYPE_BUILDING,
		OBJTYPE_TIME,
		OBJTYPE_SCORE,
		OBJTYPE_ITEM,
		OBJTYPE_BULLET,
		OBJTYPE_CUBECOLLIDER,
		OBJTYPE_CLOUD,
		OBJTYPE_TARGET,
		OBJTYPE_OTHERPLAYERSCORE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene ();							//コンストラクタ
	virtual ~CScene ();					//デストラクタ
	virtual void Initialize (void) = 0;	//初期化処理
	virtual void Uninitialize (void) = 0;		//終了処理
	virtual void Update (void) = 0;		//更新処理
	virtual void Draw (void) = 0 ;		//描画処理

	static void UpdateAll(void);		//オブジェクト全更新処理
	static void DrawAll (void);			//オブジェクト全描画処理
	static void ReleaseAll(void);		//オブジェクト全破棄処理

	void SetObjType(OBJTYPE type);											//オブジェクトの種類格納関数
	OBJTYPE GetObjType (void){return  m_objType;}							//オブジェクトの種類取得関数
	static CScene *GetScene(int nIdxScene){return  m_apScene[nIdxScene];}	//オブジェクトの情報取得関数
	
private:
	static CScene *m_apScene[NUM_OBJECT];	//オブジェクトの最大数
	static int m_nNumScene;			//オブジェクトの総数
	
	//変数宣言
	int m_nID;				//オブジェクト固有ID
	OBJTYPE m_objType;		//オブジェクトの種類格納変数

	protected:
	 void Release(void);				//オブジェクト破棄処理
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************/
#endif