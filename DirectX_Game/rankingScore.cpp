#include "rankingScore.h"
#include "file.h"

CRankingScore::CRankingScore()
{
	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//NULLを入れる
		m_apNumber[nCnt] = NULL;
	}

}

void CRankingScore::Initialize(void)
{
	int nScore;
	m_nScore = CFile::Load("score.bin", 1);

	nScore = m_nScore;
	
	Position = D3DXVECTOR3(400.0f, 300.0f, 0.0f);

	//表示桁数分繰り返す
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//ナンバーの生成
		m_apNumber[nCnt] = CNumber::Create(nCnt, Position);

		//各桁に数字を設定
		m_apNumber[nCnt]->SetNumber(0);
	}

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

void CRankingScore::Uninitialize(void)
{
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

void CRankingScore::Update(void)
{

}

void CRankingScore::Draw(void)
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

CRankingScore *CRankingScore::Create(void)
{
	CRankingScore *pRankingScore;

	pRankingScore = new CRankingScore;

	pRankingScore->Initialize();
	pRankingScore->SetObjType(OBJTYPE_SCORE);
	return pRankingScore;
}
