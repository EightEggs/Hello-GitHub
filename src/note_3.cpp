/*
*<Created by Eight_Eggs. 8,April,2021>
* Generic Programming beginning.
* Standard Template Library(STL): containers + generic algorithm.
*/

#include <iostream>
#include <vector>
using namespace std;

// Now there is a job:
// ���һ������find()������һ��vector<int>��һ������ֵ�������ֵ������vector�ڣ��򷵻�һ��ָ���ֵ��ָ�룬���򷵻�nullptr.
// We can easily make it like this:
int* find(const vector<int>& vec, const int& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		// ��������ΪʲôҪ����д��������һ���µ����ۣ�������һ��(note_4)����.
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