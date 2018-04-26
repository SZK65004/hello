//-----------------------------------------------
//カメラヘッダー
//              2017.1031
//------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>
#include "transform.h"

class CCamera : public transform
{

private:
	void Camera1();
	void Camera2();
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

};


D3DXMATRIX* GetView();


#endif