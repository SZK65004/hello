#include "light.h"
#include "main.h"

Light::Light()
{
	// Clean up light memory.
	ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = { 0.0f, -1.0f, 0.5f };
	light.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f }; // Color
	light.Ambient = { 1.0f, 1.0f, 1.0f ,1.00f };
	//light.Position = { 0.0f, 0.0f, 0.0f };
	light.Range = 1000.00f;
}

Light::~Light()
{
}

void Light::SetLightType(int LightName)
{
	switch (LightName)
	{
	case AMBIENT:
		break;
	case DIRECTIONAL:
		light.Type = D3DLIGHT_DIRECTIONAL;
		break;
	case SPECULAR:
		light.Type = D3DLIGHT_FORCE_DWORD;
		break;
	case POINT:
		light.Type = D3DLIGHT_POINT;
		break;
	case SPOT:
		light.Type = D3DLIGHT_SPOT;
		break;
	default:
		break;
	}

}

void Light::SetLightDiffuse(D3DCOLORVALUE diffuse)
{
	light.Diffuse = diffuse;
}

void Light::SetLightDirection(D3DXVECTOR3 vector)
{
	D3DXVec3Normalize(&vector, &vector);
	light.Direction = vector;
	return;
}

void Light::SetLightSettings()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetLight(0, &light);  // Allocatable 0 - 3 Light.
	pDevice->LightEnable(0, TRUE); // Activate Light[id].
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

