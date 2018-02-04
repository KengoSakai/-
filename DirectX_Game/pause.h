#ifndef _PAUSE_H_
#define _PAUSE_H_
class CPause
{
public:
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CPause *Create(void);
private:
};
#endif
