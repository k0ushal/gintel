#ifndef _UTIL_H_
#define _UTIL_H_


namespace gintel
{
    namespace util
    {
        namespace string
        {
            std::string lowercase(const std::string& input)
            {
                std::string result;
                std::transform(
                        input.begin(),
                        input.end(),
                        std::back_inserter(result),
                        [](const char c) {
                            return std::tolower(c);
                        });
                return result;
            }
        }
    }
}

#endif  //  _UTIL_H_
