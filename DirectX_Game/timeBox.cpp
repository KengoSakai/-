/******************************************************************
***
***		�Q�[�W����
***
***		timeBox.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
�C���N���[�h�t�@�C��
*******************************************************************/
#include "manager.h"
#include "timeBox.h"

/******************************************************************
�R���X�g���N�^
*******************************************************************/
CTimeBox::CTimeBox()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	WidthHeight = D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f);
	Color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
}

/******************************************************************
����������
*******************************************************************/
void CTimeBox::Initialize(void)
{
	CScene2D::Initialize();
	CScene2D::SetColor(Color);
}

/******************************************************************
�I������
*******************************************************************/
void CTimeBox::Uninitialize(void)
{
	CScene2D::Uninitialize();
}

/******************************************************************
�X�V����
*******************************************************************/
void CTimeBox::Update(void)
{

}

/******************************************************************
�`�揈��
*******************************************************************/
void CTimeBox::Draw(void)
{
	CScene2D::Draw();
}

/******************************************************************
�I�u�W�F�N�g��������
*******************************************************************/
CTimeBox *CTimeBox::Create(void)
{
	//�I�u�W�F�N�g�|�C���^
	CTimeBox *pTimeGauge;

	//�C���X�^���X����
	pTimeGauge = new CTimeBox;

	//������
	pTimeGauge->Initialize();
	
	//�I�u�W�F�N�g�̌^��ݒ�
	pTimeGauge->SetObjType(OBJTYPE_TIME);
	
	CManager::GetTextureManager()->LoadTexture(CTextureManager::TYPE_SCREEN_UI);

	//�e�N�X�`����ݒ�
	pTimeGauge->BindTexture(CManager::GetTextureManager()->GetTexture(CTextureManager::TYPE_SCREEN_UI));

	return pTimeGauge;
}