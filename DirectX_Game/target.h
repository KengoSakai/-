#ifndef _TARGET_H_
#define _TARGET_H_

#include "model.h"

class CTarget : public CModel
{
public:
	~CTarget() {}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CTarget *Create(void);
	void HitObject(OBJTYPE Type);
	D3DXVECTOR3 GetPosition(void);

private:
	CTarget();
};
#endif