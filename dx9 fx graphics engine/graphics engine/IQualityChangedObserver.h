#pragma once
namespace graphicsengine
{
	namespace implementation
	{
		class IQualityChangedObserver
		{
		public:

			IQualityChangedObserver(void)
			{
			}
		public:
			virtual void QualityChanged(int newQuality) = 0;
			virtual ~IQualityChangedObserver(void)
			{
			}
		};
	}
}
