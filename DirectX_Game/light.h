/******************************************************************
***
***		ライト処理
***
***		light.h
***
***		author: Kengo Sakai
***
*******************************************************************/
#ifndef _LIGHT_H_
#define _LIGHT_H_

/******************************************************************
構造体またはクラス定義
*******************************************************************/
class CLight
{
public:
	CLight();	//コンストラクタ
	~CLight();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);
	void Update(void);
	void SetShadowLight(void);
	void SetModelLight(void);
	void SetCameraLight(void);
	D3DXVECTOR3 GetPosition(void) { return m_Light.Position; }
private:
	void Debug(void);
	D3DLIGHT9 m_Light;
};
#endif
