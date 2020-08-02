
#include <algorithm>
#include <unordered_set>
#include <string>
#include <filesystem>
#include <functional>
#include <iostream>
#include "CSourceEnumerator.h"

using std::cout;
using std::endl;
using gintel::modules::CSourceEnumerator;


void CSourceEnumerator::enumerate(
	const std::filesystem::path& dirPath,
	std::function<bool(const std::filesystem::path&)> callback
	)
{
	for (auto& dirEntry: std::filesystem::recursive_directory_iterator(dirPath))
	{
		//	call callback only for source file extensions.
		if (dirEntry.is_regular_file())
		{
			if (m_enumerableExtensions.count(dirEntry.path().extension().string()) > 0)
			{
				auto ret {callback(dirEntry.path())};
				if (!ret)
				{
					//	terminate enumeration if callback returns false
					return;
				}
			}
		}
	}
}

void CSourceEnumerator::addEnumerableFileExtensions(
	std::vector<std::string>& extensions
	)
{
	std::for_each(const auto& e: extensions)
	{
		m_enumerableExtensions.emplace(e);
	}
}



#if 0
int main()
{
	CSourceEnumerator se;

	se.enumerate("/home/koushal/projects/gintel", [](const std::filesystem::path&) -> bool {
		return true;
	});

	return 0;
}
#endif
