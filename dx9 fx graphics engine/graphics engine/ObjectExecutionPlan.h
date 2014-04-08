#pragma once

namespace graphicsengine
{
	namespace renderables
	{
		class IExecuteSemantic
		{
		public:
			virtual ~IExecuteSemantic() {};
			virtual void Execute() = 0;
		};

		/*!
			Takes ownership off all passed in executions. deletes them all here.
		*/
		class ObjectExecutionPlan
		{
		public:
			ObjectExecutionPlan(void);
			~ObjectExecutionPlan(void);
			void Execute();
			void AddExecute(IExecuteSemantic* execute);
		private:
			std::vector<IExecuteSemantic*> executes;
		};
	}
}
