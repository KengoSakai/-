#include "physics.h"

//コンストラクタ
CPhysics::CPhysics()
{

}

//初期化処理関数
void CPhysics::Initialize(void)
{
	
}

//
D3DXVECTOR3 CPhysics::AddForce(D3DXVECTOR3 Position,D3DXVECTOR3 AddForce)
{
	Position += AddForce;
	return Position;
}
