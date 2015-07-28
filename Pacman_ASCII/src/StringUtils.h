#pragma once
#include <vector>
#include <string>

namespace StringUtils
{
	std::vector<std::string> Tokenize(const std::string &str, const std::string &delimiters);
}