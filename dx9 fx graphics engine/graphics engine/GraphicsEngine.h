#pragma once
#include "igraphicsengine.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "RenderManager.h"


namespace graphicsengine
{
	namespace renderables
	{
		class Renderable;
	}
	namespace implementation
	{
		class IQualityChangedObserver;

		class GraphicsEngine :
			public IGraphicsEngine
		{
		public:
			GraphicsEngine(void);
			virtual ~GraphicsEngine(void);
			virtual void Initialize(WindowSettings* windowSettings);

		private:
			
			IDirect3D9* d3d;
			IDirect3DDevice9* d3d_device;
			D3DXMATRIX matView;
			D3DXMATRIX matProj;
			D3DXMATRIX matPara;
			D3DXMATRIX matViewProj;
			D3DXMATRIX matViewPara;
			D3DCOLOR backgroundColor;
			graphicsengine::manager::ResourceManager* resourceManager;
			graphicsengine::manager::RenderManager* renderManager;
			HANDLE renderEvent;
			HANDLE copyDataEvent;
			int screenWidth;
			int screenHeight;
			float aspectRatio;
			std::vector<graphicsengine::renderables::Renderable*> insertQueue;
			std::vector<graphicsengine::renderables::Renderable*> deleteQueue;
			LARGE_INTEGER starttime;
			LARGE_INTEGER endtime;
			double timerfreq;
			float time;
			int highestQuality;
			int quality;
			std::vector<IQualityChangedObserver*> qualityObservers;
		public:
			int refCount;
			virtual void setBackgroundColor(const float& red, const float& green,const float& blue);
			void Render();
			static unsigned int _stdcall RenderThread(void*);
			virtual void LoadData(const std::string& fileName);
			IDirect3DDevice9* getD3DDevice(void);
			virtual ITextBlock* CreateTextBlock(const std::string& prototypeName);
			virtual ISprite* CreateSprite(const std::string& prototypeName);
			static bool done;
			static HANDLE hThread;
			virtual void Commit();
			int GetScreenWidth() { return screenWidth;}
			int GetScreenHeight() { return screenHeight;}
			float GetAspectRatio() { return aspectRatio;}
			graphicsengine::manager::ResourceManager* GetResourceManager() { return resourceManager; }
			const D3DXMATRIX* View() const { return &matView;}
			const D3DXMATRIX* ViewProj() const { return &matViewProj;}
			const D3DXMATRIX* ViewPara() const { return &matViewPara;}
			float Time() { return time; }
		public:
			void AddToDeleteQueue(IRenderable *renderable);
		public:
			virtual int GetHighestValidQuality(void);
		public:
			virtual void SetQuality(int quality);
		public:
			void MarkQualityAsInvalid(int quality);
		public:
			void RegisterQualityChangeObserver(IQualityChangedObserver* observer);
		};
	}
}

#define GENGINE ((graphicsengine::implementation::GraphicsEngine*)IGraphicsEngine::getInstance())
