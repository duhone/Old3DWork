
#ifndef __SHADER_REFLECT_H
#define __SHADER_REFLECT_H

#include "MouseUI.h"


typedef enum LightOptions
{
	PHONG = 0,
	PHONG_CUBE = 1,
	COOK_TORRANCE = 2,
	COOK_TORRANCE_CUBE = 3,
	CUBEMAP = 4,
	CTCUBEMAP = 5,
	LIGHTOPTIONS_FORCEDWORD = 0xFFFFFFFF
} LightOptions;


typedef enum MatOptions
{
	GOLD = 0,
	GOLD2 =1,
	BLUEMAT = 2,
	SILVER = 3,
    MIRROR = 4,
	MATOPTIONS_FORCEDWORD = 0xFFFFFFFF
} MatOptions;

typedef enum LightColor
{
	WHITE = 0,
	RED =1,
	BLUE = 2,
	GREEN = 3,
    LightColor_FORCEDWORD = 0xFFFFFFFF
} LightColor;

typedef enum LightBright
{
	THIRD = 0,
	TWO_THIRD =1,
	FULL = 2,
	LightBright_FORCEDWORD = 0xFFFFFFFF
} LightBright;




class CShaderCook : public EBEffect
{
public:
	CShaderCook();
	~CShaderCook();
	virtual void UpdateProperties();
	virtual HRESULT Initialize(LPDIRECT3DDEVICE8 pDev);
	virtual HRESULT Free();
	virtual HRESULT Start();
	virtual HRESULT Tick(EBTimer* pTimer);
	virtual HRESULT ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format);
	virtual void MouseButton(HWND hWnd, eButtonID button, bool bDown, int x, int y);
	virtual void MouseMove(HWND hWnd, int x, int y);
	virtual void Keyboard(DWORD dwKey, UINT nFlags, bool bDown);
	void creatematerial();
private:
	LightOptions light_type; 
	LightColor light_color;
	LightBright light_bright;
	MatOptions mat_type;
	bool paused;
	MouseUI* m_pUI;
	nv_objects::NVDevice* m_pNVDevice;
	nv_objects::NVMesh* m_pTeapot;
	nv_objects::NVMesh* m_pLight;
	nv_objects::NVMesh* m_pLight2;
	LPDIRECT3DCUBETEXTURE8 m_pCubeTexture;
	DWORD m_dwBasicShader;
	DWORD m_dwPhongShader;
	DWORD m_dwCookShader;
	DWORD m_dwCookcubeShader;
	DWORD m_dwPhongcubeShader;
	DWORD m_dwCubeShader;
	DWORD m_dwctCubeShader;
	DWORD m_dwCubePixelShader;
	DWORD m_dwBasicPixelShader;
	float angle;
	float light_distance;
	D3DXVECTOR3 speccolor;
	D3DXVECTOR3 difcolor;
	D3DXVECTOR3 specamount;
	D3DXVECTOR4 matprop;
	D3DXVECTOR3 cookmatprop;
	bool m_bMipMap;
	bool m_bWireframe;
};

#endif