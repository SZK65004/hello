#include "Renderer.h"
#include "main.h"

LPDIRECT3D9 CRenderer::m_D3D = NULL;

bool CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	//Direct3Dインターフェースの作成
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D == NULL)
	{
		return FALSE;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return FALSE;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	//デバイスのプレゼンテーションパラメータ
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//指定された容量０で埋め尽くす関数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//twoにすると描画２回で一回更新する

																//[デバイス作成処理]<描画>と頂点処理を行う
	if (FAILED(m_D3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_D3DDevice	//出来上がったデバイスが入ってるところ
	)))
	{
		MessageBox(hWnd, "あなたのＰＣじゃ動きません", "", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//レンダーステート
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//αブレンド
	//SRC : 今から描くもの。つまりポリゴンにテクスチャを張ったもの
	//DST : すでに描画されている画面のこと。
	//SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_a)
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//ポリゴンとテクスチャをどうブレンドするか
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//アルファの設定たち
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//サンプラーステート
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);//テクスチャアドレス外を参照したときにどうするのか
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);//WRAP反復になる CLAMP切り取り BORDER 範囲外だと指定した色で塗りつぶされる

	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

}

void CRenderer::Uninit()
{
	if (m_D3DDevice != NULL)
	{//作られていたらデバイスの開放
		m_D3DDevice->Release();//開放
		m_D3DDevice = NULL;
	}

	if (m_D3D != NULL)
	{//Direct3Dオブジェクトの開放
		m_D3D->Release();
		m_D3D = NULL;
	}
}
void CRenderer::DrawBegin()
{
	//1frameに一回
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 50, 100, 255), 1.0f, 0);
	m_D3DDevice->BeginScene();
}

void CRenderer::DrawEnd()
{
	//Direct3Dによる描画終了
	m_D3DDevice->EndScene();

	m_D3DDevice->Present(NULL, NULL, NULL, NULL);//一回だけ
}

LPDIRECT3DDEVICE9 CRenderer::GetD3DDevice()
{
	return m_D3DDevice;
}