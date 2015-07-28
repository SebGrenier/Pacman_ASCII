#include "StringUtils.h"

using namespace std;

namespace StringUtils
{
	vector<string> Tokenize(const string &str, const string &delimiters)
	{
		const string::size_type length = str.length();
		string currentChar = " ";
		vector<string> tokens;

		string::size_type pos_first = str.find_first_not_of(delimiters);
		string::size_type pos_last = pos_first;
		string::size_type count = 0;

		while (pos_first != string::npos && pos_first < length)
		{
			pos_last = str.find_first_of(delimiters, pos_first);
			count = pos_last - pos_first + 1;
			string token = str.substr(pos_first, count);

			tokens.push_back(token);

			pos_first = str.find_first_not_of(delimiters, pos_last);
		}

		return tokens;
	}
}
