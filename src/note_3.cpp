/*
*<Created by Eight_Eggs. 8,April,2021>
* Generic Programming beginning.
* Standard Template Library(STL): containers + generic algorithm.
*/

#include <iostream>
#include <vector>
using namespace std;

// Now there is a job:
// 设计一个函数find()，给定一个vector<int>和一个整数值，如果此值存在于vector内，则返回一个指向该值的指针，否则返回nullptr.
// We can easily make it like this:
int* find(const vector<int>& vec, const int& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		// 至于这里为什么要这样写，引出了一个新的讨论，将在下一节(note_4)讲解.
		if (vec[ix] == value) return const_cast<int*>(&vec[ix]);
	return nullptr;
}

int main()
{
	vector<int> a{ 1,2,3,4,5,6,7 };
	int* pa = find(a, 3);
	*pa = 33;
	cout << a[2];
	return 0;
}