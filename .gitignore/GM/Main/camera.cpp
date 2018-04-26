#include "camera.h"
#include "main.h"
#include <Windows.h>
//-------------------------------------
//�O���[�o���ϐ�
//------------------------------------
static D3DXVECTOR3 g_at(0.0f, 0.0f, 0.0f);		//�����_
static D3DXVECTOR3 g_up(0.0f, 1.0f, 0.0f);		//�A�b�v�x�N�g���@������w���x�N�g��


static float Angle;
static D3DXMATRIX mtxView;		//�r���[�s��

static D3DXVECTOR3 g_front;
static D3DXVECTOR3 g_right;
static D3DXVECTOR3 g_left;
static D3DXVECTOR3 g_back;


//�萔
//�ړ����x�A��]���x�i���W�A���j
static float SPEED;
static float RSPEED;

static bool came = true;

//-------------------------------------
//�v���g�^�C�v�錾
//------------------------------------
static void Camera1();
static void Camera2();

//--------------------------------------
//�֐�
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

	////player�Ɠ���

	//float test = D3DXVec3Dot(&X, &Y);

	//D3DXMATRIX mtxProj;		//�v���W�F�N�V�����s��
	//						// += *player.GetPos() ;
	//g_at = GetClass()->pos;

	//m_Position = g_at + D3DXVECTOR3(0.0f, 2.0f, -3.3f);
	//D3DXMatrixLookAtLH(&mtxView, &m_Position, &g_at, &g_up);		//view�s������

	//														//�v���W�F�N�V�����i�p�[�X�y�N�e�B�u�j�s��̍쐬
	//D3DXMatrixPerspectiveFovLH(&mtxProj, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000);

	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	////set
	//pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	//pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

}

void CCamera::Camera2()
{

	D3DXMATRIX mtxProj;		//�v���W�F�N�V�����s��


	D3DXMatrixLookAtLH(&mtxView, &m_Position, &g_at, &g_up);		//view�s������

															//�v���W�F�N�V�����i�p�[�X�y�N�e�B�u�j�s��̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProj, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//��]�s���錾�i�������j
	D3DXMATRIX mtxAngle;

	//�O���������߂�
	g_front = g_at - m_Position;

	//g_front�𐳋K��
	D3DXVec3Normalize(&g_front, &g_front);

	//�E�����x�N�g�������߂�
	//				�o��	���Ӓl	�E�Ӓl
	D3DXVec3Cross(&g_right, &g_up, &g_front);

	//�E�𐳋K�����鍡��͕K�v�Ȃ�

	//�쐬
	D3DXVECTOR3 zVec = g_front;
	D3DXVECTOR3 xVec = g_right;
	D3DXVECTOR3 yVec = g_up;

	zVec.y = 0;
	yVec.x = 0;
	yVec.z = 0;

	//vec�𐳋K��
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