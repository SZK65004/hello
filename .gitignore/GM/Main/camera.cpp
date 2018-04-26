#include "camera.h"
#include "main.h"
#include <Windows.h>
//-------------------------------------
//グローバル変数
//------------------------------------
static D3DXVECTOR3 g_at(0.0f, 0.0f, 0.0f);		//注視点
static D3DXVECTOR3 g_up(0.0f, 1.0f, 0.0f);		//アップベクトル　頭上を指すベクトル


static float Angle;
static D3DXMATRIX mtxView;		//ビュー行列

static D3DXVECTOR3 g_front;
static D3DXVECTOR3 g_right;
static D3DXVECTOR3 g_left;
static D3DXVECTOR3 g_back;


//定数
//移動速度、回転速度（ラジアン）
static float SPEED;
static float RSPEED;

static bool came = true;

//-------------------------------------
//プロトタイプ宣言
//------------------------------------
static void Camera1();
static void Camera2();

//--------------------------------------
//関数
//--------------------------------------
void CCamera::Init()
{
	SPEED = 0.3f;
	RSPEED = 0.03f;
	m_Position = { 0,2,-5 };
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	Camera2();

}

void Camera1()
{
	//
	//D3DXVECTOR3 X(1, 0, 0);
	//D3DXVECTOR3 Y(0, 1, 0);

	////playerと同期

	//float test = D3DXVec3Dot(&X, &Y);

	//D3DXMATRIX mtxProj;		//プロジェクション行列
	//						// += *player.GetPos() ;
	//g_at = GetClass()->pos;

	//m_Position = g_at + D3DXVECTOR3(0.0f, 2.0f, -3.3f);
	//D3DXMatrixLookAtLH(&mtxView, &m_Position, &g_at, &g_up);		//view行列を作る

	//														//プロジェクション（パースペクティブ）行列の作成
	//D3DXMatrixPerspectiveFovLH(&mtxProj, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000);

	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	////set
	//pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	//pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

}

void CCamera::Camera2()
{

	D3DXMATRIX mtxProj;		//プロジェクション行列


	D3DXMatrixLookAtLH(&mtxView, &m_Position, &g_at, &g_up);		//view行列を作る

															//プロジェクション（パースペクティブ）行列の作成
	D3DXMatrixPerspectiveFovLH(&mtxProj, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//回転行列を宣言（ｍｔｘ）
	D3DXMATRIX mtxAngle;

	//前方向を決める
	g_front = g_at - m_Position;

	//g_frontを正規化
	D3DXVec3Normalize(&g_front, &g_front);

	//右方向ベクトルを求める
	//				出力	左辺値	右辺値
	D3DXVec3Cross(&g_right, &g_up, &g_front);

	//右を正規化する今回は必要なし

	//作成
	D3DXVECTOR3 zVec = g_front;
	D3DXVECTOR3 xVec = g_right;
	D3DXVECTOR3 yVec = g_up;

	zVec.y = 0;
	yVec.x = 0;
	yVec.z = 0;

	//vecを正規化
	D3DXVec3Normalize(&zVec, &zVec);

	
	//set
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

}

void CCamera::Draw()
{

}

D3DXMATRIX* GetView()
{
	return &mtxView;
}