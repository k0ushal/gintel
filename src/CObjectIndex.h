
namespace gintel
{
	namespace storage
	{
		class CObjectIndex
		{
			public:
				void add(const std::string& key, std::any value);
				std::vector<std::any> search(const std::string& key);
				std::vector<std::any> typeAheadSuggestions(const std::string& key);

			public:
				CObjectIndex() = default;
				~CObjectIndex() = default;
		};
	}
}

