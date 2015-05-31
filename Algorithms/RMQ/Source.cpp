#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <assert.h>
#include <iterator>

using namespace std;

struct CInterval
{
	int low;
	int hi;
	CInterval(int l, int h): low(l), hi(h){}
};

struct CNode
{
	int m_Min;
	CInterval m_Interval;

	shared_ptr<CNode> m_Left;
	shared_ptr<CNode> m_Right;

	CNode(int l, int h, int m, shared_ptr<CNode> leftPtr, shared_ptr<CNode> rightPtr):m_Interval(l,h), m_Min(m), m_Left(leftPtr), m_Right(rightPtr){}
};

shared_ptr<CNode> constructSegmentTree(vector<int>& v, int start, int end)
{
	assert(start <= end);
	if(end == start)
		return make_shared<CNode>(start, end, v[start], nullptr, nullptr);

	auto rLeftEnd = start + ((end - start) /2);
	auto rLeft = constructSegmentTree(v, start, rLeftEnd);
	auto rRight = constructSegmentTree(v, rLeftEnd + 1, end);

	auto rRoot = make_shared<CNode>(rLeft->m_Interval.low, rRight->m_Interval.hi, std::min(rLeft->m_Min,rRight->m_Min),rLeft, rRight);

	return rRoot;
}
int RMQ(shared_ptr<CNode> rRoot, int qs, int qe)
{
	if(nullptr == rRoot)
		return numeric_limits<int>::max();

	assert(qs <= qe);
	if((qs <= rRoot->m_Interval.low) &&(qe >= rRoot->m_Interval.hi))
		return rRoot->m_Min;
	if((qe<= rRoot->m_Interval.low) && (qs >= rRoot->m_Interval.hi))
		return numeric_limits<int>::max();
	return (std::min(RMQ(rRoot->m_Left, qs, qe), RMQ(rRoot->m_Right, qs, qe)));
}

void printBT(shared_ptr<CNode> rHead, int indent = 0)
{
	if(nullptr == rHead)
		return;
	
	if(rHead->m_Right) 
	{
		printBT(rHead->m_Right, indent+4);
	}
	if (indent) 
	{
		std::cout << std::setw(indent) << ' ';
	}
	if (rHead->m_Right)
		std::cout<<" /\n" << std::setw(indent) << ' ';

	std::cout<< rHead->m_Min << "\n ";
	if(rHead->m_Left) 
	{
		std::cout << std::setw(indent) << ' ' <<" \\\n";
		printBT(rHead->m_Left, indent+4);
	}
}
int main()
{
	int arr[] = {10, 5, 8, 20, 28, 2, 30, 32, 35, 4};
	int num = sizeof(arr)/ sizeof(int);
	vector<int> v(arr,arr + num);
	
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	auto rRoot = constructSegmentTree(v, 0, num-1);
	//printBT(rRoot);
	auto qs = 3; auto qe = 8;
	cout << "RMQ of range: "<< qs << ":" << qe << "is "<<RMQ(rRoot,qs, qe) << endl;
}


