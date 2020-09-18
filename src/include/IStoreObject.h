
#ifndef _ISTORE_OBJECT_H_
#define _ISTORE_OBJECT_H_

#include <memory>
#include <string>

namespace gintel
{
	namespace storage
	{
		class IStoreObject
		{
			public:
				virtual ~IStoreObject() = default;
				virtual std::string name() = 0;
				virtual std::shared_ptr<IStoreObject> clone() = 0;
		};
	}
}


#endif	//	_ISTORE_OBJECT_H_

