#include "Renderer.h"
#include "main.h"

LPDIRECT3D9 CRenderer::m_D3D = NULL;

bool CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�[�t�F�[�X�̍쐬
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D == NULL)
	{
		return FALSE;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return FALSE;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//�w�肳�ꂽ�e�ʂO�Ŗ��ߐs�����֐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//two�ɂ���ƕ`��Q��ň��X�V����

																//[�f�o�C�X�쐬����]<�`��>�ƒ��_�������s��
	if (FAILED(m_D3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_D3DDevice	//�o���オ�����f�o�C�X�������Ă�Ƃ���
	)))
	{
		MessageBox(hWnd, "���Ȃ��̂o�b���ᓮ���܂���", "", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//�����_�[�X�e�[�g
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//���u�����h
	//SRC : ������`�����́B�܂�|���S���Ƀe�N�X�`���𒣂�������
	//DST : ���łɕ`�悳��Ă����ʂ̂��ƁB
	//SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_a)
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//�|���S���ƃe�N�X�`�����ǂ��u�����h���邩
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//�A���t�@�̐ݒ肽��
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//�T���v���[�X�e�[�g
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);//�e�N�X�`���A�h���X�O���Q�Ƃ����Ƃ��ɂǂ�����̂�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);//WRAP�����ɂȂ� CLAMP�؂��� BORDER �͈͊O���Ǝw�肵���F�œh��Ԃ����

	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

}

void CRenderer::Uninit()
{
	if (m_D3DDevice != NULL)
	{//����Ă�����f�o�C�X�̊J��
		m_D3DDevice->Release();//�J��
		m_D3DDevice = NULL;
	}

	if (m_D3D != NULL)
	{//Direct3D�I�u�W�F�N�g�̊J��
		m_D3D->Release();
		m_D3D = NULL;
	}
}
void CRenderer::DrawBegin()
{
	//1frame�Ɉ��
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 50, 100, 255), 1.0f, 0);
	m_D3DDevice->BeginScene();
}

void CRenderer::DrawEnd()
{
	//Direct3D�ɂ��`��I��
	m_D3DDevice->EndScene();

	m_D3DDevice->Present(NULL, NULL, NULL, NULL);//��񂾂�
}

LPDIRECT3DDEVICE9 CRenderer::GetD3DDevice()
{
	return m_D3DDevice;
}