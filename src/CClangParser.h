
#include <filesystem>
#include <functional>

namespace gintel
{
	namespace modules
	{
		class CClangParser
		{
			public:
				enum class ObjectType
				{
					GlobalFunction,
					Class,
					Method
				};

				struct ObjectLocationInfo
				{
					std::filesystem::path file;
				};

				struct ObjectInfo
				{
					ObjectType type;
					std::string name;
					ObjectLocationInfo location;
				};

			public:
				void parseSourceFile(
					const std::filesystem::path& filePath,
					std::function<bool(const CClangParser::ObjectInfo&, void*)> callback,
					void* context
					);
		};
	}
}

