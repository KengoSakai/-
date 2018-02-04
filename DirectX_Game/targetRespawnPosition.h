#ifndef _TARGETRESPAWNPOSITION_H_
#define _TARGETRESPAWNPOSITION_H_
#include "main.h"
class CTargetRespawnPosition
{
public:
	~CTargetRespawnPosition() {}
	static D3DXVECTOR3 RespawnPosition(void);
private:
	CTargetRespawnPosition();

};
#endif
