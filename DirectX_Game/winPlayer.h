#include "scene2D.h"

class CWinPlayer:public CScene2D
{
public:
	~CWinPlayer(){}
	void Initialize(void);	//����������
	void Uninitialize(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static CWinPlayer *Create(OBJTYPE WinObjtype);
private:
	CWinPlayer();
};
