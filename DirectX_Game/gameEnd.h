#include "scene2D.h"

class CGameEnd:public CScene2D
{
public:
	~CGameEnd(){}
	void Initialize(void);	//����������
	void Uninitialize(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static CGameEnd *Create(void);
private:
	CGameEnd();
};
