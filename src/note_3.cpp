/*
*<Created by Eight_Eggs. 9,April,2021>
* Generic Programming beginning.
* Standard Template Library(STL): containers + generic algorithm.
*/

#include <iostream>
#include <vector>
using namespace std;

// Now there is a task:
// 设计一个函数find()，给定一个vector<int>和一个整数值，如果此值存在于vector内，则返回一个指向该值的指针，否则返回nullptr.
// We can easily make it like this:
int* find_1(const vector<int>& vec, const int& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		// 至于这里为什么要这样写，引出了一个新的讨论，将在下一节(note_4)讲解.
		if (vec[ix] == value) return const_cast<int*>(&vec[ix]);
	return nullptr;
}

// OK, it works well. However, here comes a new task:
// 使这个函数可以处理任何定义有"=="的类型，而不仅仅是整数.
// 我们只需将它改写成function template即可：
template <typename T>
T* find_2(const vector<T>& vec, const T& value)
{
	for (auto ix = 0; ix < vec.size(); ++ix)
		if (vec[ix] == value) return const_cast<T*>(&vec[ix]);
	return nullptr;
}

// Again, it works well. And again, a new task:
// 使这个函数能够同时处理vector和array，并且不用overload.
// 问题的关键在于如何让vector和array从参数中消失，当我们知道它们传入的方式是以指针的形式之后，似乎就有了一点头绪.
// 但是数组不能通过size()方法获取到元素个数，我们可以增加一个参数，传入array的元素个数，但总觉得不太优雅；
// 另一种解决方法是增加一个指针参数，用于判断vector或array的终点，有趣的是，这个指针应该指向最后一个元素的下一个地址，
// 我们将这个指针称为"标兵"，至于为什么要指向最后一个元素的下一个，后面会详细解释.
template <typename T>
T* find_3(const T* first, const T* last, const T& value)
{
	if (!first || !last) return nullptr;
	for (; first != last; ++first)
		if (*first == value) return const_cast<T*>(first);
	return nullptr;
}
// 如果last指向最后一个元素，那么遍历时就会漏掉最后一个元素，指向下一个就正好可以完成遍历。
// 但指向边界外的地址合法吗？答案是合法，但如果进行读或写操作就不合法。仅仅是将此地址与其他地址比较完全没有问题。


// 下面是测试每个find函数
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