#pragma once
#include<string>
#include "FileResource.h"

namespace graphicsengine
{
	namespace resources
	{
		class Resource : public graphicsengine::manager::FileResource
		{
		private:
			int refCount;
			unsigned long id;
			static unsigned long nextId;
		public:
			Resource(IDirect3DDevice9* d3d_device);
			virtual void BuildResource() = 0;
			virtual void FreeResource() = 0;
		public:
			virtual ~Resource(void);
		
		public:
			void AddRef(void);
			void SubRef(void);
			long GetId() const { return id;}
		protected:
			IDirect3DDevice9* d3d_device;
			int RefCount() { return refCount; }
		
		};
	}
}
