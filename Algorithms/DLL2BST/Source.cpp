#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

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
shared_ptr<CNode<T>> arrToDLL(vector<T> v)
{
	shared_ptr<CNode<T>> rHead = nullptr;
	shared_ptr<CNode<T>> rLast = nullptr;
	for(auto elem : v)
	{
		if(nullptr == rHead)
		{
			rHead = make_shared<CNode<T>>(elem);
			rLast = rHead;
		}
		else
		{
			rLast->right() = make_shared<CNode<T>>(elem);
			rLast->right()->left() = rLast;
			rLast = rLast->right();
		}
	}

	return rHead;
}
template <typename T>
void printDLL(shared_ptr<CNode<T>> rHead)
{
	while(rHead)
	{
		cout << rHead->data() << " ";
		rHead = rHead->right();
	}
	cout <<endl;
}
template <typename T>
shared_ptr<CNode<T>> getMid(shared_ptr<CNode<T>> rHead, int num)
{
	if (num <= 2)
		return nullptr;

	auto mid = num/2;	//if num is 4 then mid = 2 so increment twice. if num is 3 mid = 1 so increment once.
	for(auto i = 0; i < mid; ++i)
		rHead = rHead->right();

	return rHead;
}


template <typename T>
shared_ptr<CNode<T>> dll2BST(shared_ptr<CNode<T>> rHead, int num)
{
	{
		//Only useful for linklist of size 2 or less ohterwise skipped
		if (num == 2)
		{
			rHead->right()->left() = nullptr;
			return rHead;
		}
		if (num < 2)
			return rHead;
	}

	auto rMid = getMid(rHead,num);

	if(auto rLeft = rMid->left())
	{
		rLeft->right() = nullptr;
		auto lSize = num/2;
		//if(lSize <= 2)
		//{
		//	rMid->left() = rHead;
		//	if(lSize == 2)
		//	{
		//		rHead->right()->left() = nullptr;
		//	}
		//}
		//else               //Main Recursion
			rMid->left() = dll2BST(rHead, lSize); 
	}
	if (auto rRight = rMid->right())
	{
		rRight->left() = nullptr;
		auto rSize = (num+1)/2 - 1;
		/*if(rSize <= 2)
		{
			if(rSize == 2)
			{
				rMid->right()->right()->left() = nullptr;
			}
		}
		else*/
			rMid->right() = dll2BST(rMid->right(), rSize);
	}

	return rMid;
}
template <typename T>
shared_ptr<CNode<T>> dll2BSTFast(shared_ptr<CNode<T>>& rHead,/*# of nodes*/ int n)
{
	/* Base Case */
    if (n <= 0)
        return nullptr;
 
    /* Recursively construct the left subtree */
    shared_ptr<CNode<T>> rLeft = dll2BSTFast(rHead, n/2);
 
    /* head_ref now refers to middle node, make middle node as root of BST*/
    shared_ptr<CNode<T>> rRoot = rHead;
 
    // Set pointer to left subtree
    rRoot->left() = rLeft;
 
    /* Change head pointer of Linked List for parent recursive calls */
    rHead = rHead->right();
 
    /* Recursively construct the right subtree and link it with root
      The number of nodes in right subtree  is total nodes - nodes in
      left subtree - 1 (for root) */
    rRoot->right() = dll2BSTFast(rHead, n-n/2-1);
 
    return rRoot;
}
template <typename T>
void postorder(shared_ptr<CNode<T>> rHead, int indent = 0)
{
    if(rHead)
	{
		if(rHead->right()) 
		{
            postorder(rHead->right(), indent+4);
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
            postorder(rHead->left(), indent+4);
        }
    }
}
int main()
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70,80, 90, 100, 110};
	auto num  = sizeof(arr)/ sizeof(int);
	vector<int> v(arr, arr+num);

	auto rHead = arrToDLL(v);
	printDLL(rHead);

	auto rTreeHead = dll2BST(rHead, num);

	postorder(rTreeHead);
}