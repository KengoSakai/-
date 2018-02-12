#include "scene2D.h"

class CWinPlayer:public CScene2D
{
public:
	~CWinPlayer(){}
	void Initialize(void);	//‰Šú‰»ˆ—
	void Uninitialize(void);	//I—¹ˆ—
	void Update(void);	//XVˆ—
	void Draw(void);	//•`‰æˆ—
	static CWinPlayer *Create(OBJTYPE WinObjtype);
private:
	CWinPlayer();
};
