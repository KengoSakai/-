#include "model.h"

class CGoalModel : public CModel
{
public:
	~CGoalModel() {}
	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);
	static CGoalModel *Create(void);
private:
	CGoalModel();

protected:

};
