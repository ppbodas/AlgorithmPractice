#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <deque>

using namespace std;

template<typename T>
class CNode
{
public:
	CNode(T data):mData(data), mLeft(nullptr), mRight(nullptr)
	{
	}
	shared_ptr<CNode<T>>& left(){return mLeft;}
	shared_ptr<CNode<T>>& right(){return mRight;}
	T data() {return mData;}
private:
	T				  mData;
	shared_ptr<CNode<T>> mLeft;
	shared_ptr<CNode<T>> mRight;
};

template <typename T>
shared_ptr<CNode<T>> parseCompleteBT(vector<T> v)
{
	if (v.empty())
		return nullptr;

	auto rRoot = make_shared<CNode<T>>(v[0]);

	std::deque<shared_ptr<CNode<T>>> q;

	q.push_back(rRoot);
	
	auto iter = v.begin();
	++iter;
	while (iter != v.end())
	{
		auto rParent = q.front();
		rParent->left() = make_shared<CNode<T>>(*iter);
		q.push_back(rParent->left());
		++iter;
		if (iter != v.end())
		{
			rParent->right() = make_shared<CNode<T>>(*iter);
			q.push_back(rParent->right());
			++iter;
		}
		q.pop_front();
	}
	return rRoot;
}
template <typename T>
void printBT(shared_ptr<CNode<T>> rHead, int indent = 0)
{
    if(rHead)
	{
		if(rHead->right()) 
		{
            printBT(rHead->right(), indent+4);
        }
        if (indent) 
		{
            std::cout << std::setw(indent) << ' ';
        }
        if (rHead->right())
			std::cout<<" /\n" << std::setw(indent) << ' ';

        std::cout<< rHead->data() << "\n ";
		if(rHead->left()) 
		{
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            printBT(rHead->left(), indent+4);
        }
    }
}
template <typename T>
void printDLL(shared_ptr<CNode<T>> rHead)
{
	while(rHead)
	{
		cout << rHead->data() << " ";
		rHead = rHead->right();
	}
	cout << endl;
}
template <typename T>
void inorderTraversal(shared_ptr<CNode<T>>rRoot, shared_ptr<CNode<T>>& rHead)
{
	if (!rRoot)
		return;

	static shared_ptr<CNode<T>> rLast = nullptr;
	
	inorderTraversal(rRoot->left(),rHead);

	if (nullptr ==rLast)
	{
		rHead = rRoot;
	}
	else
	{
		rLast->right() = rRoot;
		rRoot->left() = rLast;
	}
	rLast = rRoot;

	inorderTraversal(rRoot->right(),rHead);
}
int main()
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70,80, 90, 100, 110};
	auto num  = sizeof(arr)/ sizeof(int);
	vector<int> v(arr, arr+num);

	auto rRoot = parseCompleteBT(v);
	printBT(rRoot);

	shared_ptr<CNode<int>> rHead = nullptr;

	inorderTraversal(rRoot, rHead);

	printDLL(rHead);
}
