#ifndef _ENEMYMODEL_H_
#define _ENEMYMODEL_H_

#include "model.h"

class CEnemyModel : public CModel
{
public:
	typedef enum
	{
		NONE = 0,
		WALK,
		ATTACK,
		JUMP,
		DAMAGE,
		MAX
	}STATE;
	~CEnemyModel() {}	//�f�X�g���N�^
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CEnemyModel *Create(void);
	D3DXVECTOR3 GetPosition(void) { return Position; }
	void HitObject(void);
private:
	CEnemyModel();	//�R���X�g���N�^
	void Move(void);
	int Count;
	float Speed;
	STATE State;
	void SearchObject(void);
	D3DXVECTOR3 TargetPosition;
protected:
};
#endif
