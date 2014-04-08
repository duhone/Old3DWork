#include "StdAfx.h"
#include "ObjectExecutionPlan.h"
#include "FunctionObjects.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace std;
using namespace boost::lambda;
using namespace Syntax;
using namespace Syntax::Utility;

ObjectExecutionPlan::ObjectExecutionPlan(void)
{
}

ObjectExecutionPlan::~ObjectExecutionPlan(void)
{
	for_each(executes.begin(),executes.end(),DeleteFO<IExecuteSemantic*>());
	executes.clear();
}

void ObjectExecutionPlan::Execute()
{
	vector<IExecuteSemantic*>::iterator iterator = executes.begin();
	while(iterator != executes.end())
	{
		(*iterator)->Execute();
		iterator++;
	}
}

void ObjectExecutionPlan::AddExecute(IExecuteSemantic* execute)
{
	executes.push_back(execute);
}