/*
*<Created by Eight_Eggs. 22,May,2021>
* Generic Programming beginning.
* A discussion from note_3.
*/

#include "header.h"
using namespace std;

// We have constructed a function in note_3.cpp like this:
template <typename T>
T* find(const vector<T>& vec, const T& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		if (vec[ix] == value) return const_cast<T*>(&vec[ix]);
	return nullptr;
}

// If we rewrite it like this:
int* find_1(const vector<int>& vec, const int& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		if (vec[ix] == value) return const_cast<int*>(&vec[ix]);	// Error C2440: "return": �޷���"const _Ty *"ת��Ϊ"int *"
	return nullptr;
}
// ����_Ty��ʲô��Ҳ�鲻������ĵ������Ʋ�Ӧ����IDE�Լ�������м����͡�
// ������_Ty����˳��ת��Ϊint��const _Ty*����˳��ת��Ϊconst int*������const _Ty*����ȥ��const���ν���ת����
// ����Ϊʲô&vec[ix]��const _Ty*���ͣ�����Ϊ������const vector<int>& vec�����������ô����ã�������const���Σ�����Ϊ
// find�����Ĺ��ܾ����˲���Ҫ����һ�ζ���Ĵ�ֵ���ƣ�����find����ֻ������ң������޸�vec����κ�ֵ������һ����
// ��find�����ڲ���&vec[ix]��������Ȼ����const _Ty*�ˡ���������Ҫ�ѵõ��Ľ��&vec[ix] return��ȥ��һ���޸ķ�����
// ��find����ǰ��const����������һ��find����������ʲô���أ��û���vec���ҵ���ϣ���ҵ�ֵ���õ���ָ���constֵ��ָ�룬������Ϊ
// ���const���û������ֵʲô������������ɲ����������find�����ĳ��ԡ�
// ������һ���޸ķ�������&vec[ix]ǰ����������Ƴ�������const��volatile�޶�����const_castת����,
// д���������ӣ� return const_cast<int*>(&vec[ix]); �����������������⡣

int main()
{
	// �����ǲ��Դ���
	vector<int> vec{ 0,1,2,3,4,5 };
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		cout << *it << endl;
	cout << endl;
	int* a = find_1(vec, 2);
	*a = 200;
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		cout << *it << endl;
	cout << endl;
	cout << "Done.";
}