#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "transform.h"

class CScene2D:public transform
{
private:
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DTEXTURE9 m_Texture;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	float m_Width;
	float m_Height;
public :
	CScene2D();
	~CScene2D();

	void Init();
	void SetTexture(CHAR * texturename);
	void Uninit();
	void Update();
	void Draw();

};