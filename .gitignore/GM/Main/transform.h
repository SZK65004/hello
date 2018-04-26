#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class transform
{
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Front;
	D3DXVECTOR3 m_Scale;

public:
	virtual void Init() {};
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


	void SetPosition(D3DXVECTOR3 pos);
	void LookAt();
};