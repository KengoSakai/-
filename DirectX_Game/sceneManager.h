#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "baseScene.h"
#include "fade.h"

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager(){}
	void Initialize(void);
	void Uninitalize(void);
	void Update(void);
	CFade *pFade;
private:
	CBaseScene *pBaseScene;
};
#endif
