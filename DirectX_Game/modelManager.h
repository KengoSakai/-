/******************************************************************
***
***		���f���Ǘ�����
***
***		modelManager.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_
/******************************************************************
�C���N���[�h�t�@�C��
*******************************************************************/

/******************************************************************
�}�N����`
*******************************************************************/

/******************************************************************
�\���̂܂��̓N���X��`
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

	CModelManager();			//�R���X�g���N�^
	~CModelManager() {}			//�f�X�g���N�^
	void Initialize(void);
	void Unitialize(void);
	void LoadModel(MODEL_TYPE OrderModelType);	//���f���擾����
	LPD3DXMESH GetMesh(MODEL_TYPE OrderModelType);
	DWORD GetNumMaterials(MODEL_TYPE OrderModelType);
	LPD3DXBUFFER GetMaterialBuffer(MODEL_TYPE OrderModelType);
private:
	char *pModelList[TYPE_MAX];	//���f�����X�g
	LPD3DXMESH pMesh[TYPE_MAX];			//���b�V��
	LPD3DXBUFFER pMatBuff[TYPE_MAX];		//�o�b�t�@�|�C���^
	DWORD NumMaterials[TYPE_MAX];		//�v�f��
};

/******************************************************************
�v���g�^�C�v�錾
*******************************************************************/

/******************************************************************
�O���[�o���ϐ�
*******************************************************************/

/******************************************************************
�R���X�g���N�^
*******************************************************************/
#endif
