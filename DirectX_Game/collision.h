#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "main.h"
class CCollision
{
public:
	CCollision();
	~CCollision();
	static bool SphereCollision(D3DXVECTOR3 MyPos, D3DXVECTOR3 OtherPos);		//円の当たり判定
	static bool CubeCollision(D3DXVECTOR3 MyPos, D3DXVECTOR3 OtherPos);		//立方体の当たり判定
	static float Distance(D3DXVECTOR3 MyPos, D3DXVECTOR3 OtherPos);			//オブジェクトからの距離を求める

};
#endif
