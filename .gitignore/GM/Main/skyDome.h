#pragma once

#include "transform.h"
#include "sceneModel.h"
#include <d3d9.h>
#include <d3dx9.h>

class CSkydome : public transform
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	CSceneModel *pModel;		//3dModel
};