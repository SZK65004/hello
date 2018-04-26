//-----------------------------------------------------
// ポリゴン描画
//-----------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "Polygon.h"


//グローバル
//static LPDIRECT3DTEXTURE9 g_pTexture[2] = { NULL, NULL};
//LPDIRECT3DDEVICE9		pDevice = NULL;	//direct3Dデバイス
static float g_uv;

static float g_fScaleX = 1.0f;
static float g_fScaleY = 1.0f;
static float g_fScaleOffsetX = 0.0f;
static float g_fScaleOffsetY = 0.0f;
static float g_fTestScale = 1.0f;
static float g_fScaleAdd = 0.0f;
static float g_fAngle = 0.0f;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static float g_fRotationOffsetX = 0.0f;
static float g_fRotationOffsetY = 0.0f;


//構造体
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//頂点の形を表している

// 関数プロトタイプ宣言
static void CreateVertex(int texNum, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
static void CreateVertexAffine(int texNum, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

BOOL PolygonInit(void)
{
	//pDeviceにmainで使っていた値をもらうそれ以降pDeviceを使っていく
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	if( pDevice == NULL) { return FALSE ;}
	
	HRESULT hr;

	for( int i = 0; i < TEXTURE_MAX ;i++){
	
	hr = D3DXCreateTextureFromFile( pDevice, 
										g_aTexture[i].fileName,	//ファイル名
										&g_pTexture[i]);		//アドレスのアドレス
		if(FAILED(hr)) {
			MessageBox(NULL, "テクスチャの読み込みエラーです。","警告",NULL);
			return false;
		}

	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファの作成エラーです。", "警告", NULL);
		return false;
	}

	return TRUE;
}

void PolygonUninit(void)
{
	if (g_pVertexBuffer != NULL) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pTexture[0] != NULL) {
		g_pTexture[0]->Release();
		g_pTexture[0] = NULL;
	}

	if(g_pTexture[1] != NULL)
	{
		g_pTexture[1]->Release();
		g_pTexture[1] = NULL;
	}

}

void PolygonUpdate(void)
{
	
	//g_uv += 0.01;
	

}

void SetPolygonColor(D3DCOLOR color)
{
	g_PolygonColor = color;
}

void SetPolygonScale(float cx, float cy, float sx, float sy)
{
	g_fScaleOffsetX = cx;
	g_fScaleOffsetY = cy;
	g_fScaleX = sx;
	g_fScaleY = sy;
}

void SetRotation(float cx, float cy, float ang)
{
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
	g_fAngle = ang;
	
}

void PolygonDraw( int texNum, float dx, float dy , float dw, float dh, int tcx, int tcy, int tcw, int tch, bool bAffine)
{
	//毎回よぶ、グロ－バルにするとdeviceを失った場合に対応できない
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	float u0 = (float)tcx / g_aTexture[texNum].width;
	float v0 = (float)tcy / g_aTexture[texNum].height;
	float u1 = (float)(tcx + tcw) / g_aTexture[texNum].width;
	float v1 = (float)(tcy + tch) / g_aTexture[texNum].height;

	if( bAffine) {
		CreateVertexAffine(texNum, dx, dy, dw, dh, tcx, tcy, tcw, tch);
	}
	else
	{
	//ポリゴンの描画処理
		CreateVertex(texNum, dx, dy, dw, dh, tcx, tcy, tcw, tch);
		
	}
	//FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTexture[texNum]);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	/*
	pDevice->SetTexture(0, g_pTexture[1]);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vtx[4], sizeof(VERTEX_2D));
	*/

}

static void CreateVertex(int texNum, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	// VRAMのロック CPUから書き込み開始
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	float u0 = (float)tcx / g_aTexture[texNum].width;
	float v0 = (float)tcy / g_aTexture[texNum].height;
	float u1 = (float)(tcx + tcw) / g_aTexture[texNum].width;
	float v1 = (float)(tcy + tch) / g_aTexture[texNum].height;

	// POS
	pV[0].pos = D3DXVECTOR4(-0.5f + dx, -0.5 + dy, 1.0f, 1);
	pV[1].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5 + dy, 1.0f, 1);
	pV[2].pos = D3DXVECTOR4(-0.5f + dx, -0.5 + dy + dh, 1.0f, 1);
	pV[3].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5 + dy + dh, 1.0f, 1);


	// COLOR
	pV[0].color = g_PolygonColor;
	pV[1].color = g_PolygonColor;
	pV[2].color = g_PolygonColor;
	pV[3].color = g_PolygonColor;

	/*
	pV[0].color = 
	pV[1].color = 
	pV[2].color = 
	pV[3].color = g_PolygonColor;

	でも同じことができる。
	*/


	// UV
	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	// VRAMのアンロック CPUから書き込み終了
	g_pVertexBuffer->Unlock();
}

static void CreateVertexAffine(int texNum, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	// VRAMのロック CPUから書き込み開始
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	
	float x   = ( 0.0f - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX;
	float x_w = ( dw   - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX;
	float y   = ( 0.0f - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY;
	float y_h = ( dh   - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY;

	float fRotationOffsetX = ( g_fRotationOffsetX - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX ;
	float fRotationOffsetY = ( g_fRotationOffsetY - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY;

	x   += ( 0.0f - fRotationOffsetX );
	x_w += (    - fRotationOffsetX );
	y   += ( 0.0f - fRotationOffsetY );
	y_h += (    - fRotationOffsetY );

	dx += fRotationOffsetX - 0.5;
	dy += fRotationOffsetY - 0.5;

	float u0 = (float)tcx / g_aTexture[texNum].width;
	float v0 = (float)tcy / g_aTexture[texNum].height;
	float u1 = (float)(tcx + tcw) / g_aTexture[texNum].width;
	float v1 = (float)(tcy + tch) / g_aTexture[texNum].height;

	// POS
	pV[0].pos = D3DXVECTOR4(x   *cosf(g_fAngle) - y * sinf(g_fAngle) + dx ,
							x   *sinf(g_fAngle) + y * cosf(g_fAngle) + dy , 1.0f, 1);

	pV[1].pos = D3DXVECTOR4(x_w *cosf(g_fAngle) - y * sinf(g_fAngle) + dx,
							x_w *sinf(g_fAngle) + y * cosf(g_fAngle) + dy, 1.0f, 1);

	pV[2].pos = D3DXVECTOR4(x * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx,
							x * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 1.0f, 1);

	pV[3].pos = D3DXVECTOR4(x_w * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx,
							x_w * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 1.0f, 1);


	// COLOR
	pV[0].color = g_PolygonColor;
	pV[1].color = g_PolygonColor;
	pV[2].color = g_PolygonColor;
	pV[3].color = g_PolygonColor;

	/*
	pV[0].color = 
	pV[1].color = 
	pV[2].color = 
	pV[3].color = g_PolygonColor;

	でも同じことができる。
	*/


	// UV
	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	// VRAMのアンロック CPUから書き込み終了
	g_pVertexBuffer->Unlock();
}