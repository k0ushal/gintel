
#ifndef _CCLANGPARSER_H_
#define _CCLANGPARSER_H_

#include <filesystem>
#include <functional>
#include <string>
#include <memory>

namespace gintel
{
	namespace storage
	{
		class CSymbolInfo;
	}
	
	namespace modules
	{
		class CClangParser
		{
			public:
				void parseSourceFile(
					const std::filesystem::path &filePath,
					std::function<bool(std::shared_ptr<gintel::storage::CSymbolInfo>, void *)> callback,
					void *context);
		};
	}
}

#endif	//	_CCLANGPARSER_H_
