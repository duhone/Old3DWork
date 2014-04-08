#include "StdAfx.h"
#include ".\sphere.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;

Sphere::Sphere(void)
{
}

Sphere::~Sphere(void)
{
}

LPD3DXMESH Sphere::CreateMappedSphere(IGraphicsEngine* gEngine,float fRad,int slices,int stacks)
{
	/*
	// create the sphere
	LPD3DXMESH mesh;
	if (FAILED(D3DXCreateSphere(pDev,fRad,slices,stacks,&mesh,NULL)))
		return NULL;

	// create a copy of the mesh with texture coordinates,
	// since the D3DX function doesn't include them
	LPD3DXMESH texMesh;
	if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM,FVF_VERTEX,pDev,&texMesh)))
		// failed, return un-textured mesh
		return mesh;

	// finished with the original mesh, release itsd
	mesh->Release();

	// lock the vertex buffer
	LPVERTEX pVerts;
	if (SUCCEEDED(texMesh->LockVertexBuffer(0,(BYTE **) &pVerts))) {

		// get vertex count
		int numVerts=texMesh->GetNumVertices();

		// loop through the vertices
		for (int i=0;i<numVerts;i++) {

			// calculate texture coordinates
			pVerts->tu=asinf(pVerts->norm.x)/D3DX_PI+0.5f;
			pVerts->tv=asinf(pVerts->norm.y)/D3DX_PI+0.5f;
	        
			// go to next vertex
			pVerts++;
		}

		// unlock the vertex buffer
		texMesh->UnlockVertexBuffer();
	}
	
	// return pointer to caller
	return texMesh;*/
	return NULL;
}