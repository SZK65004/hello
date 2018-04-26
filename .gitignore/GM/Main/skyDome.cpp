#include "skyDome.h"

void CSkydome::Init()
{
	pModel = new CSceneModel("cart.x");
	
}

void CSkydome::Uninit()
{
	pModel->Uninit();
	delete pModel;
}

void CSkydome::Update()
{

}

void CSkydome::Draw()
{

}