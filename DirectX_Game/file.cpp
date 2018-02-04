/******************************************************************
***
***		ファイル処理
***
***		file.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "file.h"

/******************************************************************
ファイルセーブ処理関数
*******************************************************************/
void CFile::Save(char *OpenFileName, int NumberData, int Score)
{
	FILE *pFile = NULL;

	pFile = fopen(OpenFileName, "wb");	//ファイルを開く

	//データがある場合
	if (pFile != NULL)
	{
		//入力した人数分ファイルに書き出す
		fwrite(&NumberData, sizeof(int), 1, pFile);
		
		//入力したステータスをファイルに書き出す
		fwrite(&Score, sizeof(int), NumberData, pFile);
		
		//ファイルを閉じる
		fclose(pFile);
	}

	//データがない場合
	else
	{
		//起動時に表示するタイトルとメッセージ
		MessageBox(NULL, "データを記録できませんでした", "エラーメッセージ", MB_OK);					
	}
}

/******************************************************************
ファイルロード処理関数
*******************************************************************/
int CFile::Load(char *OpenFileName, int NumberData)
{
	//ファイルポインタ
	FILE *pFile=NULL;

	//スコア用変数
	int Score = 0;

	//ファイルを開く
	pFile = fopen(OpenFileName, "rb");

	//ファイルポインタがNULLでない場合
	if (pFile != NULL)
	{
		//入力されていた人数分ファイルを読みこむ
		fread(&NumberData, sizeof(int), 1, pFile);	
		
		//入力されたステータスを読みこむ
		fread(&Score, sizeof(int), NumberData, pFile);
		
		//ファイルを閉じる
		fclose(pFile);
	}

	//ファイルポインタが読み込めなかった場合
	else
	{
		//起動時に表示するタイトルとメッセージ
		MessageBox(NULL, "データを読み込めませんでした", "エラーメッセージ", MB_OK);					
	}

	return Score;
}
