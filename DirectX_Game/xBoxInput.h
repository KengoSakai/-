#ifndef _XBOXINPUT_H_
#define _XBOXINPUT_H_
#include "main.h"

class CXBoxInput
{
public:
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	XINPUT_STATE *State;

};
#endif
