
#include <clang-c/Index.h>
#include <string>

namespace gintel
{
	namespace modules
	{
		class CClangUtil
		{
			public:
				static std::string getCursorName(CXCursor cursor);
				static std::string getCursorFileLocation(CXCursor cursor);
		};
	}
}

