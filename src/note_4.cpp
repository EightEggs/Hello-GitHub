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
		if (vec[ix] == value) return const_cast<int*>(&vec[ix]);	// Error C2440: "return": 无法从"const _Ty *"转换为"int *"
	return nullptr;
}
// 这里_Ty是什么，也查不到相关文档，我推测应该是IDE自己定义的中间类型。
// 理论上_Ty可以顺利转换为int，const _Ty*可以顺利转换为const int*，但是const _Ty*不能去掉const修饰进行转化。
// 但是为什么&vec[ix]是const _Ty*类型？是因为函数的const vector<int>& vec参数，我们用传引用，并且用const修饰，是因为
// find函数的功能决定了不需要进行一次多余的传值复制，并且find函数只负责查找，不会修改vec里的任何值。这样一来，
// 在find函数内部，&vec[ix]的类型自然就是const _Ty*了。但是我们要把得到的结果&vec[ix] return出去，一种修改方法是
// 在find函数前加const，但是这样一个find函数究竟有什么用呢？用户在vec中找到了希望找的值，得到了指向该const值的指针，但是因为
// 这个const，用户对这个值什么都不能做，这可不是我们设计find函数的初衷。
// 于是另一种修改方法，在&vec[ix]前面加上用来移除变量的const或volatile限定符的const_cast转换符,
// 写成这种样子： return const_cast<int*>(&vec[ix]); 就完美解决了这个问题。

int main()
{
	// 下面是测试代码
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