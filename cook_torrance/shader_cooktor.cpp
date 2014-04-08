/******************************************************************************

 created by Eric Duhon
 Torrance and Cook Lighting

  This program needs more comments, but alas time has run out for the contest,
  so I apologize for any lack of clarity. Feel free to email me at
  duhone@ev1.net for any questions.
        
******************************************************************************/

#include "eb_effect.h"
#include "nvmesh.h"
#include "nvdevice.h"
#include "shader_cooktor.h"
#include "cooktor.h"

using namespace nv_objects;
using namespace std;


DECLARE_EFFECT_MAIN()

extern "C"
{

__declspec(dllexport) unsigned int GetNumEffects() { return 1; }

__declspec(dllexport) EBEffect* CreateEffect(unsigned int EffectNum)
{
	return new CShaderCook();
}

}





CShaderCook::CShaderCook()
	: m_pCubeTexture(NULL),
		m_pTeapot(NULL),
		m_pLight(NULL),
		m_pLight2(NULL),
		light_type(COOK_TORRANCE_CUBE),
		m_pNVDevice(NULL),
		mat_type(GOLD),
		light_color(WHITE),
		light_bright(FULL),
		m_pUI(NULL)
{
	m_strEffectName = "Cook and Torance Lighting";
	m_strEffectLocation = "Effects\\AdvancedLighting";
	m_strEffectVertexShader = GetFilePath("cooktor.nvv");
	m_strEffectPixelShader = GetFilePath("att_cube.nvp");
	m_strEffectVersion = "1.0";

}

CShaderCook::~CShaderCook()
{
	Free();	
}

void CShaderCook::UpdateProperties()
{

	
	
	EBEffect::UpdateProperties();
	EBEnumProperty* pEnumProp = new EBEnumProperty("ALight Options", OBJECT_MEMBER(light_type), EBTYPE_DWORD_PROP);
	
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Standard Phong Lighting", (DWORD)PHONG, EBTYPE_DWORD_PROP));
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Torrance and Cook Lighting", (DWORD)COOK_TORRANCE, EBTYPE_DWORD_PROP));
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Phong Cube Map", (DWORD)CUBEMAP, EBTYPE_DWORD_PROP));
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Torrance and Cook Cube Map", (DWORD)CTCUBEMAP, EBTYPE_DWORD_PROP));
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Standard Phong Lighting + Phong Cube Map", (DWORD)PHONG_CUBE, EBTYPE_DWORD_PROP));
	pEnumProp->AddEnumerant(new EBEnumValue(pEnumProp, "Torrance and Cook Lighting + Torrance and Cook Cube Map", (DWORD)COOK_TORRANCE_CUBE, EBTYPE_DWORD_PROP));

	AddProperty(pEnumProp);
    
	EBEnumProperty* pEnumProp2 = new EBEnumProperty("BMaterial Options", OBJECT_MEMBER(mat_type), EBTYPE_DWORD_PROP);
	pEnumProp2->AddEnumerant(new EBEnumValue(pEnumProp2, "Shiny Gold", (DWORD)GOLD, EBTYPE_DWORD_PROP));
	pEnumProp2->AddEnumerant(new EBEnumValue(pEnumProp2, "Dull Gold", (DWORD)GOLD2, EBTYPE_DWORD_PROP));
	pEnumProp2->AddEnumerant(new EBEnumValue(pEnumProp2, "Dull Blue Material", (DWORD)BLUEMAT, EBTYPE_DWORD_PROP));
	pEnumProp2->AddEnumerant(new EBEnumValue(pEnumProp2, "Silver", (DWORD)SILVER, EBTYPE_DWORD_PROP));
    pEnumProp2->AddEnumerant(new EBEnumValue(pEnumProp2, "Mirror", (DWORD)MIRROR, EBTYPE_DWORD_PROP));
 	AddProperty(pEnumProp2);
 

	EBEnumProperty* pEnumProp4 = new EBEnumProperty("DLight Brightness", OBJECT_MEMBER(light_bright), EBTYPE_DWORD_PROP);
	pEnumProp4->AddEnumerant(new EBEnumValue(pEnumProp4, "One Third Brightness", (DWORD)THIRD, EBTYPE_DWORD_PROP));
	pEnumProp4->AddEnumerant(new EBEnumValue(pEnumProp4, "Two Thirds Brightness", (DWORD)TWO_THIRD, EBTYPE_DWORD_PROP));
	pEnumProp4->AddEnumerant(new EBEnumValue(pEnumProp4, "Full Brightness", (DWORD)FULL, EBTYPE_DWORD_PROP));
	AddProperty(pEnumProp4);
 
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Standard Phong Lighting", GetFilePath("phong.nvv"), EBTYPE_STRING_PROP));
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Torrance and Cook Lighting", GetFilePath("cooktor.nvv"), EBTYPE_STRING_PROP));
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Phong Cube Map", GetFilePath("cubemap.nvv"), EBTYPE_STRING_PROP));
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Torrance and Cook Cube Map", GetFilePath("ctcubemap.nvv"), EBTYPE_STRING_PROP));
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Standard Phong (Lighting + Cube Map)", GetFilePath("phongcube.nvv"), EBTYPE_STRING_PROP));
	m_pVertexShaderEnum->AddEnumerant(new EBEnumValue(m_pVertexShaderEnum, "Torrance and Cook (Lighting + Cube Map)", GetFilePath("cooktorcube.nvv"), EBTYPE_STRING_PROP));
	
	m_pPixelShaderEnum->AddEnumerant(new EBEnumValue(m_pPixelShaderEnum, "Basic Pixel Shader", GetFilePath("basic.nvp"), EBTYPE_STRING_PROP));
	m_pPixelShaderEnum->AddEnumerant(new EBEnumValue(m_pPixelShaderEnum, "Lighting + Cubemap Pixel Shader", GetFilePath("att_cube.nvp"), EBTYPE_STRING_PROP));

	AddProperty(new EBProperty("Pause", OBJECT_MEMBER(paused), EBTYPE_BOOL_PROP));

	SetAboutInfo( NULL, _T("Created by Eric Duhon"),NULL);
	SetAboutInfo( _T("Date"), _T("June 2001"));

}

HRESULT CShaderCook::ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{


	return S_OK;
}

void CShaderCook::creatematerial()
{
	
	float brightness;
	if(light_bright == FULL) brightness = 1.0f;
	if(light_bright == TWO_THIRD) brightness = 0.66f;
	if(light_bright == THIRD) brightness = 0.33f;

	if(mat_type == GOLD)
		speccolor = D3DXVECTOR3(0.7701f,0.6792f,0.2627f);
	if(mat_type == GOLD2)
		speccolor =  D3DXVECTOR3(0.7701f,0.6792f,0.2627f);
	if(mat_type == BLUEMAT)
		speccolor =  D3DXVECTOR3(0.2f,0.3f,0.8f);
	if((mat_type == SILVER))
		speccolor =  D3DXVECTOR3(0.95f,0.93f,0.90f);
	if((mat_type == MIRROR))
		speccolor =  D3DXVECTOR3(1.0f,1.0f,1.0f);
	
	
	if(mat_type == GOLD)
		difcolor = D3DXVECTOR3(0.7701f/2,0.6792f/2,0.2627f/2);
	if(mat_type == GOLD2)
		difcolor =  D3DXVECTOR3(0.7701f/2,0.6792f/2,0.2627f/2);
	if(mat_type == BLUEMAT)
		difcolor =  D3DXVECTOR3(0.2f,0.3f,0.8f);
	if((mat_type == SILVER))
		difcolor =  D3DXVECTOR3(0.95f,0.93f,0.90f);
	if((mat_type == MIRROR))
		difcolor =  D3DXVECTOR3(1.0f,1.0f,1.0f);

	if(mat_type == GOLD)
		specamount = D3DXVECTOR3(0.9f,0.9f,0.9f);
	if(mat_type == GOLD2)
		specamount = D3DXVECTOR3(0.6f,0.6f,0.6f);
	if(mat_type == BLUEMAT)
		specamount = D3DXVECTOR3(0.25f,0.25f,0.25f);
	if((mat_type == SILVER))
		specamount = D3DXVECTOR3(0.6f,0.6f,0.6f);
	if((mat_type == MIRROR))
		specamount = D3DXVECTOR3(1.0f,1.0f,1.0f);
	specamount = specamount * brightness;

	if(mat_type == GOLD)
		matprop = D3DXVECTOR4(0.1f,0.05f,0.95f,75.0f);
	if(mat_type == GOLD2)	
		matprop =  D3DXVECTOR4(0.3f,0.4f,0.6f,60.0f);
	if(mat_type == BLUEMAT)	
		matprop =  D3DXVECTOR4(0.35f,0.75f,0.25f,40.0f);
	if(mat_type == SILVER)	
		matprop = D3DXVECTOR4(0.1f,0.2f,0.8f,70.0f);
	if(mat_type == MIRROR)	
		matprop =  D3DXVECTOR4(0.0f,0.0f,1.0f,100.0f);
	matprop.x *= brightness;

	if(mat_type == GOLD)
		cookmatprop = D3DXVECTOR3(25.0f,0.1f,1.3f);
	if(mat_type == GOLD2)
		cookmatprop =  D3DXVECTOR3(35.0f,0.0001f,0.7f);
	if(mat_type == BLUEMAT)
		cookmatprop =  D3DXVECTOR3(15.0f,0.0001f,0.4f);
	if((mat_type == SILVER))
		cookmatprop =  D3DXVECTOR3(45.0f,0.0001f,1.2f);
	if((mat_type == MIRROR))
		cookmatprop =  D3DXVECTOR3(35.0f,0.0001f,6.0f);

	m_pD3DDev->SetVertexShaderConstant(CV_COOK_M, cookmatprop, 1);


	m_pD3DDev->SetVertexShaderConstant(CV_MAT_PROP, matprop, 1);


	m_pD3DDev->SetPixelShaderConstant(CP_SPEC_AMOUNT, specamount, 1);

	m_pD3DDev->SetVertexShaderConstant(CV_COLOR_DIFUSE, difcolor, 1);

	m_pD3DDev->SetVertexShaderConstant(CV_COLOR_SPECULAR, speccolor, 1);
	m_pD3DDev->SetPixelShaderConstant(CP_COLOR_SPECULAR, speccolor, 1);

}


HRESULT CShaderCook::Initialize(IDirect3DDevice8* pDev)
{
	HRESULT hr;

	m_pD3DDev = pDev;
	pDev->AddRef();

	m_pNVDevice = new NVDevice(pDev);

	DWORD dwVBFlags = D3DUSAGE_WRITEONLY;

	vector<DWORD> Declaration;
	Declaration.push_back(D3DVSD_STREAM(0));
	Declaration.push_back(D3DVSD_REG(0, D3DVSDT_FLOAT3));
	Declaration.push_back(D3DVSD_END());

		vector<DWORD> Declaration2;
	Declaration2.push_back(D3DVSD_STREAM(0));
	Declaration2.push_back(D3DVSD_REG(0, D3DVSDT_FLOAT3));
	Declaration2.push_back(D3DVSD_REG(1, D3DVSDT_FLOAT3));
Declaration2.push_back(D3DVSD_END());

 
	hr = LoadAndCreateShader(GetFilePath("basic.vso"), &Declaration[0], 0, SHADERTYPE_VERTEX, &m_dwBasicShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("phong.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwPhongShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("cooktor.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwCookShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("cooktorcube.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwCookcubeShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("phongcube.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwPhongcubeShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("cubemap.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwCubeShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("ctcubemap.vso"), &Declaration2[0], 0, SHADERTYPE_VERTEX, &m_dwctCubeShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("att_cube.pso"), &Declaration2[0], 0, SHADERTYPE_PIXEL, &m_dwCubePixelShader);
	if (FAILED(hr))
		return hr;
	hr = LoadAndCreateShader(GetFilePath("basic.pso"), &Declaration2[0], 0, SHADERTYPE_PIXEL, &m_dwBasicPixelShader);
	if (FAILED(hr))
		return hr;

	m_pTeapot = new NVMesh();
	m_pLight = new NVMesh();
	m_pLight2 = new NVMesh();
	hr = m_pTeapot->Create(m_pNVDevice, GetFilePath("teapot1.x"));
	if (FAILED(hr))
	{
		m_strLastError = "Could not load teapot.x";
		return hr;
	}
	m_pTeapot->SetFVF(m_pNVDevice, D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pTeapot->SetVertexShader(m_dwPhongShader);

	hr = m_pLight->Create(m_pNVDevice, GetFilePath("sphere.x"));
	if (FAILED(hr))
	{
		m_strLastError = "Could not load sphere.x";
		return hr;
	}
	m_pLight->SetFVF(m_pNVDevice, D3DFVF_XYZ);
	m_pLight->SetVertexShader(m_dwBasicShader);

	hr = m_pLight2->Create(m_pNVDevice, GetFilePath("sphere.x"));
	if (FAILED(hr))
	{
		m_strLastError = "Could not load sphere.x";
		return hr;
	}
	m_pLight2->SetFVF(m_pNVDevice, D3DFVF_XYZ);
	m_pLight2->SetVertexShader(m_dwBasicShader);
	    // allocate our cube texture
	hr = D3DXCreateCubeTextureFromFileEx(m_pD3DDev, 
		GetFilePath("sky_cube_mipmap.dds").c_str(),
		D3DX_DEFAULT,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,
		0,
		NULL,
		NULL,
		&m_pCubeTexture);
	if (FAILED(hr))
	{
		m_strLastError = "Could not create sky_cube_mipmap.dds";
		return hr;
	}

	//initialize mouse UI
	RECT rect;
	rect.left = rect.top = 0;
	D3DVIEWPORT8 viewport;
	m_pD3DDev->GetViewport(&viewport);
	rect.bottom = viewport.Height;
	rect.right  = viewport.Width;
	m_pUI = new MouseUI((const RECT)rect);
	m_pUI->SetTranslationalSensitivityFactor(0.2f);



	m_pD3DDev->SetVertexShaderConstant(CV_ZERO, D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f), 1);
	m_pD3DDev->SetVertexShaderConstant(CV_ONE, D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 1);

	
	m_pTeapot->SetTexture(m_pCubeTexture);
m_pD3DDev->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
m_pD3DDev->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
m_pD3DDev->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
m_pD3DDev->SetTextureStageState(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
m_pD3DDev->SetTextureStageState(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
m_pD3DDev->SetTextureStageState(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

	m_pLight->SetTexture(NULL);
	m_pLight2->SetTexture(NULL);

	m_pTeapot->RestoreDeviceObjects(m_pNVDevice);
	m_pLight->RestoreDeviceObjects(m_pNVDevice);
	m_pLight2->RestoreDeviceObjects(m_pNVDevice);
	paused = false;
	return S_OK;

}

HRESULT CShaderCook::Free()
{
	SAFE_DELETE(m_pTeapot);
	SAFE_DELETE(m_pLight);
	SAFE_DELETE(m_pLight2);
	SAFE_RELEASE(m_pCubeTexture);
	SAFE_DELETE(m_pNVDevice);
	SAFE_DELETE(m_pUI);
	if (m_pD3DDev)
	{
		m_pD3DDev->DeleteVertexShader(m_dwBasicShader);
		m_pD3DDev->DeleteVertexShader(m_dwPhongShader);
		m_pD3DDev->DeleteVertexShader(m_dwCookShader);
		m_pD3DDev->DeleteVertexShader(m_dwPhongcubeShader);
		m_pD3DDev->DeleteVertexShader(m_dwCookcubeShader);
		m_pD3DDev->DeleteVertexShader(m_dwCubeShader);
		m_pD3DDev->DeleteVertexShader(m_dwctCubeShader);
		m_pD3DDev->DeletePixelShader(m_dwCubePixelShader);
		m_pD3DDev->DeletePixelShader(m_dwBasicPixelShader);
	
		SAFE_RELEASE(m_pD3DDev);
	}
	
	return S_OK;
}

HRESULT CShaderCook::Start()
{
	angle = 3.0f;
	light_distance = 30.0;
	return S_OK;
}

HRESULT CShaderCook::Tick(EBTimer* pTimer)
{
	HRESULT hr = S_OK;
	if(!paused) angle = pTimer->GetDuration()*0.15+1.0;
	if(!paused) light_distance = 45+20*sin(pTimer->GetDuration());
//set vertex shader	
	if(light_type == PHONG)	m_pTeapot->SetVertexShader(m_dwPhongShader);
	if(light_type == PHONG_CUBE)	m_pTeapot->SetVertexShader(m_dwPhongcubeShader);
	if(light_type == CUBEMAP)	m_pTeapot->SetVertexShader(m_dwCubeShader);
	if(light_type == CTCUBEMAP)	m_pTeapot->SetVertexShader(m_dwctCubeShader);
	if(light_type == COOK_TORRANCE)	m_pTeapot->SetVertexShader(m_dwCookShader);
	if(light_type == COOK_TORRANCE_CUBE)	m_pTeapot->SetVertexShader(m_dwCookcubeShader);
	if((light_type == CUBEMAP) || (light_type == CTCUBEMAP) || (light_type == PHONG_CUBE) || (light_type == COOK_TORRANCE_CUBE))	m_pD3DDev->SetPixelShader(m_dwCubePixelShader);
	else 	m_pD3DDev->SetPixelShader(m_dwBasicPixelShader);


	
D3DXMATRIX matWorld;
	D3DXMATRIX matWorldI;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXMATRIX matTemp;
	D3DXMATRIX matWorldView;
	D3DXMATRIX matWorldViewIT;
	D3DXMATRIX matWorldViewProj;

	hr = m_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0xAA, 0xAA, 0xAA ), 1.0, 0);

	m_pD3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	D3DXVECTOR3 vEyePt = D3DXVECTOR3( 0.0f, 0.0f, -2.4f );
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	
	creatematerial();



	m_pD3DDev->SetVertexShaderConstant(CV_COOK_CONSTANTS, D3DXVECTOR4(1.0f,0.25f,2.0f,3.141593f), 1);

//set light properties	
	D3DXVECTOR4 light_props;
	if(light_color == WHITE) light_props = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	if(light_color == RED) light_props = D3DXVECTOR4(1.0f,0.6f,0.6f,1.0f);
	if(light_color == GREEN) light_props = D3DXVECTOR4(0.6f,1.0f,0.6f,1.0f);
	if(light_color == BLUE) light_props = D3DXVECTOR4(0.6f,0.6f,1.0f,1.0f);
	if(light_bright == THIRD) light_props.w = 30.0f;
	if(light_bright == TWO_THIRD) light_props.w = 60.0f;
	if(light_bright == FULL) light_props.w = 90.0f;
	m_pD3DDev->SetVertexShaderConstant(CV_LIGHT_PROP, &light_props, 1);

	D3DXVECTOR4 light_props2;
	if(light_color == WHITE) light_props2 = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	if(light_color == RED) light_props2 = D3DXVECTOR4(1.0f,0.6f,0.6f,1.0f);
	if(light_color == GREEN) light_props2 = D3DXVECTOR4(0.6f,1.0f,0.6f,1.0f);
	if(light_color == BLUE) light_props2 = D3DXVECTOR4(0.6f,0.6f,1.0f,1.0f);
	if(light_bright == THIRD) light_props2.w = 20.0f;
	if(light_bright == TWO_THIRD) light_props2.w = 40.0f;
	if(light_bright == FULL) light_props2.w = 60.0f;
	m_pD3DDev->SetVertexShaderConstant(CV_LIGHT_PROP2, &light_props2, 1);

	// Set world rotation/translation
	D3DXMatrixMultiply( &matWorld, &m_pUI->GetRotationMatrix(), &m_pUI->GetTranslationMatrix() );

	// Move the loaded object to the middle and scale
	const NVBounds* pBounds = m_pTeapot->GetBounds();
	D3DXMatrixScaling(&matTemp, 1.0f / pBounds->m_fRadius, 1.0f / pBounds->m_fRadius, 1.0f / pBounds->m_fRadius);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTemp);

	D3DXMatrixTranslation(&matTemp, -pBounds->m_vecCenter.x, -pBounds->m_vecCenter.y, -pBounds->m_vecCenter.z);
	D3DXMatrixMultiply(&matWorld, &matTemp, &matWorld);

	// View
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUp);

	// Projection
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60.0f), 1.0f, 0.2f, 20.0f);

	D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProj, &matWorldView, &matProj);
	D3DXMatrixInverse(&matWorldViewIT, NULL, &matWorldView);

	// Projection to clip space
	D3DXMatrixTranspose(&matWorldViewProj, &matWorldViewProj);
	m_pD3DDev->SetVertexShaderConstant(CV_WORLDVIEWPROJ_0, &matWorldViewProj(0, 0), 4);
	D3DXMatrixTranspose(&matWorldViewProj, &matWorldViewProj);


	// Create a 3x3 inverse of the worldview for the light transformation back to model space
	D3DXMatrixInverse(&matWorldI, NULL, &matWorld);

	// Transform from world space to model space and point it away from the vertex towards the light
	// Light is pointing into the world
	D3DXVECTOR3 vecPos(sin(angle)*light_distance, 0.0f, cos(angle)*light_distance);
	D3DXVECTOR3 vecPos2(sin(angle+3.1459)*30, 0.0f, cos(angle+3.14)*30);
	D3DXVECTOR3 vecLight,vecLight2;// = -vecpos;
	D3DXVec3Normalize(&vecLight, &vecPos);
    D3DXVECTOR3 vecToEye(vEyePt - vLookatPt);
	D3DXVec3Normalize(&vecToEye, &vecToEye);
	D3DXVec3TransformNormal(&vecLight, &vecPos, &matWorldI);
	D3DXVec3TransformNormal(&vecLight2, &vecPos2, &matWorldI);
		D3DXVec3TransformNormal(&vEyePt, &vEyePt, &matWorldI);
	m_pD3DDev->SetVertexShaderConstant(CV_LIGHT1_POS, &vecLight.x, 1);
	m_pD3DDev->SetVertexShaderConstant(CV_LIGHT1_POS2, &vecLight2.x, 1);
	m_pD3DDev->SetVertexShaderConstant(CV_LIGHT1_VIEWPOS, &vEyePt.x, 1);
	
	m_pTeapot->Render(m_pNVDevice);
	
	
	D3DXMatrixTranslation(&matWorld, 0, 0,0);
	const NVBounds* pBounds2 = m_pLight->GetBounds();
	D3DXMatrixScaling(&matTemp, 1.0f / 50*pBounds2->m_fRadius, 1.0f / 50*pBounds2->m_fRadius, 1.0f / 50*pBounds2->m_fRadius);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTemp);

	D3DXMatrixTranslation(&matTemp, -pBounds2->m_vecCenter.x, -pBounds2->m_vecCenter.y, -pBounds2->m_vecCenter.z);
	D3DXMatrixMultiply(&matWorld, &matTemp, &matWorld);
	D3DXMatrixTranslation(&matTemp,vecPos.x,vecPos.y,vecPos.z);
	D3DXMatrixMultiply(&matWorld, &matTemp, &matWorld);

	D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProj, &matWorldView, &matProj);
		D3DXMatrixTranspose(&matWorldViewProj, &matWorldViewProj);
	m_pD3DDev->SetVertexShaderConstant(CV_WORLDVIEWPROJ_0, &matWorldViewProj(0, 0), 4);
	if(light_bright == FULL)
	{
		light_props.x = light_props.x * 1.0f;
		light_props.y = light_props.y * 1.0f;
		light_props.z = light_props.z * 1.0f;
	}
	if(light_bright == TWO_THIRD)
	{
		light_props.x = light_props.x * 0.9f;
		light_props.y = light_props.y * 0.9f;
		light_props.z = light_props.z * 0.9f;
	}
	if(light_bright == THIRD)
	{
		light_props.x = light_props.x * 0.8f;
		light_props.y = light_props.y * 0.8f;
		light_props.z = light_props.z * 0.8f;
	}

	m_pD3DDev->SetVertexShaderConstant(CV_COLOR_DIFUSE, light_props, 1);

	m_pD3DDev->SetPixelShader(m_dwBasicPixelShader);
	m_pLight->Render(m_pNVDevice);
	
	
		D3DXMatrixTranslation(&matWorld, 0, 0,0);
	const NVBounds* pBounds3 = m_pLight2->GetBounds();
	D3DXMatrixScaling(&matTemp, 1.0f / 50*pBounds3->m_fRadius, 1.0f / 50*pBounds3->m_fRadius, 1.0f / 50*pBounds3->m_fRadius);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTemp);

	D3DXMatrixTranslation(&matTemp, -pBounds3->m_vecCenter.x, -pBounds3->m_vecCenter.y, -pBounds3->m_vecCenter.z);
	D3DXMatrixMultiply(&matWorld, &matTemp, &matWorld);
	D3DXMatrixTranslation(&matTemp,vecPos2.x,vecPos2.y,vecPos2.z);
	D3DXMatrixMultiply(&matWorld, &matTemp, &matWorld);
	// View

	// Projection

	D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProj, &matWorldView, &matProj);
		D3DXMatrixTranspose(&matWorldViewProj, &matWorldViewProj);
	m_pD3DDev->SetVertexShaderConstant(CV_WORLDVIEWPROJ_0, &matWorldViewProj(0, 0), 4);

	m_pLight2->Render(m_pNVDevice);

	return hr;
}


void CShaderCook::MouseButton(HWND hWnd, eButtonID button, bool bDown, int x, int y)
{
	if(button == MOUSE_LEFTBUTTON)
	{
		if(bDown)
		{
			m_pUI->OnLButtonDown(x, y);
		}
		else
		{
			m_pUI->OnLButtonUp(x, y);
		}
	}
	return;
}

void CShaderCook::MouseMove(HWND hWnd, int x, int y)
{
	m_pUI->OnMouseMove(x, y);
	return;
}

void CShaderCook::Keyboard(DWORD dwKey, UINT nFlags, bool bDown)
{
	eEBKeyAction Action = TranslateEffectKey(dwKey, nFlags, bDown);
	
    switch ( Action )
    {
		case EB_HELP:
		{
			::MessageBoxEx( NULL, " Help : F1 - Help \n\n Home - Reset To Defaults \n\n W - Wireframe Toggle \n\n Space\\Pause - Toggle Pause/Resume \n\n Left Button & Mouse - Rotate Object\n\n Shift Left Button & Mouse - Pan Camera \n\n Ctrl Left Button & Mouse - Move Camera In & Out\n\n +\\- Change Bump Scale\n\n",
				   "Help", MB_ICONINFORMATION | MB_TASKMODAL, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ) );
		}
		break;

	

		case EB_RESET:
        {
            m_pUI->Reset();
 			m_dwEffectDirtyFlags |= EBEFFECT_DIRTY_PUBLICSTATE;
            
        }
		break;


        default :
            break;
    }
}

