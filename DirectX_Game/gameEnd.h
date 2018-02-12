#include "scene2D.h"

class CGameEnd:public CScene2D
{
public:
	~CGameEnd(){}
	void Initialize(void);	//‰Šú‰»ˆ—
	void Uninitialize(void);	//I—¹ˆ—
	void Update(void);	//XVˆ—
	void Draw(void);	//•`‰æˆ—
	static CGameEnd *Create(void);
private:
	CGameEnd();
};
