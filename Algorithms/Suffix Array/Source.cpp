#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string> string_list;


string_list createSuffixArrayNaive(string & str)
{
	string_list strList;
	auto len = str.size();
	strList.reserve(len);

	for(decltype(len) i = 0; i < len; ++i)
	{
		strList.push_back(str.substr(i));
	}
	sort(strList.begin(), strList.end());

	return strList;
}
int main()
{
	string str;
	cout << "Enter String: ";
	std::getline(cin, str);
	cout << "Input String is: " << str << endl;
	auto strList = createSuffixArrayNaive(str);
	copy(strList.begin(), strList.end(), ostream_iterator<string>(cout, "\n"));
}