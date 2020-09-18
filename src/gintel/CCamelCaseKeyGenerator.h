
#ifndef _CCamelCaseKeyGenerator_H_
#define _CCamelCaseKeyGenerator_H_

#include <string>
#include <vector>

namespace gintel
{
    namespace modules
    {
        //  This is a simple key generator class that extracts camel case
        //  substrings from a word.
        //  For instance,
        //      If the word is "CCamelCaseTestString", then the keys extracted are:
        //      1. CCamel
        //      2. Case
        //      3. Test
        //      4. String
        //  If there are no uppercase characters in the string or if the string
        //  only begins with a lowercase character, then the algorithm extracts all
        //  characters until an uppercase char is found or the end of string is reached,
        //  whichever comes first, and treats it as one key.
        //  For instance,
        //      For the word "alllowecasechars", only one key will be returned which is
        //      the full word as it is.
        //      For the word "functionName", two keys will be returned: "function", and "Name".
        class CCamelCaseKeyGenerator
        {
            public:
                static std::vector<std::string> createKeys(const std::string& input);
        };
    }
}

#endif  //  _CCamelCaseKeyGenerator_H_
