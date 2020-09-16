
#include <iostream>
#include <regex>
#include "CCamelCaseKeyGenerator.h"

using gintel::modules::CCamelCaseKeyGenerator;

std::vector<std::string> CCamelCaseKeyGenerator::createKeys(
    const std::string& input
    )
{
    if (input.empty())
        return {};

    std::regex rexpr ("([^a-zA-Z]*)((^[a-z]|[A-Z]*)[a-z]*)");
    std::smatch matches;

    std::vector<std::string> result;
    auto inputStr {input};

    while (std::regex_search(inputStr, matches, rexpr))
    {
        if (matches.size() < 3)
            break;

        std::string ignoredChars {matches[1].str()};
        std::string partialMatch {matches[2].str()};

        if (partialMatch.empty())
            break;

        result.push_back(partialMatch);

        inputStr = inputStr.substr(partialMatch.length() + ignoredChars.length());
        if (inputStr.empty())
            break;
    }

    return std::move(result);
}
