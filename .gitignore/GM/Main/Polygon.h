// ----------------------------------------------
//　ポリゴン描画
//        2017.06.05   鈴木翔斗
//-----------------------------------------------

#ifndef _POLUGON_H_
#define _POLUGON_H_

#include <d3d9.h>

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE;

//ﾃｸｽﾁｬデータ
static const TEXTURE g_aTexture[] = {
	{ "data/texture/title.png", 1280, 780},
	{ "data/texture/tuto.png", 1280, 780},
	{ "data/texture/result.png", 1280, 780},
	

};


//テクスチャ列挙
typedef enum TEXTURE_ENUM
{
	TEXTURE_CHAIR,
	TEXTURE_KOUGEKI,
	TEXTURE_PLAYER,
	TEXTURE_MAX
};
#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
/*
static const int TEXTURE_FILE_COUNT = sizeof(g_aTextureFileName) / sizeof(g_aTextureFileName[0])
*/
static LPDIRECT3DTEXTURE9 g_pTexture[TEXTURE_MAX];
static D3DCOLOR g_PolygonColor = D3DCOLOR_RGBA( 255, 255, 255, 255);

BOOL PolygonInit(void);		//描画
void PolygonUninit(void);	//
void PolygonUpdate(void);	//

void SetPolygonScale(float cx, float cy, float sx, float sy);
void SetPolygonColor(D3DCOLOR color);
void SetRotation(float cx, float cy, float ang);

				//テクすチャ番号  色　　　　　　　　座標　　　　　　　　　　　　　　　　切り取り座標の情報
void PolygonDraw( int texNum, float dx, float dy , float dw, float dh, int tcx, int tcy, int tcw, int tch, bool bAffine);
#endif // POLUGON_H_