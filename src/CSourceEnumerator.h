#ifndef _CFSITERATOR_H_
#define _CFSITERATOR_H_

#include <filesystem>

namespace gintel
{
	namespace modules
	{
		class CSourceEnumerator
		{
			public:
				CSourceEnumerator() = default;
				~CSourceEnumerator() = default;
				CSourceEnumerator(const CSourceEnumerator&) = delete;
				CSourceEnumerator& operator =(const CSourceEnumerator&) = delete;

				void addEnumerableFileExtensions(
					std::vector<std::string>& extensions
					);

				void enumerate(
					const std::filesystem::path& dirPath,
					std::function<bool(const std::filesystem::path&)> callback
					);

			private:
				std::unordered_set<std::string> m_enumerableExtensions;
		};
	}
}

#endif	//	_CFSITERATOR_H_

