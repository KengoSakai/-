#ifndef _CLOUD_H_
#define _CLOUD_H_
#include "scene3D.h"

class CCloud : public CScene3D
{
public:
	~CCloud() {}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CCloud *Create(void);
private:
	CCloud();
};
#endif 
