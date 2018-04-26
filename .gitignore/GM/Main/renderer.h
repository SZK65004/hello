#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <windows.h>
#include <stdio.h>

class CRenderer
{
private:
	static LPDIRECT3D9 m_D3D;
	static LPDIRECT3DDEVICE9 m_D3DDevice;

public:
	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void DrawBegin();
	static void DrawEnd();
	static LPDIRECT3DDEVICE9 GetD3DDevice();
};