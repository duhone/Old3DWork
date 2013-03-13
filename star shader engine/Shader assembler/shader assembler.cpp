// shader assembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<d3dx9.h>


int main(int argc, char* argv[])
{
	LPD3DXBUFFER shader;
	D3DXAssembleShaderFromFile(argv[1],NULL,NULL,0,&shader,NULL);
	char newfile[256];
	strcpy(newfile,argv[1]);
	newfile[strlen(newfile)-3] = 0;
	strcat(newfile,"dsf");

	HANDLE filehandle = CreateFile(newfile,GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(filehandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,argv[0],"could not open HGF file",MB_OK);
		return 0;
	}
	HANDLE filemapping = CreateFileMapping(filehandle,NULL,PAGE_READWRITE | SEC_COMMIT,0,shader->GetBufferSize(),NULL);
	if(filemapping == NULL)
	{
		MessageBox(NULL,"name","could not map requested HGF file",MB_OK);
		return 0;
	}
	void *filepointer = MapViewOfFile(filemapping,FILE_MAP_WRITE,0,0,shader->GetBufferSize());
	if(filepointer == NULL)
	{
		MessageBox(NULL,"name","could not view requested HGF file",MB_OK);
		return 0;
	}

	memcpy(filepointer,shader->GetBufferPointer(),shader->GetBufferSize());

	UnmapViewOfFile(filepointer);
	CloseHandle(filemapping);
	CloseHandle(filehandle);

	return 0;
}
