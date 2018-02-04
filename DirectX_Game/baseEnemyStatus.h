#ifndef _ENEMYSTATUS_H_
#define _ENEMYSTATUS_H_
class CBaseEnemyStatus
{
public:
	CBaseEnemyStatus();
	~CBaseEnemyStatus();
	static void Initialize(void);
	static void Update(void);
protected:
	float Speed;
	float Life;
};
#endif
