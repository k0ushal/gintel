
#include <filesystem>

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
				
			public:
				CGintelEngine() = default;
				~CGintelEngine() = default;
				CGintelEngine(const CGintelEngine&) = delete;
				CGintelEngine& operator =(const CGintelEngine&) = delete;

			private:
				void processProject(
					const ProjectItem& project
					);
		};
	}
}


