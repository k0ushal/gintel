
#include <filesystem>
#include <vector>
#include <string>
#include <map>

namespace gintel
{
	namespace modules
	{
		struct ProjectItem
		{
			std::string projectName;
			std::filesystem::path srcDirPath;
		};

		class CGintelEngine
		{
			public:
				void addProject(const ProjectItem& project);
				void start();
				
			public:
				CGintelEngine() = default;
				~CGintelEngine() = default;
				CGintelEngine(const CGintelEngine&) = delete;
				CGintelEngine& operator =(const CGintelEngine&) = delete;

			private:
				void processProject(
					const ProjectItem& project
					);

			private:
				static std::vector<std::string> SOURCE_FILE_EXTENSIONS;
				std::map<std::string, ProjectItem> m_projectsList;
		};
	}
}


