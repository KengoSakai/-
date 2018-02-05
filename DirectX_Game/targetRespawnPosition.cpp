
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
	
	//—”‚ª0‚È‚ç
	if (RandomNumber == 0)
	{
		Position = D3DXVECTOR3(-630.0f, 0.0f, 0.0f);
	}

	//—”‚ª1‚È‚ç
	else if (RandomNumber == 1)
	{

		Position = D3DXVECTOR3(630.0f, 0.0f, 0.0f);
	}

	//—”‚ª2‚È‚ç
	else if (RandomNumber == 2)
	{
		Position = D3DXVECTOR3(0.0f, 0.0f, 630.0f);
	}

	//—”‚ª3‚È‚ç
	else if (RandomNumber == 3)
	{
		Position = D3DXVECTOR3(0.0f, 0.0f, -630.0f);
	}

	//ã‹LˆÈŠO
	else
	{

	}

	return Position;
}
