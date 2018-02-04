#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "scene.h"
#include "number.h"

#define NUM_DIGIT (8)	//表示桁数

class CRankingScore : public CScene
{
public:
	~CRankingScore(){}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CRankingScore *Create(void);
private:
	CRankingScore();
	CNumber * m_apNumber[NUM_DIGIT];			//数字へのポインタ
	D3DXVECTOR3 Position;					//ＸＹ座標
	int m_nScore;							//スコアの値
};
#endif
