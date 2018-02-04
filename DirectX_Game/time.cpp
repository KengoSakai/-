/******************************************************************
***
***		時間処理
***
***		time.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "time.h"
#include "number.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CTime::CTime()
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		//NULLを入れる
		m_apNumber[nCnt] = NULL;
	}
	m_nTime = 10 * 60;
}

/******************************************************************
デストラクタ
*******************************************************************/
CTime :: ~CTime()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CTime::Initialize(void)
{
	Position = D3DXVECTOR3((float)(SCREEN_WIDTH / 2), 20.0f, 0.0f);

	int nTime = 0;

	nTime = m_nTime;

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		//ナンバーの生成
		m_apNumber[nCnt] = CNumber::Create(nCnt, Position);

		//各桁に数字を設定
		m_apNumber[nCnt]->SetNumber(nTime % 10);
		nTime /= 10;
	}
}

/******************************************************************
終了処理関数
*******************************************************************/
void CTime::Uninitialize(void)
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		//ナンバーの破棄
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
	//シーンの破棄
	CScene::Release();
}

/******************************************************************
更新処理関数
*******************************************************************/
void CTime::Update(void)
{
	SubTime();
}

/******************************************************************
描画処理関数
*******************************************************************/
void CTime::Draw(void)
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//ナンバーの描画処理
			m_apNumber[nCnt]->Draw();
		}
	}
}

/******************************************************************
オブジェクト生成関数
*******************************************************************/
CTime *CTime::Create(void)
{
	//オブジェクトポインタ
	CTime *pTime;

	//インスタンスの生成
	pTime = new CTime;

	//初期化処理
	pTime->Initialize();

	pTime->SetObjType(OBJTYPE_TIME);

	return pTime;
}

/******************************************************************
加算処理関数
*******************************************************************/
void CTime::AddTime(void)
{
	int nTime = 0;
	int nAddTime = m_nTime;

	nAddTime /= 60;

	//数値の加算
	nTime = nAddTime;

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//各桁に数値を設定
			m_apNumber[nCnt]->SetNumber(nTime % 10);
			nTime /= 10;
		}
	}
	m_nTime++;
}

/******************************************************************
減算処理関数
*******************************************************************/
void CTime::SubTime(void)
{
	int nTime = 0;
	int nSubTime = m_nTime;

	nSubTime /= 60;

	//数値の減算
	nTime = nSubTime;

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//各桁に数値を設定
			m_apNumber[nCnt]->SetNumber(nTime % 10);
			nTime /= 10;
		}
	}
	m_nTime--;
}

/******************************************************************
時間取得処理関数
*******************************************************************/
int CTime::GetTime(void)
{
	return m_nTime;
}
