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
//プロトタイプ宣言
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDPROC defEditWndProc;

LPDIRECT3D9				g_pD3D = NULL;			//direct3Dインターフェース
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	//direct3Dデバイス

BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//初期化
void Update();
void Draw();
void Uninit();

//ポインタ
CScene2D *pScene2D;
CScene3D *pScene3D;
CSceneModel *pModel;
CCamera *pCamera;

#define CLASS_NAME		"sample"			//windowの名前
#define WINDOW_NAME		"ウィンドウの表示"	//表示
#define SCREEN_WIDTH	(800)				//windowの幅
#define SCREEN_HEIGHT	(600)				//windowの高さ

//------------------------------------------------------------------------
//WInMain関数
//------------------------------------------------------------------------
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd
)
{
	WNDCLASSEX wcex = {
		//初期化でいれる方法

		sizeof(WNDCLASSEX),				//構造体のサイズ
		CS_VREDRAW | CS_HREDRAW,		//windowスタイル
		WndProc,						//windowプロシージャのアドレス
		0,								//今は使用しない
		0,
		hInstance,
		NULL,							//アイコンとなるところ
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),		//windowsの色
		NULL,
		CLASS_NAME,						//windowクラス名
		NULL,							//ミニアイコンの指定
	};

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindowEx(
		0,								//拡張ウィンドウスタイル
		CLASS_NAME,						//登録されているクラス名
		WINDOW_NAME,					//ウィンドウ名
		WS_OVERLAPPEDWINDOW,			//ウィンドウスタイル
		CW_USEDEFAULT,					//ウィンドウの横方向の位置
		CW_USEDEFAULT,					//ウィンドウの横方向の位置
		SCREEN_WIDTH,					//ウィンドウの幅
		SCREEN_HEIGHT,					//ウィンドウの高さ
		NULL,							//親ウィンドウまたはオーナーウィンドウのハンドル今回はこれが親なのでなし
		NULL,							// メニューハンドルまたは子識別子
		hInstance,						// アプリケーションインスタンスのハンドル
		NULL);							// ウィンドウ作成データ

										//ウィンドウの表示
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime = 0;
	DWORD dwCurrentTime = 0;

	if (!Init(hInstance, hWnd, TRUE))
	{
		//exit(1);
	}
	//メッセージループ

	//分解能を設定
	timeBeginPeriod(1);

	MSG msg;
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{//ゲームの処理(60fpsでループするようにする)
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{//ゲーム処理
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

	case WM_DESTROY:PostQuitMessage(0);			//WM_QUITメッセージの送信
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
		case VK_ESCAPE:			//ｴｽｹｰﾌﾟが押されたら
			nID = MessageBox(hWnd, "終了しますか？", "MENU", MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2);//いいえの方が最初に
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
	
	//初期化
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
