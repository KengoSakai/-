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
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_GOAL,
		TYPE_TREE,
		TYPE_ITEM,
		TYPE_BUILDING,
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
