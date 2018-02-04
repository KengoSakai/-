#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "main.h"

class CPhysics
{
public:
	CPhysics();
	~CPhysics(){}
	static void Initialize(void);
	static bool BoxCast(void);
	static bool BoxCastAll(void);
	static bool BoxCastNonAlloc(void);
	static bool CapsuleCast(void);
	static bool CapsuleCastAll(void);
	static bool CheckBox(void);
	static bool CheckCapsule(void);
	static bool CheckSphere(void);
	static D3DXVECTOR3 AddForce(D3DXVECTOR3 Position,D3DXVECTOR3 AddForce);
};
#endif
