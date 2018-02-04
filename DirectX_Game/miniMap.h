#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "scene2D.h"

class CMiniMap : public CScene2D
{
public:
	~CMiniMap(){}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CMiniMap *Create(void);
	D3DXVECTOR3 GetPosition(void) { return Position; }
	D3DXVECTOR3 GetWidthHeight(void) { return WidthHeight; }
private:
	CMiniMap();
};
#endif
