#include "scene.h"
#include "modelManager.h"
#include "textureManager.h"

class CMotionModel : public CScene
{
public:
	typedef enum
	{
		BODY=0,
		HEAD,
		ARM_RIGHT,
		ARM_LEFT,
		HAND_RIGHT,
		HAND_LEFT,
		LEG_RIGHT,
		LEG_LEFT,
		FOOT_RIGHT,
		FOOT_LEFT,
		PARTS_MAX
	}PARTS;

	CMotionModel();
	~CMotionModel(){}
	void Initialize(void);
	void Uninitialize(void);	//終了処理
	void Update(void);
	void Draw(void);			//描画処理
	void DrawShadow(void);
	void BindBuff(LPD3DXBUFFER pOrderMatBuff, PARTS ModelParts);						//バッファ情報読み込み処理
	void BindMesh(LPD3DXMESH pOrderMesh, PARTS ModelParts);
	void BindMaterials(DWORD OrderNumMaterials, PARTS ModelParts);					//要素数読み込み処理
	void BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture);
	void SetMatrix(void);

private:
	LPD3DXMESH pMesh[PARTS_MAX];			//メッシュ
	LPD3DXBUFFER pMaterialBuffer[PARTS_MAX];	//バッファポインタ
	DWORD NumMaterials[PARTS_MAX];	//要素数
	LPDIRECT3DTEXTURE9 pTexture;		//テクスチャポインタ
	
protected:
	//座標情報
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotate;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Vector;

	D3DXMATRIX RotateMatrix;
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ShadowMatrix;

	PARTS ParentParts[PARTS_MAX];
};
