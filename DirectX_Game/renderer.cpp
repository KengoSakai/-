/******************************************************************
***
***		レンダラー処理
***
***		renderer.cpp
***
***		author: Kengo Sakai
***
*******************************************************************/

/******************************************************************
インクルードファイル
*******************************************************************/
#include "renderer.h"
#include "scene.h"
#include "particleManager.h"
/******************************************************************
マクロ定義
*******************************************************************/

/******************************************************************
構造体定義
*******************************************************************/


/******************************************************************
プロトタイプ宣言
*******************************************************************/

/******************************************************************
グローバル変数
*******************************************************************/


/******************************************************************
コンストラクタ
*******************************************************************/
CRenderer :: CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

/******************************************************************
デストラクタ
*******************************************************************/
CRenderer :: ~CRenderer()
{

}

/******************************************************************
初期化処理関数
*******************************************************************/
HRESULT CRenderer :: Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//D3D9インターフェースの取得
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードの取得
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//ワークをゼロクリア
	d3dpp.BackBufferCount			 = 1;							//バックバッファの数
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				//カラーモードの指定
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		//映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil	 = TRUE;						//デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					//デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;						//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの作成
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL, 
			hWnd, 
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
				D3DDEVTYPE_REF, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングを行わない

	//m_pD3DDevice -> SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);	//設定値、逆時計回りを裏面とする
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αデスティネーションカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT,0xffffffff);

	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャＵ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//テクスチャＶ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//テクスチャ拡大時の補間設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//テクスチャ縮小時の補間設定

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//アルファブレンディング処理(初期値はD3DTOP_SELECTARG1)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//最初のアルファ引数(初期値はD3DTA_TEXTURE、テクスチャがない場合はD3DTA_DIFFUSE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//２番目のアルファ引数(初期値はD3DTA_CURRENT)

	//m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
	//m_pD3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_NEVER);
	//m_pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);
	//m_pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_LESS);

	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	return S_OK;
}

/******************************************************************
終了処理関数
*******************************************************************/
void  CRenderer :: Uninit(void)
{
	//デバイスの破棄
	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//オブジェクトの破棄
	if(m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

/******************************************************************
更新処理関数
*******************************************************************/
void  CRenderer :: Update(void)
{
	//全更新
	CScene :: UpdateAll();

	CParticleManager::UpdateAll();
}

/******************************************************************
描画処理関数
*******************************************************************/
void  CRenderer :: Draw(void)
{
	//バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3Dによる描画の開始
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//オブジェクト全描画
		CScene::DrawAll();

		CParticleManager::DrawAll();

		//Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/******************************************************************
加算合成有効処理関数
*******************************************************************/
void CRenderer::SetAlphaBlend(void)
{
	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,false);
}

/******************************************************************
加算合成無効処理関数
*******************************************************************/
void CRenderer::SetDefaultBrend(void)
{
	m_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,true);
}

/******************************************************************
Zバッファ設定処理関数
*******************************************************************/
void CRenderer::SetzBuff(void)
{
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,true);
}
