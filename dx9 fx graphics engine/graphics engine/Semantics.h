#pragma once
#include<string>
#include <boost/algorithm/string.hpp>
#include "Singleton.h"

namespace graphicsengine
{
	namespace implementation
	{
		class Semantics : public Syntax::Utility::Singleton<Semantics>
		{
			friend Syntax::Utility::Singleton<Semantics>;
		public:
			enum SEMANTICS
			{
				Custom,

				//general
				World,
				WorldInverse,
				View,
				ViewInverse,
				WorldView,
				WorldViewInverse,
				WorldViewProjection,
				WorldViewParallel,
				Color,
				Texture0,

				//sprite
				FrameWidth,
				FrameNumber,

				NumSemantics
			};

			inline SEMANTICS LookupSemantic(std::string key)
			{
				boost::to_lower(key);
				stdext::hash_map<std::string,SEMANTICS>::iterator iterator = semanticLookup.find(key);
				if(iterator == semanticLookup.end())
					return Custom;
				else
					return static_cast<SEMANTICS>(iterator->second);

			};
		private:
			Semantics(void);
			~Semantics(void);
			stdext::hash_map<std::string,SEMANTICS> semanticLookup;
		};
	}
}
