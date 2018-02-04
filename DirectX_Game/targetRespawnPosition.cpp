#include "targetRespawnPosition.h"

CTargetRespawnPosition::CTargetRespawnPosition()
{

}

D3DXVECTOR3 CTargetRespawnPosition::RespawnPosition(void)
{
	D3DXVECTOR3 Position;

	//
	Position = D3DXVECTOR3(-630.0f, 0.0f, 0.0f);

	//
	Position = D3DXVECTOR3(630.0f, 0.0f, 0.0f);

	//
	Position = D3DXVECTOR3(0.0f, 0.0f, 630.0f);

	//
	Position = D3DXVECTOR3(0.0f, 0.0f, -630.0f);

	return Position;
}