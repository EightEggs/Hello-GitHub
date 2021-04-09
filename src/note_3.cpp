/*
*<Created by Eight_Eggs. 9,April,2021>
* Generic Programming beginning.
* Standard Template Library(STL): containers + generic algorithm.
*/

#include <iostream>
#include <vector>
using namespace std;

// Now there is a task:
// ���һ������find()������һ��vector<int>��һ������ֵ�������ֵ������vector�ڣ��򷵻�һ��ָ���ֵ��ָ�룬���򷵻�nullptr.
// We can easily make it like this:
int* find_1(const vector<int>& vec, const int& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		// ��������ΪʲôҪ����д��������һ���µ����ۣ�������һ��(note_4)����.
		if (vec[ix] == value) return const_cast<int*>(&vec[ix]);
	return nullptr;
}

// OK, it works well. However, here comes a new task:
// ʹ����������Դ����κζ�����"=="�����ͣ���������������.
// ����ֻ�轫����д��function template���ɣ�
template <typename T>
T* find_2(const vector<T>& vec, const T& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		if (vec[ix] == value) return const_cast<T*>(&vec[ix]);
	return nullptr;
}

// Again, it works well. And again, a new task:
// ʹ��������ܹ�ͬʱ����vector��array�����Ҳ���overload.
// ����Ĺؼ����������vector��array�Ӳ�������ʧ��������֪�����Ǵ���ķ�ʽ����ָ�����ʽ֮���ƺ�������һ��ͷ��.
// �������鲻��ͨ��size()������ȡ��Ԫ�ظ��������ǿ�������һ������������array��Ԫ�ظ��������ܾ��ò�̫���ţ�
// ��һ�ֽ������������һ��ָ������������ж�vector��array���յ㣬��Ȥ���ǣ����ָ��Ӧ��ָ�����һ��Ԫ�ص���һ����ַ��
// ���ǽ����ָ���Ϊ"���"������ΪʲôҪָ�����һ��Ԫ�ص���һ�����������ϸ����.
template <typename T>
T* find_3(const T* first, const T* last, const T& value)
{
	if (!first || !last) return nullptr;
	for (; first != last; ++first)
		if (*first == value) return const_cast<T*>(first);
	return nullptr;
}
// ���lastָ�����һ��Ԫ�أ���ô����ʱ�ͻ�©�����һ��Ԫ�أ�ָ����һ�������ÿ�����ɱ�����
// ��ָ��߽���ĵ�ַ�Ϸ��𣿴��ǺϷ�����������ж���д�����Ͳ��Ϸ��������ǽ��˵�ַ��������ַ�Ƚ���ȫû�����⡣


// �����ǲ���ÿ��find����
int main()
{
	vector<int> vec1{ 1,2,3,4,5,6,7 };
	vector<string> vec2{ "abc","def","ghi","jkl","mno" };
	int arr1[7]{ 11,12,13,14,15,16,17 };
	char arr2[6]{ 'a','b','c','d','e','\0' };

	cout << find_1(vec1, 1) << endl;
	cout << find_2(vec1, 2) << endl;
	cout << find_2(vec2, static_cast<string>("abc")) << endl;
	cout << find_3(&vec2[0], &vec2[4] + 1, static_cast<string>("def")) << endl;
	cout << find_3(arr1, arr1 + 7, 16) << endl;
	cout << find_3(arr2, arr2 + 6, 'a') << endl;

	return 0;
}