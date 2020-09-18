
#include <clang-c/Index.h>
#include <string>
#include "CClangUtil.h"

using gintel::modules::CClangUtil;

std::string CClangUtil::getCursorName(CXCursor cursor)
{
	auto cursorName {clang_getCursorDisplayName(cursor)};
	auto name {std::string(clang_getCString(cursorName))};
	clang_disposeString(cursorName);

	return name;
}

std::string CClangUtil::getCursorFileLocation(CXCursor cursor)
{
	CXSourceRange range {clang_getCursorExtent(cursor)};
	CXSourceLocation location {clang_getRangeStart(range)};

	CXFile file;
	clang_getFileLocation(location, &file, nullptr, nullptr, nullptr);

	auto fileName {clang_getFileName(file)};
	auto result {clang_getCString(fileName)};

	clang_disposeString(fileName);

	return result;
}

