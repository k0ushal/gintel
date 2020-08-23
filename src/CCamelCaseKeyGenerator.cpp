
#include <regex>
#include "CCamelCaseKeyGenerator.h"

using gintel::modules::CCamelCaseKeyGenerator;

std::vector<std::string> CCamelCaseKeyGenerator::createKeys(const std::string& input)
{
    std::regex rexpr {"((^[a-z]|[A-Z]*)[a-z]*)"};
    std::smatch matches;

    std::vector<std::string> result;
    auto inputStr {input};

    while (std::regex_search(inputStr, matches, rexpr))
    {
        if (!matches.size())
            break;

        std::string partialMatch {matches[0].str()};
        result.push_back(partialMatch);

        inputStr = inputStr.substr(partialMatch.length());
        if (inputStr.empty())
            break;
    }

    return std::move(result);
}
