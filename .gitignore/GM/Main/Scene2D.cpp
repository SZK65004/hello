#include "scene2D.h"


#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//頂点の形を表している

//構造体
typedef struct
{
	D3DXVECTOR4 Position;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX2D;

//-----------------------------
//関数
//-----------------------------
CScene2D::CScene2D()
{
	//pDeviceにmainで使っていた値をもらうそれ以降pDeviceを使っていく
	pDevice = GetD3DDevice();
	m_Position = D3DXVECTOR3(10, 10, 1);
	m_Texture = NULL;
	m_VertexBuffer = NULL;

}

CScene2D::~CScene2D()
{

}


void CScene2D::SetTexture(CHAR * texturename)
{
	
	char name[50] = { "data/texture/" };
	//strcat(name, cc);

	HRESULT hr;

	hr = D3DXCreateTextureFromFile(pDevice,
		name,	//ファイル名
		&m_Texture);		//アドレスのアドレス

	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャの読み込みエラーです。", "警告", NULL);
		//return false;
	}
}


void CScene2D::Init()
{

	HRESULT hr;
	char name[] = "data/texture/face.png";
	hr = D3DXCreateTextureFromFile(pDevice,
		name,	//ファイル名
		&m_Texture);		//アドレスのアドレス
	
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファの作成エラーです。", "警告", NULL);
		
	}

	m_Height = 100;
	m_Width = 100;
	
}

void CScene2D::Uninit()
{
	if (m_Texture != NULL)
	{
		//空にする
		m_Texture->Release();
		m_Texture = NULL;
	}
}

void CScene2D::Update()
{

}

void CScene2D::Draw()
{
	VERTEX2D* pV;

	pDevice = GetD3DDevice();
	//毎回よぶ、グロ－バルにするとdeviceを失った場合に対応できない
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// VRAMのロック CPUから書き込み開始
	m_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	float u0 = 0;
	float v0 = 0;
	float u1 = (float)( m_Position.x) / m_Width;
	float v1 = (float)( m_Position.y) / m_Height;

	// POS
	pV[0].Position = D3DXVECTOR4(-0.5f + m_Position.x       	, -0.5 + m_Position.y, 1.0f, 1);
	pV[1].Position = D3DXVECTOR4(-0.5f + m_Position.x + m_Width, -0.5 + m_Position.y, 1.0f, 1);
	pV[2].Position = D3DXVECTOR4(-0.5f + m_Position.x, -0.5 + m_Position.y + m_Height, 1.0f, 1);
	pV[3].Position = D3DXVECTOR4(-0.5f + m_Position.x + m_Width, -0.5 + m_Position.y + m_Height, 1.0f, 1);


	// COLOR
	pV[0].color = D3DCOLOR_RGBA(255,255,255,255);
	pV[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pV[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pV[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	// UV
	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	// VRAMのアンロック CPUから書き込み終了
	m_VertexBuffer->Unlock();

	//ポリゴンの描画処理
	

	//FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX2D));

	pDevice->SetTexture(0, m_Texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
