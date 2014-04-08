#pragma once

namespace graphicsengine
{
	namespace resources
	{
		class Technique
		{
		private:
			int quality;
			int preference;
			D3DXHANDLE handle;
			bool valid;
			int numPasses;
		public:
			Technique(D3DXHANDLE handle,int quality,int preference,bool valid,int numPasses);
		public:
			virtual ~Technique(void);
		public:
			bool operator<(const Technique& other);
		public:
			Technique(const Technique &technique);
		public:
			void operator=(const Technique& technique);
			bool Valid() {return valid;}
			int NumPasses() const {return numPasses;}
		};
	}
}
