/******************************************************************
***
***		スコア処理
***
***		score.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "manager.h"
#include "number.h"
#include "score.h"
#include "file.h"
/******************************************************************
コンストラクタ
*******************************************************************/
CScore::CScore(OBJTYPE type)
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//NULLを入れる
		m_apNumber[nCnt] = NULL;
	}

	if (type == OBJTYPE_SCORE)
	{
		//変数初期化
		Position = D3DXVECTOR3(300.0f, 30.0f, 0.0f);
		return;
	}

	else if (type == OBJTYPE_OTHERPLAYERSCORE)
	{
		//変数初期化
		Position = D3DXVECTOR3(1200.0f, 30.0f, 0.0f);
		return;
	}

	else
	{
		return;
	}
}

/******************************************************************
デストラクタ
*******************************************************************/
CScore :: ~CScore()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
void CScore::Initialize(void)
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//ナンバーの生成
		m_apNumber[nCnt] = CNumber::Create(nCnt, Position);

		//初期値を設定
		m_nScore = 0;

		//各桁に数字を設定
		m_apNumber[nCnt]->SetNumber(0);
	}
}

/******************************************************************
終了処理関数
*******************************************************************/
void CScore::Uninitialize(void)
{
	CFile::Save("score.bin",1,m_nScore);

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
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
void CScore::Update(void)
{

}

/******************************************************************
描画処理関数
*******************************************************************/
void CScore::Draw(void)
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//ナンバーの描画処理
			m_apNumber[nCnt]->Draw();
		}
	}
}

/******************************************************************
オブジェクト生成処理関数
*******************************************************************/
CScore *CScore::Create(OBJTYPE type)
{
	//ポインタ宣言
	CScore *pScore;

	//インスタンス生成
	pScore = new CScore(type);

	//初期化処理
	pScore->Initialize();

	pScore->SetObjType(type);

	return pScore;
}

/******************************************************************
スコア加算処理関数
*******************************************************************/
void CScore::AddScore(int nValue)
{
	int nScore;

	//数値の加算
	m_nScore += nValue;

	nScore = m_nScore;

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//各桁に数値を設定
			m_apNumber[nCnt]->SetNumber(nScore % 10);
			nScore /= 10;
		}
	}
}

/******************************************************************
スコア情報取得処理関数
*******************************************************************/
int CScore::GetScore(void)
{
	return m_nScore;
}

