#include "manager.h"
#include "enemyModel.h"
#include "particle.h"
#include "bullet.h"
#include "physics.h"
#include "target.h"
#include "collision.h"
/******************************************************************
�R���X�g���N�^
*******************************************************************/
CEnemyModel::CEnemyModel()
{
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_ENEMY);
}

/******************************************************************
�����������֐�
*******************************************************************/
void CEnemyModel::Initialize(void)
{
	Position = D3DXVECTOR3(0.0f,10.0f,20.0f);
	Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Vector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	Speed = 0.0f;
	State = WALK;
}

/******************************************************************
�I�������֐�
*******************************************************************/
void CEnemyModel::Uninitialize(void)
{
	CModel::Uninitialize();
}

/******************************************************************
�X�V�����֐�
*******************************************************************/
void CEnemyModel::Update(void)
{
	//�ړ�����
	Move();

	SearchObject();
	
	//�I�u�W�F�N�g�����蔻�菈��
	//HitObject();

	//�ҋ@��Ԃ̏ꍇ
	Speed *= 0.96f;

	//�ړ���Ԃ̏ꍇ
	if (State == WALK && Speed < 3.0f)
	{
		Speed += 0.1f;
	}
}

/******************************************************************
�`�揈���֐�
*******************************************************************/
void CEnemyModel::Draw(void)
{
	CModel::SetMatrix();
	CModel::Draw();
}

/******************************************************************
�I�u�W�F�N�g��������
*******************************************************************/
CEnemyModel *CEnemyModel::Create(void)
{
	//�I�u�W�F�N�g�|�C���^
	CEnemyModel *pEnemyModel;

	//�C���X�^���X����
	pEnemyModel = new CEnemyModel;

	//����������
	pEnemyModel->Initialize();

	//�R���e�i�N���X�ɃI�u�W�F�N�g�̌^��ݒ�
	pEnemyModel->SetObjType(OBJTYPE_ENEMY);

	//�}�e���A���o�b�t�@�𑗂�
	pEnemyModel->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_ENEMY));

	//���b�V�����𑗂�
	pEnemyModel->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_ENEMY));

	//�}�e���A���̗v�f���𑗂�
	pEnemyModel->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_ENEMY));
	
	//�e�N�X�`���̐ݒ�
	pEnemyModel->BindTexture(NULL);

	return pEnemyModel;
}

void CEnemyModel::HitObject(void)
{
	//Uninitialize();
}

/******************************************************************
�ړ������֐�
*******************************************************************/
void CEnemyModel::Move(void)
{
	//�X�e�[�g���ړ��ɕύX
	State = WALK;

	//�^�[�Q�b�g�����̃x�N�g�������߂�
	Vector = TargetPosition - Position;
	
	//�@���𐳋K��
	D3DXVec3Normalize(&Vector,&Vector);

	if (CCollision::Distance(Position, TargetPosition) < 5000)
	{
		CBullet::Create(Position, Vector, OBJTYPE_ENEMY);
	}

	if (State == WALK)
	{
		Position = CPhysics::AddForce(Position, Speed * Vector);
	}
}

/******************************************************************
�I�u�W�F�N�g�T�������֐�
*******************************************************************/
void CEnemyModel::SearchObject(void)
{
	//�I�u�W�F�N�g���J��Ԃ�
	for (int nCntScene = 0; nCntScene < NUM_OBJECT; nCntScene++)
	{
		//�I�u�W�F�N�g�̏��擾
		CScene *pScene = CScene::GetScene(nCntScene);

		//�I�u�W�F�N�g�̃|�C���^�[��NULL�łȂ��Ȃ�
		if (pScene != NULL)
		{
			//�I�u�W�F�N�g�̌^���擾
			CScene::OBJTYPE ObjType = pScene->GetObjType();

			if (ObjType == CScene::OBJTYPE_TARGET)
			{
				//�I�u�W�F�N�g�|�C���^
				CTarget *pTarget = (CTarget*)pScene;

				//if (TargetPosition = pTarget->GetPosition())
				{
					TargetPosition = pTarget->GetPosition();
					break;
				}
			}
		}
	}
}
