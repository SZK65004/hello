#pragma once
#include <d3dx9.h>
#include <d3d9.h>

class Light
{
public:
	enum
	{
		AMBIENT,
		DIRECTIONAL,
		SPECULAR,
		POINT,
		SPOT,
	};
private:
	D3DLIGHT9 light;
public:
	Light();
	~Light();
	void SetLightType(int LightName);
	void SetLightDiffuse(D3DCOLORVALUE diffuse);
	void SetLightDirection(D3DXVECTOR3 vector);
	void SetLightSettings();
private:
};