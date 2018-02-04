#include "main.h"
class CFile
{
public:
	static int Load(char *OpenFileName, int NumberData);
	static void Save(char *SaveFileName, int NumberData, int Score);
};