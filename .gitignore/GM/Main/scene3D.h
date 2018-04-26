#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "transform.h"

enum RotateAxis
{
	AxisX,
	AxisY,
	AxisZ
};

class CScene3D :public transform
{
public:
	CScene3D();
	~CScene3D();
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATRIX mtxViewRotInv;
	D3DXMATRIX mtxRotation;
	D3DXMATRIX mtxScale;

	D3DXMATRIX mtxView;		//ビュー変換行列
	D3DXMATRIX mtxProjection;	//プロジェクション変換行列
	void SetTexture(const char * texturename);
	void Init() {};
	void Uninit();
	void Update();
	void Draw();
	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 vfront);
	void Rotate(RotateAxis type, float angle);
	void Bill();

private:
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	D3DXMATRIX m_mtxView;		//ビュー変換行列
	D3DXMATRIX m_mtxProjection;	//プロジェクション変換行列
	
};