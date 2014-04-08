#include "StdAfx.h"
#include "FileResource.h"
#include "LzmaDecode.h"

using namespace graphicsengine;
using namespace graphicsengine::manager;
using namespace std;

FileResource::FileResource(FileResource &fileResource)
{
	name = new string();
	name->append(*fileResource.name);
}

FileResource::FileResource(void)
{
}

FileResource::~FileResource(void)
{
	delete name;
}

fpos_t FileResource::GetFilePosition(void)
{
	return filePosition;
}

void FileResource::SetFilePosition(FILE* file,fpos_t filePosition)
{
	this->filePosition = filePosition;
	this->file = file;
	name = GetString();
	fgetpos(file,&(this->filePosition));
	
}

std::string *FileResource::GetString(void)
{
	unsigned char temp;
	fread(&temp,sizeof(unsigned char),1,file);
	int size = temp & 0x7f;
	if(temp > 127)
	{
		fread(&temp,sizeof(byte),1,file);
		size |= ((temp & 0x7f) << 7);
	}
	char *result = new char[size+1];
	result[size] = 0;
	fread(result,1,size,file);
	return new string(result);
}

void FileResource::ResetFile(void)
{
	fseek(file,(long)filePosition,SEEK_SET);
}

int FileResource::GetInt(void)
{
	int result;
	fread(&result,4,1,file);
	return result;
}

bool FileResource::GetBool(void)
{
	bool result;
	fread(&result,1,1,file);
	return result;
}
char* FileResource::GetCompressedData(int compressedSize, int decompressedSize)
{
	CLzmaDecoderState state;
	unsigned char* props = (unsigned char*)GetData(5);
	unsigned char* inStream = (unsigned char*)GetData(compressedSize);
	unsigned char* result = new unsigned char[decompressedSize];
	unsigned int outProcessed = 0;
	unsigned int inProcessed = 0;
	LzmaDecodeProperties(&state.Properties, props, LZMA_PROPERTIES_SIZE);
	state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));

    if (state.Properties.DictionarySize == 0)
		state.Dictionary = 0;
    else
		state.Dictionary = (unsigned char *)malloc(state.Properties.DictionarySize);
	LzmaDecoderInit(&state);
    
	LzmaDecode(&state,inStream,compressedSize,&inProcessed,result, decompressedSize, &outProcessed);

	delete[] inStream;
	delete[] props;
	return (char*)result;
}

char* graphicsengine::manager::FileResource::GetData(int length)
{
	char* buffer = new char[length];
	fread(buffer,1,length,file);
	return buffer;
}

float graphicsengine::manager::FileResource::GetFloat(void)
{
	float result;
	fread(&result,4,1,file);
	return result;
}
