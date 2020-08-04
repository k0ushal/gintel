
/*

clang++ ex3.cpp $(llvm-config-10 --cxxflags) $(llvm-config-10 --ldflags --libs --system-libs) -lclang

*/

#include "CGintelEngine.h"

using gintel::modules::CGintelEngine;
using gintel::modules::SourceProject;

int main()
{
	CGintelEngine engine;

	engine.addProject(SourceProject{"Shape", "/home/koushal/projects/gintel/target_sources/shape"});
	engine.rebuildSymbolsDB();
	return 0;
}

