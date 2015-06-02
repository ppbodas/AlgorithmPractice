#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> string_list;

namespace SuffixArray
{
	int gap = 1;
	vector<int> sa;
	vector<int> pos;		//rank array
	vector<int> tmp;		//rank array
	
	int len = 0;

	bool suffixCmp(int i , int j)
	{
		if(pos[i] != pos[j])
			return pos[i] < pos[j];

		i += gap;
		j += gap;

		if(i < len && j < len)
		{
			return pos[i] < pos[j];
		}
		else
			return i > j;
	}

	string_list createSuffixArray(string & str)
	{
		len = str.size();
		sa.reserve(len);
		pos.reserve(len);
		tmp.reserve(len);

		for(decltype(len) i = 0; i < len; ++i)
		{
			sa.push_back(i);
			pos.push_back(str[i]);
			tmp.push_back(0);
		}


		for(gap = 1;; gap = gap*2)
		{
			sort(sa.begin(), sa.end(), suffixCmp);
			tmp[0] = 0;
			for(decltype(len) i = 0; i < len-1; ++i)
			{
				tmp[i + 1] = tmp[i] + suffixCmp(sa[i], sa[i + 1]);
			}

			for(decltype(len) i = 0; i < len; ++i)
			{
				pos[sa[i]] = tmp[i]; 
			}
			if(tmp[len-1] == (len-1))
				break;
		}

		/*string_list strList;
		strList.reserve(len);
		for(int i = 0;i < len; ++i)
		{
			strList.push_back(str.substr(sa[i]));
		}*/
		return sa;
	}
}
string_list createSuffixArrayNaive(string & str)
{
	string_list strList;
	auto len = str.size();
	strList.reserve(len);

	for(decltype(len) i = 0; i < len; ++i)
	{
		strList.push_back(i);
	}
	sort(strList.begin(), strList.end(), [str](int i, int j){return str.substr(i) < str.substr(j);});

	return strList;
}
int main()
{
	string str;
	cout << "Enter String: ";
	std::getline(cin, str);
	cout << "Input String is: " << str << endl;
	//auto strList = createSuffixArrayNaive(str);

	auto strList = SuffixArray::createSuffixArray(str);
	copy(strList.begin(), strList.end(), ostream_iterator<int>(cout, "\n"));

	cout << strList.size() <<endl;
}