
#include "targetRespawnPosition.h"

#define NUM_RESPAWN_POSITION (4)

CTargetRespawnPosition::CTargetRespawnPosition()
{

}

D3DXVECTOR3 CTargetRespawnPosition::RespawnPosition(void)
{
	D3DXVECTOR3 Position;
	int RandomNumber = 0;
	RandomNumber = rand() % NUM_RESPAWN_POSITION;
	
	//乱数が0なら
	if (RandomNumber == 0)
	{
		Position = D3DXVECTOR3(-630.0f, 0.0f, 0.0f);
	}

	//乱数が1なら
	else if (RandomNumber == 1)
	{

		Position = D3DXVECTOR3(630.0f, 0.0f, 0.0f);
	}

	//乱数が2なら
	else if (RandomNumber == 2)
	{
		Position = D3DXVECTOR3(0.0f, 0.0f, 630.0f);
	}

	//乱数が3なら
	else if (RandomNumber == 3)
	{
		Position = D3DXVECTOR3(0.0f, 0.0f, -630.0f);
	}

	//上記以外
	else
	{

	}

	return Position;
}
