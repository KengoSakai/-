/******************************************************************
***
***		�Q�[�W����
***
***		timeBox.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _TIMEBOX_H_
#define _TIMEBOX_H_
/******************************************************************
�C���N���[�h�t�@�C��
*******************************************************************/
#include "scene2D.h"

/******************************************************************
�N���X��`
*******************************************************************/
class CTimeBox :public CScene2D
{
public:
	~CTimeBox() {}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CTimeBox *Create(void);

private:
	CTimeBox();
};
#endif
