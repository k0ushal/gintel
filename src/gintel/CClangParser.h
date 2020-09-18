
#ifndef _CCLANGPARSER_H_
#define _CCLANGPARSER_H_

#include <filesystem>
#include <functional>
#include <string>
#include <memory>
#include "IStoreObject.h"

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

				class CObjectInfo : public gintel::storage::IStoreObject
				{
					public:
						CObjectInfo() = default;
						CObjectInfo(
							const std::string& projectName,
							const std::string& name,
							CClangParser::ObjectType type,
							const std::filesystem::path filePath) :
							m_project(projectName),
							m_name{name},
							m_type{type},
							m_location{filePath}
						{
						}

						bool operator ==(const CObjectInfo& right) const
						{
							return (m_project == right.m_project &&
									m_name == right.m_name &&
									m_type == right.m_type &&
									m_location.file == right.m_location.file);
						}

						virtual ~CObjectInfo() = default;

						virtual std::shared_ptr<gintel::storage::IStoreObject> clone() override
						{
							auto obCopy {std::make_shared<CObjectInfo>()};
							obCopy->m_project = this->m_project;
							obCopy->m_name = this->m_name;
							obCopy->m_type = this->m_type;
							obCopy->m_location = this->m_location;

							return obCopy;
						}

						virtual std::string name() override
						{
							return m_name;
						}

					public:
						std::string m_project;
						std::string m_name;
						ObjectType m_type;
						ObjectLocationInfo m_location;
				};

			public:
				void parseSourceFile(
					const std::filesystem::path &filePath,
					std::function<bool(std::shared_ptr<CClangParser::CObjectInfo>, void *)> callback,
					void *context);
		};
	}
}

#endif	//	_CCLANGPARSER_H_
