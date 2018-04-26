#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "transform.h"

class CSceneModel : public transform
{
private:
	LPD3DXMESH m_Mesh = NULL;
	DWORD m_MaterialNum = 0;
	LPD3DXBUFFER m_Materials = NULL;
	D3DXMATRIX m_mtxWorld;		//ÉèÅ[ÉãÉhïœä∑çsóÒ

	LPDIRECT3DTEXTURE9 m_Texture[255];

	float m_Angle;

public:
	CSceneModel(const char * modelname);
	~CSceneModel() {};
	void Init();		
	void Uninit();
	void Update();
	void Draw();
};