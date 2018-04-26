#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <stdio.h>
#include "Polygon.h"
#include "scene2D.h"
#include "scene3D.h"
#include "camera.h"
#include "sceneModel.h"


//--------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDPROC defEditWndProc;

LPDIRECT3D9				g_pD3D = NULL;			//direct3D�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	//direct3D�f�o�C�X

BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//������
void Update();
void Draw();
void Uninit();

//�|�C���^
CScene2D *pScene2D;
CScene3D *pScene3D;
CSceneModel *pModel;
CCamera *pCamera;

#define CLASS_NAME		"sample"			//window�̖��O
#define WINDOW_NAME		"�E�B���h�E�̕\��"	//�\��
#define SCREEN_WIDTH	(800)				//window�̕�
#define SCREEN_HEIGHT	(600)				//window�̍���

//------------------------------------------------------------------------
//WInMain�֐�
//------------------------------------------------------------------------
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd
)
{
	WNDCLASSEX wcex = {
		//�������ł������@

		sizeof(WNDCLASSEX),				//�\���̂̃T�C�Y
		CS_VREDRAW | CS_HREDRAW,		//window�X�^�C��
		WndProc,						//window�v���V�[�W���̃A�h���X
		0,								//���͎g�p���Ȃ�
		0,
		hInstance,
		NULL,							//�A�C�R���ƂȂ�Ƃ���
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),		//windows�̐F
		NULL,
		CLASS_NAME,						//window�N���X��
		NULL,							//�~�j�A�C�R���̎w��
	};

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindowEx(
		0,								//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�o�^����Ă���N���X��
		WINDOW_NAME,					//�E�B���h�E��
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E�̉������̈ʒu
		CW_USEDEFAULT,					//�E�B���h�E�̉������̈ʒu
		SCREEN_WIDTH,					//�E�B���h�E�̕�
		SCREEN_HEIGHT,					//�E�B���h�E�̍���
		NULL,							//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h������͂��ꂪ�e�Ȃ̂łȂ�
		NULL,							// ���j���[�n���h���܂��͎q���ʎq
		hInstance,						// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL);							// �E�B���h�E�쐬�f�[�^

										//�E�B���h�E�̕\��
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime = 0;
	DWORD dwCurrentTime = 0;

	if (!Init(hInstance, hWnd, TRUE))
	{
		//exit(1);
	}
	//���b�Z�[�W���[�v

	//����\��ݒ�
	timeBeginPeriod(1);

	MSG msg;
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{//�Q�[���̏���(60fps�Ń��[�v����悤�ɂ���)
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{//�Q�[������
				dwExecLastTime = dwCurrentTime;
				Update();
				Draw();
			}

		}
	} while (msg.message != WM_QUIT);

	Uninit();
	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_COMMAND:

		break;

	case WM_DESTROY:PostQuitMessage(0);			//WM_QUIT���b�Z�[�W�̑��M
		break;

	case WM_LBUTTONDOWN:
	{

		break;
	}

	case WM_RBUTTONDOWN:
	{

		break;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:			//�����߂������ꂽ��
			nID = MessageBox(hWnd, "�I�����܂����H", "MENU", MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2);//�������̕����ŏ���
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

		}
		break;
	default:break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CRenderer::Init(hInstance, hWnd, bWindow);

	//PolygonInit();
	pCamera = new CCamera();
	pScene2D = new CScene2D();
	pScene3D = new CScene3D();
	pModel = new CSceneModel("cart.x");
	
	//������
	pCamera->Init();
	pScene2D->Init();
	pModel->Init();

	pScene2D->SetPosition(D3DXVECTOR3(100, 100, 0));
	pScene3D->SetData(D3DXVECTOR3 (0,0,0), D3DXVECTOR3 (0,1,0));
	pScene3D->SetTexture("sky.jpg");
	
	//pScene2D.SetTexture("face.png");
	return true;
}

void Uninit()
{
	
	//PolygonUninit();
	pCamera->Uninit();
	pScene3D->Uninit();
	pScene2D->Uninit();

	delete pCamera;
	delete pScene2D;
	delete pScene3D;

	CRenderer::Uninit();
}

void Update()
{

	pCamera->Update();
	pScene2D->Update();
	
}

void Draw()
{
	CRenderer::DrawBegin();
	pModel->SetPosition(D3DXVECTOR3(0, 1, 0));

	pScene2D->Draw();
	pScene3D->Bill();
	pScene3D->Draw();
	pModel->Draw();
	//PolygonDraw(0, 0, 0, 100, 100, 0,0, 100, 100, false);

	CRenderer::DrawEnd();
}
