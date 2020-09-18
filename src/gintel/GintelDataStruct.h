#ifndef _GINTEL_DATASTRUCT_H_
#define _GINTEL_DATASTRUCT_H_

#include <string>
#include <filesystem>

namespace gintel
{
    namespace modules
    {
		struct SourceProject
		{
			std::string projectName;
			std::filesystem::path srcDirPath;
		};
    }
}

#endif  //  _GINTEL_DATASTRUCT_H_
