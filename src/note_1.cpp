/*
*<Created by Eight_Eggs. 2,April,2021>
*Something about type conversion.
*/
#include <iostream>
using namespace std;

class CDummy
{
public:
	float i, j;
	CDummy() :i(100), j(10)
	{
		;//do nothing. 
	}
};

class CAddition : public CDummy
{
	int* x;
	int y;
public:
	CAddition(int a, int b)
	{
		x = &a; y = b;
	}
	int result()
	{
		return *x + y;
	}
};

int main()
{
	// 隐式转换(implicit conversion)

	short a = 999;
	int b;
	b = a; // 宽化转换. It's OK.

	double c = 999.99;
	int d;
	d = c; // 窄化转换. Warning C4244:从“double”转换到“int”，可能丢失数据 


	// C风格显式转换(C-style explicit conversion)

	double e = 999.99;
	short f;
	f = (short)e;    // c-like cast notation
	f = short(e);    // functional notation
	// Till now, they are OK.
	// But... is C-style explicit conversion really safe? Let's see...
	CDummy dd;
	CAddition* padd;
	padd = (CAddition*)&dd; // Pay attention here!
	cout << padd->result();
	/*
	此时父类的指针&dd被C风格转换方式强制转成了子类的指针了，
	后面调用了子类的方法result，需要访问*x，
	但指针指向的对象本质还是父类的，所以x相当于父类中的i，y相当于父类中的j，*x相当于*i，
	但i是float型变量(初始化为100)，不是地址，所以出错，
	如果程序员正是鲁莽地对这个地址指向的内存进行写入操作，
	那将可能会破坏系统程序，导致操作系统崩溃！

	这里有一个重要概念，CAddition*是子类的指针，
	它的变量padd可以调用子类的方法，但是它指向的是父类的对象，
	也就是说padd指向的内存空间里存放的是父类的成员变量。
	深入地说，数据在内存中是没有“类型”一说的，
	比如0x3F可能是字符型，也可能是整型的一部分，
	还可能是地址的一部分。我们定义的变量类型，
	其实就是定义了数据应该“被看成什么”的方式。

	因此padd类指针实质是定义了取值的方式，
	如padd->x就是一并取出内存空间里的0号单元至3号单元的值(共4个字节)，
	将其拼成32位并当作指针; padd->y则取出内存空间里的4号单元至7号单元(共4个字节)，
	将其拼成32位并当作int型变量。
	但实际上padd指向的是父类的对象，
	也就是前4个字节是float型变量，后4个字节也是float型变量。

	从这里可以看出，程序员的这种转换使编译器“理解”出错，把牛当成马了。
	从上可见，用C风格的转换其实是不安全的，编译器无法看到转换的不安全。
	*/

	// 上行转换(up-casting)与下行转换(down-casting)
	/*
	看到这个，读者可能会问，哪些转换不安全？
	根据前面所举的例子，可以看到，不安全来源于两个方面：
	其一是类型的窄化转化，会导致数据位数的丢失；
	其二是在类继承链中，将父类对象的地址（指针）强制转化成子类的地址（指针），
	这就是所谓的下行转换。“下”表示沿着继承链向下走（向子类的方向走）。
	类似地，上行转换的“上”表示沿继承链向上走（向父类的方向走）。

	我们给出结论，上行转换一般是安全的，下行转换很可能是不安全的。

	为什么呢？因为子类中包含父类，所以上行转换（只能调用父类的方法，引用父类的成员变量）一般是安全的。
	但父类中却没有子类的任何信息，而下行转换会调用到子类的方法、引用子类的成员变量，
	这些父类都没有，所以很容易“指鹿为马”或者干脆指向不存在的内存空间。

	值得一说的是，不安全的转换不一定会导致程序出错，
	比如一些窄化转换在很多场合都会被频繁地使用，前提是程序员足够小心以防止数据溢出；
	下行转换关键看其“本质”是什么，比如一个父类指针指向子类，
	再将这个父类指针转成子类指针，这种下行转换就不会有问题。
	*/

	// 针对类指针的问题，C++特别设计了更加细致的转换方法，分别有：
	/*******************************************\
	 *  static_cast<new_type> (expression)
	 *  dynamic_cast<new_type> (expression)
	 *  reinterpret_cast<new_type> (expression)
	 *  const_cast<new_type> (expression)
	\*******************************************/

	// 1.static_cast
	double pi = 3.1415926;
	int i = static_cast<int>(pi); // OK.
	//静态转换是最接近于C风格转换，很多时候都需要程序员自身去判断转换是否安全.

	// 2.dynamic_cast
	padd = dynamic_cast<CAddition*>(&dd); // wrong: base-to-derived 
	//动态转换确保类指针的转换是合适完整的，它有两个重要的约束条件，
	//其一是要求new_type为指针或引用，其二是下行转换时要求基类是多态的(基类中包含至少一个虚函数).
	//dynamic_cast提升了安全性，dynamic_cast可以识别出不安全的下行转换，但并不抛出异常，而是将转换的结果设置成nullptr.

	// 3.reinterpret_cast
	//这个转换是最“不安全”的，两个没有任何关系的类指针之间转换都可以用这个转换实现，举个例子：
	/*
	class A {};
	class B {};
	A* a = new A;
	B* b = reinterpret_cast<B*>(a); // succesful!
	*/
	//更厉害的是，reinterpret_cast可以把整型数转换成地址(指针)，
	//这种转换在系统底层的操作，有极强的平台依赖性，移植性不好，而且搞不好会吧内存搞坏。
	//它同样要求new_type是指针或引用.

	// 4.const_cast
	//这个转换将常量转成非常量。例如：
	const char* cc = "sample text";
	char* ccc = const_cast<char*> (cc);
	print(ccc); // OK.
	//但切记，这个转换并不转换原常量本身，即cc还是常量，只是它返回的结果ccc是非常量了.

	return 0;
}

void print(char* str) // 注意这里的形参并不是const
{
	cout << str << endl;
}

/*Conclusion:
 C风格转换是“万能的转换”，但需要程序员把握转换的安全性，编译器无能为力；
 static_cast最接近于C风格转换，但在无关类指针转换时，编译器会报错，提升了安全性；
 dynamic_cast要求转换类型必须是指针或引用，且在下行转换时要求基类是多态的，
 如果发现下行转换不安全，dynamic_cast返回一个null指针，dynamic_cast总是认为void*之间的转换是安全的；
 reinterpret_cast可以对无关类指针进行转换，甚至可以直接将整型值转成指针，这种转换是底层的，有较强的平台依赖性；
 const_cast可以将常量转成非常量，但不会破坏原常量的const属性，只是返回一个去掉const的变量。
*/