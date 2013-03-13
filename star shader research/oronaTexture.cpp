// oronaTexture.cpp: implementation of the CoronaTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "oronaTexture.h"
#include<vector>
#include "GraphicsEngine.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern GraphicsEngine *gengine;

CoronaTexture::CoronaTexture()
{
	D3DXCreateVolumeTexture(gengine->GetD3DDevice(),256,256,256,0,0,D3DFMT_G16R16F,D3DPOOL_MANAGED,&corona_texture);
	CreateDensity();
}

CoronaTexture::~CoronaTexture()
{

}

void CoronaTexture::CreateDensity()
{
	float level1[4][4][4];
	float level2[16][16][16];
	float level3[64][64][64];
	float level4[256][256][256];

	for(int count = 0;count < 4;count++)
	{
		for(int count2 = 0;count2 < 4;count2++)
		{
			for(int count3 = 0;count3 < 4;count3++)
			{
				level1[count][count2][count3] = (((float)rand())/RAND_MAX)*0.5f;
			}
		}
	}

	for(count = 0;count < 16;count++)
	{
		for(int count2 = 0;count2 < 16;count2++)
		{
			for(int count3 = 0;count3 < 16;count3++)
			{
				level2[count][count2][count3] = (((float)rand())/RAND_MAX)*0.25f;
			}
		}
	}

	for(count = 0;count < 64;count++)
	{
		for(int count2 = 0;count2 < 64;count2++)
		{
			for(int count3 = 0;count3 < 64;count3++)
			{
				level3[count][count2][count3] = (((float)rand())/RAND_MAX)*0.12f;
			}
		}
	}

	for(count = 0;count < 256;count++)
	{
		for(int count2 = 0;count2 < 256;count2++)
		{
			for(int count3 = 0;count3 < 256;count3++)
			{
				level4[count][count2][count3] = (((float)rand())/RAND_MAX)*0.05f;
			}
		}
	}

	for(count = 0;count < 256;count++)
	{
		for(int count2 = 0;count2 < 256;count2++)
		{
			for(int count3 = 0;count3 < 256;count3++)
			{
				float first,second,third,result,temp;
				temp = sample(count/256.0f,1.0f/4.0f,level1[floor(count)][floor(count2)][floor(count3)],level1[ceil(count)][floor(count2)][floor(count3)]);

			}
		}
	}


}

float CoronaTexture::sample(float position,float step_size,float first,float second)
{
	float factor1,factor2;
	factor1 = position
}