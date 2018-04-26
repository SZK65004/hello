#include "scene3D.h"
#include <string.h>
#include "camera.h"
#include "light.h"

//-----------------------------------------------------------------------------
//グローバル
//-----------------------------------------------------------------------------
#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Nor;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;

//頂点の設定
static VERTEX3D V[] = {
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },	// 手前
{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
{ D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) },
{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),  D3DXVECTOR3(0.0, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },


};

static WORD Index[] = {
	0 , 1 , 2 ,//前
	1 , 3 , 2 ,

};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

CScene3D::CScene3D()
{
	m_Scale = { 5,5,1 };
}

CScene3D::~CScene3D()
{

}

void CScene3D::SetTexture(const char * texturename)
{

	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;

	//pDeviceにmainで使っていた値をもらうそれ以降pDeviceを使っていく
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	char name[30] = { "data/texture/" };
	char texname[20];
	
	strcpy_s(texname, texturename);
	strcat_s(name, texname);

	D3DXCreateTextureFromFile(pDevice,
		name,	//ファイル名
		&m_pTexture);		//アドレスのアドレス

	pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);


	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);

	VERTEX3D* pV;
	m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, &V[0], sizeof(VERTEX3D) * 4);
	m_pVertexBuffer->Unlock();

	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	//インデックスデータをpIndexに書き込み
	memcpy(pIndex, &Index[0], sizeof(Index));

	m_pIndexBuffer->Unlock();
}

void CScene3D::Uninit()
{
	if(m_pTexture != NULL)
	{
		//空にする
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CScene3D::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 vfront)
{
	m_Position = pos;
	m_Front = vfront;
}

void CScene3D::Update()
{


}

void CScene3D::Draw()
{
	D3DXMATRIX tmp;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//CreateVertex( texNum, dx, dy, dw, dh, tcx, tcy, tcw, tch);


	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetFVF(FVF_VERTEX3D);

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
	pDevice->SetIndices(m_pIndexBuffer);

	//
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	//D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
	//移動
	D3DXMatrixTranslation(&m_mtxWorld, m_Position.x, m_Position.y, m_Position.z);

	m_mtxWorld = mtxScale * mtxRotation * m_mtxWorld;

	//各種行列の設定（好きなところに描いて良い）
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	
	pDevice->SetRenderState(D3DRS_ALPHAREF, 30);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(40, 40, 80), 1, 0);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

void CScene3D::Bill()
{
	//回転
	D3DXMatrixInverse(&mtxRotation, NULL, GetView());

	//平行移動を削除
	mtxRotation._41 = 0;
	mtxRotation._42 = 0;
	mtxRotation._43 = 0;
}

//回転
void CScene3D::Rotate(RotateAxis type, float angle)
{
	switch (type)
	{
	case AxisX:
		D3DXMatrixRotationX(&mtxRotation, angle);

	case AxisY:
		D3DXMatrixRotationY(&mtxRotation, angle);

	case AxisZ:
		D3DXMatrixRotationZ(&mtxRotation, angle);
	}
}

