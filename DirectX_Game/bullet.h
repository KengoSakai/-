#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene3D.h"
class CRenderer;
class CBullet : public CScene3D
{
public:
	~CBullet() {}
	void Initialize(D3DXVECTOR3 OrderPosition, D3DXVECTOR3 OrderVector, CScene::OBJTYPE OrderObjectType);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 OrderPosition, D3DXVECTOR3 OrderVector, CScene::OBJTYPE OrderObjectType);
private:
	typedef enum
	{
		NONE = 0,
		SHOT,
		HIT,
		MAX
	}STATE;

	CBullet();
	void HitObject(void);
	STATE State;
	CScene::OBJTYPE OwnerObjectType;
	static CRenderer *m_pRenderer;
};
#endif