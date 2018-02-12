/******************************************************************
***
***		モデル管理処理
***
***		modelManager.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_
/******************************************************************
インクルードファイル
*******************************************************************/

/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CModelManager
{
public:
	typedef enum
	{
		TYPE_PLAYER=0,
		TYPE_ENEMY,
		TYPE_GOAL,
		TYPE_TREE,
		TYPE_ITEM,
		TYPE_BUILDING,
		TYPE_BODY,
		TYPE_HEAD,
		TYPE_RIGHT_ARM,
		TYPE_LEFT_ARM,
		TYPE_RIGHT_LEG,
		TYPE_LEFT_LEG,
		TYPE_RIGHT_HAND,
		TYPE_LEFT_HAND,
		TYPE_RIGHT_FOOT,
		TYPE_LEFT_FOOT,
		TYPE_MAX
	}MODEL_TYPE;

	CModelManager();			//コンストラクタ
	~CModelManager() {}			//デストラクタ
	void Initialize(void);
	void Unitialize(void);
	void LoadModel(MODEL_TYPE OrderModelType);	//モデル取得処理
	LPD3DXMESH GetMesh(MODEL_TYPE OrderModelType);
	DWORD GetNumMaterials(MODEL_TYPE OrderModelType);
	LPD3DXBUFFER GetMaterialBuffer(MODEL_TYPE OrderModelType);
private:
	char *pModelList[TYPE_MAX];	//モデルリスト
	LPD3DXMESH pMesh[TYPE_MAX];			//メッシュ
	LPD3DXBUFFER pMatBuff[TYPE_MAX];		//バッファポインタ
	DWORD NumMaterials[TYPE_MAX];		//要素数
};

/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/

/******************************************************************
コンストラクタ
*******************************************************************/
#endif
