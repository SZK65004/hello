#include "scene2D.h"


#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//���_�̌`��\���Ă���

//�\����
typedef struct
{
	D3DXVECTOR4 Position;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX2D;

//-----------------------------
//�֐�
//-----------------------------
CScene2D::CScene2D()
{
	//pDevice��main�Ŏg���Ă����l�����炤����ȍ~pDevice���g���Ă���
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
		name,	//�t�@�C����
		&m_Texture);		//�A�h���X�̃A�h���X

	if (FAILED(hr)) {
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݃G���[�ł��B", "�x��", NULL);
		//return false;
	}
}


void CScene2D::Init()
{

	HRESULT hr;
	char name[] = "data/texture/face.png";
	hr = D3DXCreateTextureFromFile(pDevice,
		name,	//�t�@�C����
		&m_Texture);		//�A�h���X�̃A�h���X
	
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "���_�o�b�t�@�̍쐬�G���[�ł��B", "�x��", NULL);
		
	}

	m_Height = 100;
	m_Width = 100;
	
}

void CScene2D::Uninit()
{
	if (m_Texture != NULL)
	{
		//��ɂ���
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
	//�����ԁA�O���|�o���ɂ����device���������ꍇ�ɑΉ��ł��Ȃ�
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// VRAM�̃��b�N CPU���珑�����݊J�n
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

	// VRAM�̃A�����b�N CPU���珑�����ݏI��
	m_VertexBuffer->Unlock();

	//�|���S���̕`�揈��
	

	//FVF�i������g�p���钸�_���j�̐ݒ�
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX2D));

	pDevice->SetTexture(0, m_Texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
