#include "sceneModel.h"
#include "sceneModel.h"
#include "light.h"
#include "renderer.h"
//-------------------------------------
//グローバル変数
//-------------------------------------

Light *pLight;
//テクスチャ略

//-------------------------------------
//関数
//-------------------------------------
CSceneModel::CSceneModel(const char * modelname)
{
	char name[30] = { "data/" };
	char texname[20];

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	strcpy_s(texname, modelname);
	strcat_s(name, texname);

	HRESULT hr;
	LPD3DXBUFFER pAdjacency;
	hr = D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, pDevice, &pAdjacency, &m_Materials, NULL, &m_MaterialNum, &m_Mesh);

	hr = m_Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);
	LPD3DXMESH pCloneMesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];
	m_Mesh->GetDeclaration(elements);
	m_Mesh->CloneMesh(D3DXMESH_MANAGED, elements, pDevice, &pCloneMesh);

	m_Mesh->Release();
	m_Mesh = pCloneMesh;

	LPD3DXMATERIAL pMaterials = (LPD3DXMATERIAL)m_Materials->GetBufferPointer();
	char str1[30][255];
	char str2[255] = "data/texture/";
	char tmp[] = "data/texture/";

	for (int i = 0; i < m_MaterialNum; i++)
	{
		strcpy_s(str1[i], (char*)pMaterials[i].pTextureFilename);
		strcat_s(str2, str1[i]);
		D3DXCreateTextureFromFile(pDevice,
			str2,				//ファイル名
			&m_Texture[i]);	//アドレスのアドレス
		strcpy_s(str2, tmp);
	}
}

void CSceneModel::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	pLight = new Light;

	



	m_Position = {0,0,0};
	m_Scale = { 3,1,1 };
	m_Angle = 0;
}

void CSceneModel::Uninit()
{

}

void CSceneModel::Update()
{

}

void CSceneModel::Draw()
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	pLight->SetLightType(D3DLIGHT_DIRECTIONAL);

	//CreateVertex( texNum, dx, dy, dw, dh, tcx, tcy, tcw, tch);


	D3DXMATRIX tmp;

	D3DXMatrixScaling(&m_mtxWorld, m_Scale.x, m_Scale.y, m_Scale.z);

	//拡縮

	//回転
	D3DXMatrixRotationY(&tmp, m_Angle);
	tmp = m_mtxWorld * tmp;

	//移動
	D3DXMatrixTranslation(&m_mtxWorld, m_Position.x, m_Position.y, m_Position.z);
	m_mtxWorld = tmp * m_mtxWorld;

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	for (int i = 0; i<m_MaterialNum; i++)
	{

		pDevice->SetTexture(0, m_Texture[i]);
		//マテリアルのセット、テクスチャのセット
		m_Mesh->DrawSubset(i);
	}
}