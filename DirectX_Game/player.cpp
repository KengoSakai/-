/******************************************************************
***
***		����
***
***		.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
�C���N���[�h�t�@�C��
*******************************************************************/
#include "manager.h"
#include "camera.h"
#include "player.h"
#include "particle.h"
#include "DebugFont.h"
#include "gaugeBox.h"
#include "gaugeMeter.h"
#include "score.h"
#include "collision.h"
#include "cubeCollider.h"
#include "physics.h"
#include "item.h"
#include "bullet.h"
#include "startPosition.h"
/******************************************************************
�}�N����`
*******************************************************************/
#define NUM_PARTS (10)
/******************************************************************
�\���̂܂��̓N���X��`
*******************************************************************/

/******************************************************************
�v���g�^�C�v�錾
*******************************************************************/

/******************************************************************
�O���[�o���ϐ�
*******************************************************************/

/******************************************************************/

/******************************************************************
�R���X�g���N�^
*******************************************************************/
CPlayer::CPlayer()
{
	CGauge::Create();
	pGauge = CGaugeMeter::Create(300.0f);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_HEAD);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_BODY);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_RIGHT_ARM);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_LEFT_ARM);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_RIGHT_HAND);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_LEFT_HAND);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_RIGHT_LEG);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_LEFT_LEG);
	CManager::GetModelManager()->LoadModel(CModelManager::TYPE_PLAYER);
	//	CCubeCollider::Create();

	//�e��ݒ�
	ParentParts[BODY] = BODY;
	ParentParts[HEAD] = BODY;
	ParentParts[ARM_RIGHT] = BODY;
	ParentParts[ARM_LEFT] = BODY;
	ParentParts[HAND_RIGHT] = ARM_RIGHT;
	ParentParts[HAND_LEFT] = ARM_LEFT;
	ParentParts[LEG_RIGHT] = BODY;
	ParentParts[LEG_LEFT] = BODY;
	ParentParts[FOOT_RIGHT] = LEG_RIGHT;
	ParentParts[FOOT_LEFT] = LEG_LEFT;
}

/******************************************************************
�����������֐�
*******************************************************************/
void CPlayer::Initialize(void)
{
	Position = CStartPosition::SetPosition();
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Speed = 0.0f;
	State = WALK;
	Vector = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Rotate[BODY] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotate[HEAD] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotate[ARM_RIGHT] = D3DXVECTOR3(0.0f, 0.0f,-40.0f);
	Rotate[ARM_LEFT] = D3DXVECTOR3(0.0f, 0.0f, 40.0f);
	Rotate[HAND_RIGHT] = D3DXVECTOR3(-130.0f, 0.0f, 0.0f);
	Rotate[HAND_LEFT] = D3DXVECTOR3(-130.0f, 0.0f, 0.0f);
	Rotate[LEG_RIGHT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotate[LEG_LEFT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotate[FOOT_RIGHT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotate[FOOT_LEFT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	for (int Count = 0; Count < PARTS_MAX; Count++)
	{
		Rotate[Count] += Rotate[ParentParts[Count]];
	}

	PartsPosition[BODY] = Position;
	PartsPosition[HEAD] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 25.0f, 0.0f);
	PartsPosition[ARM_RIGHT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	PartsPosition[ARM_LEFT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	PartsPosition[HAND_RIGHT] = PartsPosition[ParentParts[HAND_RIGHT]] + D3DXVECTOR3(10.0, 0.0f, 0.0f);
	PartsPosition[HAND_LEFT] = PartsPosition[ParentParts[HAND_LEFT]] + D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	PartsPosition[LEG_RIGHT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PartsPosition[LEG_LEFT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PartsPosition[FOOT_RIGHT] = PartsPosition[ParentParts[FOOT_RIGHT]] + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PartsPosition[FOOT_LEFT] = PartsPosition[ParentParts[FOOT_LEFT]] + D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

/******************************************************************
�I�������֐�
*******************************************************************/
void CPlayer::Uninitialize(void)
{
	CMotionModel::Uninitialize();
}

/******************************************************************
�X�V�����֐�
*******************************************************************/
void CPlayer::Update(void)
{
	CameraVector = CManager::GetCamera()->GetPosView();
	CameraVector.y = 0.0f;
	Vector = Position - CameraVector;
	D3DXVec3Normalize(&Vector, &Vector);

	//�ړ�����
	Move();

	//�I�u�W�F�N�g�����蔻�菈��
	HitObject();

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
void CPlayer::Draw(void)
{
	//CMotionModel::SetMatrix();
	CMotionModel::Draw();

#ifdef _DEBUG
	CManager::GetDebugFont()->AddDebugFont("Player:Position.x", Position.x, 0, 0);
	CManager::GetDebugFont()->AddDebugFont("Player:Position.y", Position.y, 0, 20);
	CManager::GetDebugFont()->AddDebugFont("Player:Position.z", Position.z, 0, 40);
	CManager::GetDebugFont()->AddDebugFont("Player:Speed", Speed, 0, 60);
	//CManager::GetDebugFont()->AddDebugFont("Player:State", State, 0, 80);
#endif
}

/******************************************************************
�I�u�W�F�N�g���������֐�
*******************************************************************/
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer;

	//�C���X�^���X����
	pPlayer = new CPlayer;

	//����������
	pPlayer->Initialize();

	//�R���e�i�N���X�ɃI�u�W�F�N�g�̌^��ݒ�
	pPlayer->SetObjType(OBJTYPE_PLAYER);

	//�}�e���A���o�b�t�@�𑗂�
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_BODY), BODY);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_HEAD), HEAD);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_RIGHT_ARM), ARM_RIGHT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_LEFT_ARM), ARM_LEFT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_RIGHT_HAND), HAND_RIGHT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_LEFT_HAND), HAND_LEFT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_RIGHT_LEG), LEG_RIGHT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_LEFT_LEG), LEG_LEFT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_LEFT_LEG), FOOT_RIGHT);
	pPlayer->BindBuff(CManager::GetModelManager()->GetMaterialBuffer(CModelManager::TYPE_LEFT_LEG), FOOT_LEFT);

	//���b�V�����𑗂�
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_BODY), BODY);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_HEAD), HEAD);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_RIGHT_ARM), ARM_RIGHT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_LEFT_ARM), ARM_LEFT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_RIGHT_HAND), HAND_RIGHT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_LEFT_HAND), HAND_LEFT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_RIGHT_LEG), LEG_RIGHT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_LEFT_LEG), LEG_LEFT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_LEFT_LEG), FOOT_RIGHT);
	pPlayer->BindMesh(CManager::GetModelManager()->GetMesh(CModelManager::TYPE_LEFT_LEG), FOOT_LEFT);

	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_PLAYER), BODY);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_HEAD), HEAD);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_RIGHT_ARM), ARM_RIGHT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_LEFT_ARM), ARM_LEFT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_RIGHT_HAND), HAND_RIGHT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_LEFT_HAND), HAND_LEFT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_RIGHT_LEG), LEG_RIGHT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_LEFT_LEG), LEG_LEFT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_LEFT_LEG), FOOT_RIGHT);
	pPlayer->BindMaterials(CManager::GetModelManager()->GetNumMaterials(CModelManager::TYPE_LEFT_LEG), FOOT_LEFT);

	pPlayer->BindTexture(NULL);

	return pPlayer;
}

/******************************************************************
�ړ������֐�
*******************************************************************/
void CPlayer::Move(void)
{
	State = NONE;

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_W))
	{
		State = WALK;
		CParticle::Create(Position);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_S))
	{
		Vector *= -1;
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_A))
	{
			//��]�s��
			D3DXMatrixRotationYawPitchRoll(&RotateVectorMatrix,
				D3DXToRadian(-90.0f),
				D3DXToRadian(0.0f),
				D3DXToRadian(0.0f));

			D3DXVec3TransformCoord(&Vector, &Vector, &RotateVectorMatrix);
		
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_D))
	{
			//��]�s��
			D3DXMatrixRotationYawPitchRoll(&RotateVectorMatrix,
				D3DXToRadian(90.0f),
				D3DXToRadian(0.0f),
				D3DXToRadian(0.0f));

			D3DXVec3TransformCoord(&Vector, &Vector, &RotateVectorMatrix);
		
		State = WALK;
	}

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		CBullet::Create(Position, Vector, OBJTYPE_PLAYER);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_X))
	{
		Rotate[ARM_RIGHT].x += 0.5f;
		Rotate[HAND_RIGHT].x += 1.5f;
		Rotate[LEG_RIGHT].x += 0.5f;
		Rotate[LEG_LEFT].x += 0.5f;
		Rotate[FOOT_RIGHT].x += 0.5f;
		Rotate[FOOT_LEFT].x += 0.5f;
		for (int Count = 0; Count < PARTS_MAX; Count++)
		{
		//	Rotate[Count] += Rotate[ParentParts[Count]];
		}
	}

	if (State == WALK)
	{
		//�͂�������
		Position = CPhysics::AddForce(Position, Speed * Vector);
	}

	//�p�[�c�̈ړ�
	PartsPosition[BODY] = Position;
	PartsPosition[HEAD] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 25.0f, 0.0f);
	PartsPosition[ARM_RIGHT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	PartsPosition[ARM_LEFT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	PartsPosition[HAND_RIGHT] = PartsPosition[ParentParts[HAND_RIGHT]];
	PartsPosition[HAND_RIGHT].x += cosf(D3DXToRadian(Rotate[ParentParts[HAND_RIGHT]].z))*10.0f;
	PartsPosition[HAND_RIGHT].y += sinf(D3DXToRadian(Rotate[ParentParts[HAND_RIGHT]].z))*10.0f;
	PartsPosition[HAND_RIGHT].z += sinf(D3DXToRadian(Rotate[ParentParts[HAND_RIGHT]].y))*10.0f;

	PartsPosition[HAND_LEFT] = PartsPosition[ParentParts[HAND_LEFT]];
	PartsPosition[HAND_LEFT].x += cosf(D3DXToRadian(Rotate[ParentParts[HAND_LEFT]].z))*-10.0f;
	PartsPosition[HAND_LEFT].y += sinf(D3DXToRadian(Rotate[ParentParts[HAND_LEFT]].z))*-10.0f;
	PartsPosition[HAND_LEFT].z += sinf(D3DXToRadian(Rotate[ParentParts[HAND_LEFT]].y))*-10.0f;

	PartsPosition[LEG_RIGHT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	PartsPosition[LEG_LEFT] = PartsPosition[BODY] + D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	PartsPosition[FOOT_RIGHT] = PartsPosition[ParentParts[FOOT_RIGHT]];
	PartsPosition[FOOT_RIGHT].x += cosf(D3DXToRadian(Rotate[ParentParts[FOOT_RIGHT]].z))*10.0f;
	PartsPosition[FOOT_RIGHT].y += sinf(D3DXToRadian(Rotate[ParentParts[FOOT_RIGHT]].z))*10.0f;
	PartsPosition[FOOT_RIGHT].z += sinf(D3DXToRadian(Rotate[ParentParts[FOOT_RIGHT]].x))*10.0f;

	PartsPosition[FOOT_LEFT] = PartsPosition[ParentParts[FOOT_LEFT]];
	PartsPosition[FOOT_LEFT].x += cosf(D3DXToRadian(Rotate[ParentParts[FOOT_LEFT]].z))*-10.0f;
	PartsPosition[FOOT_LEFT].y += sinf(D3DXToRadian(Rotate[ParentParts[FOOT_LEFT]].z))*-10.0f;
	PartsPosition[FOOT_LEFT].z += sinf(D3DXToRadian(Rotate[ParentParts[FOOT_LEFT]].x))*-10.0f;
}

/******************************************************************
�I�u�W�F�N�g�̓����蔻�菈���֐�
*******************************************************************/
void CPlayer::HitObject(void)
{
	//�I�u�W�F�N�g���J��Ԃ�
	for (int nCntScene = 0; nCntScene < 1000; nCntScene++)
	{
		//�I�u�W�F�N�g�̏��擾
		CScene *pScene = CScene::GetScene(nCntScene);

		//�I�u�W�F�N�g�̃|�C���^�[��NULL�łȂ��Ȃ�
		if (pScene != NULL)
		{
			//�I�u�W�F�N�g�̌^���擾
			CScene::OBJTYPE ObjType = pScene->GetObjType();

			if (ObjType == CScene::OBJTYPE_ITEM)
			{
				//�I�u�W�F�N�g�|�C���^
				CItem *pItem = (CItem*)pScene;

				if (CCollision::SphereCollision(Position, pItem->GetPosition()))
				{
					pItem->Hit(OBJTYPE_PLAYER);

				}
			}

		}
	}
}