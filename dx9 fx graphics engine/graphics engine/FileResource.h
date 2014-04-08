#pragma once

#include<string>

namespace graphicsengine
{
	namespace manager
	{
		class FileResource
		{
		private:
			fpos_t filePosition;
			FILE* file;
		protected:
			std::string *name;
		public:
			FileResource(void);
			FileResource(FileResource &fileResource);
		public:
			virtual ~FileResource(void);
			fpos_t GetFilePosition(void);
			virtual void SetFilePosition(FILE* file,fpos_t filePosition);
			std::string* GetString(void);
			void ResetFile(void);
			std::string Name()
			{
				return *name;
			}
			int GetInt(void);
			bool GetBool(void);
		public:
			char* GetCompressedData(int compressedSize, int decompressedSize);
		public:
			char* GetData(int length);
		public:
			float GetFloat(void);
		};
	}
}
