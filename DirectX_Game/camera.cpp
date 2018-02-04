/******************************************************************
***
***		カメラ処理
***
***		camera.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CCamera::CCamera()
{

}

/******************************************************************
デストラクタ
*******************************************************************/
CCamera::~CCamera()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
HRESULT CCamera::Init(void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pD3DDevice =  CManager::GetRenderer()->GetDevice();

	m_VecUp = D3DXVECTOR3(0.0f,1.0f,0.0f);		//カメラの上方向の向き
	m_PosAt = D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの注視点
	m_PosView = D3DXVECTOR3(0.0f,50.0f,-300.0f);	//カメラの位置
	m_fRot = -90.0f;

	//プロジェクションマトリクスを作る	
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DX_PI/3.0f, (float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,3000.0f);

	//デバイスにプロジェクション変換行列を設定
	pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	D3DXMatrixLookAtLH(&m_MtxView, &m_PosView, &m_PosAt, &m_VecUp);
	pD3DDevice->SetTransform(D3DTS_VIEW,&m_MtxView);

	return S_OK;
}

/******************************************************************
終了処理関数
*******************************************************************/
void CCamera::Uninit(void)
{

}

/******************************************************************
更新処理関数
*******************************************************************/
void CCamera::Update (void)
{
	//デバイス情報を取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	if(CManager :: GetInputKeyboard()->GetKeyPress(DIK_LEFT))
	{
		m_fRot -= 1.0f;
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_RIGHT))
	{
		m_fRot += 1.0f;
	}
	
	//オブジェクト数繰り返す
	for (int nCntScene = 0; nCntScene < 100; nCntScene++)
	{
		//オブジェクトの情報取得
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		//オブジェクトのポインターがNULLでないなら
		if (pScene != NULL)
		{
			//オブジェクトの型を取得
			CScene::OBJTYPE ObjType;
			ObjType = pScene->GetObjType();

			//指定したオブジェクトなら
			if (ObjType == CScene::OBJTYPE_PLAYER)
			{
				//オブジェクトポインタ
				CPlayer *pPlayer = (CPlayer*)pScene;

				//プレイヤーの座標取得して追従
				m_PosView.z = pPlayer->GetPosition().z;
				m_PosView.x = pPlayer->GetPosition().x;
				m_PosView.y = pPlayer->GetPosition().y+20.0f;
				m_PosView.x += cosf(D3DXToRadian(m_fRot))*100.0f;
				m_PosView.z += sinf(D3DXToRadian(m_fRot))*100.0f;
		
				//注視点をプレイヤーの座標に設定
				m_PosAt = pPlayer->GetPosition();
			}
		}
	}
	//行列変換
	D3DXMatrixLookAtLH(&m_MtxView, &m_PosView, &m_PosAt, &m_VecUp);

	//ビュー行列に設定
	pD3DDevice->SetTransform(D3DTS_VIEW,&m_MtxView);

	//CManager::GetLight()->SetCameraLight();
}
