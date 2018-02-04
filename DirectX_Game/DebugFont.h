
class CDebugFont
{
public:
	CDebugFont();							//コンストラクタ
	~CDebugFont();	//デストラクタ
	void Initialize(void);
	void Uninitialize(void);
	void AddDebugFont( char *AddDebugFont, float ObjectValue,int PositionX , int PositionY);	//デバッグ表示追加処理

private:
	LPD3DXFONT pDebugFont;				//デバッグ表示インターフェース
};
