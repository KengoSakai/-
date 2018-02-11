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
	void Uninitialize(void);	//�I������
	void Update(void);
	void Draw(void);			//�`�揈��
	void DrawShadow(void);
	void BindBuff(LPD3DXBUFFER pOrderMatBuff, PARTS ModelParts);						//�o�b�t�@���ǂݍ��ݏ���
	void BindMesh(LPD3DXMESH pOrderMesh, PARTS ModelParts);
	void BindMaterials(DWORD OrderNumMaterials, PARTS ModelParts);					//�v�f���ǂݍ��ݏ���
	void BindTexture(LPDIRECT3DTEXTURE9 pOrderTexture);
	void SetMatrix(void);

private:
	LPD3DXMESH pMesh[PARTS_MAX];			//���b�V��
	LPD3DXBUFFER pMaterialBuffer[PARTS_MAX];	//�o�b�t�@�|�C���^
	DWORD NumMaterials[PARTS_MAX];	//�v�f��
	LPDIRECT3DTEXTURE9 pTexture;		//�e�N�X�`���|�C���^
	
protected:
	//���W���
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
