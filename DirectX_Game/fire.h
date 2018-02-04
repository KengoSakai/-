#ifndef _FIRE_H_
#define _FIRE_H_
#include "particleBillboard.h"
class CFire : public CParticleBillboard
{
public:
	~CFire(){}
	void Initialize(D3DXVECTOR3 OrderPosition);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CFire *Create(D3DXVECTOR3 OrderPosition);
private:
	CFire();
};
#endif
