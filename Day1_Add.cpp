// Day1_Add.cpp: 主项目文件。

#include "stdafx.h"
#include <iostream>
#include<sys/types.h>
#include <stack>

using namespace System;
using namespace std;

int add(int a, int b) 
{
	int c = a ^b; 
	int d = a&b;
	cout << "a is: " << a << "  b is: " << b << " c is: "<< c << " d is: " << d <<endl;
	return  (d == 0) ? c:add(c, d<<1);
}

#define	  CHECK_LEN(len) if(len > 1000) \
{ \
	cerr << "Len is lager than 1000" <<endl; \
	return;\
}\

class ArrayOpr {

private:
	int* oriArray;
	int length;
	static const unsigned int BUF_SIZE = 1000;
public:
	ArrayOpr() {
		oriArray = new int[BUF_SIZE];
	}
	void SetArray(int* data, int len) {
		CHECK_LEN(len)
		for(int i = 0; i < len; i++){
			oriArray[i] = data[i];
		}
		length = len;
	}

	//oriArray 和 mergeArray都是（从小到大）排序之后的数组， 将mergeArray按顺序插入oriArray
	int MergeSortedArray( int* mergeArray, int len2 ){
		
		int* pOri = oriArray + length - 1;
		int* pMerge = mergeArray + len2 -1;
		int index = length + len2  -1;
		while(pOri >= oriArray && pMerge >= mergeArray)	{
			if(*pOri  < *pMerge) {
				oriArray[index--]  = *pMerge;
				pMerge --;
			}else {
				oriArray[index--]  = *pOri;
				pOri --;
			}
		}
		
		while(index >= 0 && pMerge >= mergeArray) {
			oriArray[index --]   = *pMerge--;
		} 
		length = length+len2;
		return 0;
	}

	void PrintArray() {
		for(int i = 0; i < length; i++) {
			cout << oriArray[i] <<'\t';
		}
		cout << endl;
	}

	~ArrayOpr() {
		if(oriArray != NULL) {
			delete [] oriArray;
		}
	}
	
};

/************************************************************************/
/* 链表                                                                     */
/************************************************************************/
struct ListNode {
	int value;
	ListNode* next;
	ListNode() {
		next = NULL;
		value = 0;
	}
};

class ListOpr {
private:
	ListNode* pHead;
public:
	void CreateList(int* srcData, int len) {
		pHead = new ListNode();
		pHead->value = srcData[0];

		ListNode* pCur = pHead;
		for(int i = 1; i < len; i++) {
			ListNode* pNode = new ListNode();
			pNode->value = srcData[i];
			pCur->next = pNode;
			pCur = pNode;
		}		
	}

	void PrintList() {
		if(pHead == NULL) {
			cout << "List is null" << endl;
			return;
		}
		if(pHead->next == NULL) {
			cout << pHead->value<<endl;
			return;
		}
		ListNode* pNode = pHead;
		while(pNode != NULL) {
			cout << pNode->value<<'\t';
			pNode = pNode->next;
		}
		cout << endl;
	}

	void ReversePrint() {
		if(pHead == NULL) {
			cout << "List is null" << endl;
			return;
		}
		if(pHead->next == NULL) {
			cout <<pHead->value<<endl;
			return;
		}

		stack<int>  listStack;
		ListNode* ptr = pHead;
		while(ptr != NULL) {
			listStack.push(ptr->value);
			ptr = ptr->next;
		}
		
		while(!listStack.empty())  {
			cout << listStack.top() << '\t';
			listStack.pop();
		}

	}
/*	
	void ReverseRecursive(){
		if(pHead != NULL) {
			if(pHead->)

		}
	}
*/
	~ListOpr(){
		cout <<"Begin to call deconsutruct"<<endl;
		if(pHead == NULL) {
			return;
		}
		ListNode* pNode = pHead;
		while(pNode) {
			delete pNode;
			pNode = pNode->next;
		}
	}

};

/************************************************************************/
/* 二叉树                                                                     */
/************************************************************************/

//TODO

/************************************************************************/
/* 两个栈实现队列                                                                     */
/************************************************************************/
template <typename T>
class CQueue{
private:
	stack<T>  pushStack;
	stack<T> popStack;
public:
	int SizeQueue() {
		return pushStack.size() + popStack.size();
	}
	bool EmptyQueue() {
		return pushStack.empty() && popStack.empty();
	}
	void PushQueue(T inItem){
		pushStack.push(inItem);
	}
	void PopQueue() {
		if(popStack.empty() && pushStack.empty()) {
			cerr<<"There is no item in queue, exit" << endl;
			return;
		}
		if(popStack.empty()) {
			while(!pushStack.empty()) {
				popStack.push(pushStack.top());
				pushStack.pop();
			}
		}
		popStack.pop();
	}
	
       T TopQueue() {
	       if(popStack.empty() && pushStack.empty()) {
		       cerr<<"There is no item in queue, exit" << endl;
		       return  T();
	       }
	       if(popStack.empty()) {
		       while(!pushStack.empty()) {
			       popStack.push(pushStack.top());
			       pushStack.pop();
		       }
	       }
	       return popStack.top();		
       }    
};

/************************************************************************/
/* 寻找第k大的数字                                                                     */
/************************************************************************/
//使用策略模式
class KvalueStrategy{
public:
	     virtual  int FindKMaxInterface(int* a, int start, int end, int k) = 0;
};

class PartionStratey : public KvalueStrategy {
public:	
	int FindKMaxInterface(int*a , int start, int end, int k) {
		cout << "Enter PartionStratey" << endl;
		  return PartionK(a, start, end, k);
	}
private:
	void Swap(int* from, int* to) {
		int tmp = *from;
		*from = *to;
		*to = tmp;
	}
	int Partion(int*a, int start, int end) {
		int head = start-1;
		int tail = end ;
		int endItem = a[end];
		while(1) {
			while(a[++head] > endItem && head < end);
			while(a[--tail] < endItem && tail >= start);
			if(head < tail) {
				Swap(&a[head], &a[tail]); 
			}else {
			       break;
			}

		}
		//cout <<"a head is: "<<a[head] << "   head is: "<< head<<endl;;
		//cout <<"a end is:" << a[end]<<endl;
		Swap(&a[head], &a[end]);
		
		for(int i = start; i <= end; i++) {
			cout << a[i] <<'\t';
		}
		cout << endl;

		return head;
	}

	int PartionK(int* a, int start, int end, int k) {

		int index = Partion(a, start, end);
		int findIndex = index - start +1;
		//return findIndex;
		
		if(findIndex == k) {
			return k;
		}
		if(findIndex < k) {
			return PartionK(a,  findIndex , end, k - findIndex);
		}else {
			return PartionK(a, start, findIndex , k);
		} 
	}


};

class CountStratey : public KvalueStrategy {
public:	
	//使用前提，数组全部是正整数
	int FindKMaxInterface(int*a , int start, int end, int k) {
		cout << "Enter CountStratey" << endl;
		 int Max = a[start];
		for(int i = start+1 ; i <= end; i++) {
			if(a[i] > Max) {
				Max = a[i];
			}
		}
		 cout << Max<<endl;
		int* count = new int[Max+1];
		memset(count, 0, sizeof(int)*(Max+1));

		for(int i = start; i <= end; i++) {
			count[a[i]]++;
		}
		for(int i = 0; i <= Max ; i++) {
			cout << count[i]<<endl;
		}
		int sum = 0;
		for(int i = Max; i >= 0; i-- )	{
			//cout << count[i] <<endl;
			sum += count[i];
			if(sum >= k) {
				return i;
			}
		}
	}
};

class Context {
private:
	KvalueStrategy*  strategy;

public:
	void SetMethod(KvalueStrategy* method) {
		strategy = method;
	}
	void DoAction(int*a , int start, int end, int k){
		int ret = this->strategy->FindKMaxInterface(a , start, end, k);
		cout << "The result is: "<< ret<<endl;
	}
};		


/************************************************************************/
/* 寻找旋转数组的最小值                                                                     */
/************************************************************************/
int FindMinValueInRotateArray(int* a, int n) {
	if(n == 1) {
		return a[0];
	}
	for(int i = 0; i < n-1; i++) {
		if(a[i] > a[i+1] ) {
			return a[i+1];
		}
	}
	return a[n - 1];
}

int FindMinValueUsingBinary(int* a, int n) {
	    if(n == 1) {
		    return a[0];
	    }
	    int* pBegin = a;
	    int* pEnd = a + n -1;


	    while((pEnd - pBegin) > 1)	{
		    int* pMiddle = pBegin + (pEnd - pBegin)/2;
		    if(*pMiddle  > *pBegin) {
			    pBegin =   pMiddle;
		    }else {
			    pEnd = pMiddle;
		    }			
	    }    
	    return *pEnd;
}

int main(array<System::String ^> ^args)	  {
       Console::WriteLine(L"Hello World");

	/************************************************************************/
	/* 测试加法原理                                                                     */
	/************************************************************************/

    
    //int sum = add(5, 6);
    //cout << sum << endl;
	
	/************************************************************************/
	/* 
	*Test array:以o(n)的复杂度将两个有序数组合并
	*/
	/************************************************************************/
	//int testArray[7] = {33, 46, 81, 92 , 100, 200, 332};
	//int mergeArray[9] = {1, 2, 3, 55, 99, 111, 439, 540, 869};
	//ArrayOpr test;
	//test.SetArray(testArray, 7);
	//test. PrintArray();
	//test.MergeSortedArray(mergeArray, 9);
	//test.PrintArray();

	/************************************************************************/
	/* TestList                                                                      */
	/************************************************************************/

	//int srcData[10] = {1, 4, 20, 30, 50, 60, 70, 80,100, 200};
 //	ListOpr testList;
	//testList.CreateList(srcData, 10);
	//testList.PrintList();
	//testList.ReversePrint();

    /************************************************************************/
    /* TestStack and queue                                                                     */
    /************************************************************************/
	//CQueue<int> testQueue;
	//testQueue.PushQueue(1);
	//testQueue.PushQueue(3);
	//testQueue.PushQueue(8);
	//testQueue.PushQueue(19);

	//while(!testQueue.EmptyQueue()) {
	//
	//	cout << testQueue.TopQueue() << '\t';
	//	testQueue.PopQueue();
	//}

       /************************************************************************/
       /* 测试查询第k个最大数                                                                     */
       /***********************************************************************/
       //int a[] = {0, 20,39,39, 1, 5, 39, 39, 39, 39, 39,10, 10};

       //Context testMethod;
       //KvalueStrategy* methodPartion = new PartionStratey();
       //testMethod.SetMethod(methodPartion);
       //testMethod.DoAction(a, 0, sizeof(a)/sizeof(int) -1,  3);
       //for(int i = 0; i <= sizeof(a)/sizeof(int) -1; i++) {
	      // cout << a[i] <<'\t';
       //}
       //cout << endl;
       //cout << a[(sizeof(a)/sizeof(int) -1)/2] <<endl;

  /*
       KvalueStrategy* methodCount = new CountStratey();
       testMethod.SetMethod(methodCount);
       testMethod.DoAction(a, 0, 9, 4);
     */
       //delete methodPartion;
      // delete methodCount;


       /************************************************************************/
       /* 测试旋转数组的最小值(考察的是二分查找法))                                                                     */
       /************************************************************************/
	int a[] = {1, 2, 3, 4, 9, 10, 10 };
	int value = FindMinValueInRotateArray(a, 7);
	cout << "The result is: "<< value<<endl;
	
	value = FindMinValueUsingBinary(a, 7);
	cout << "The result2 is: "<< value << endl;

	while(1);
	return 0;
}
