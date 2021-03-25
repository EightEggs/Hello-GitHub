/*
*<Created by Eight_Eggs. 25,March,2021>
*This file is ONLY used for test,
*not related to the project.
*/

#include <iostream>
using namespace std;

// 定义抽象基类LibMat
class LibMat {
public:
	LibMat() { cout << "LibMat default constructor!\n\n"; }
	virtual ~LibMat() { cout << "LibMat destructor!\n\n"; }

	virtual void print() const
	{
		cout << "LibMat::print(): I am a LibMat object!\n\n";
	}
};

// 在全局定义一个 non-member function print()
void print(const LibMat& mat)
{
	cout << "in global print(): about to call virtual member function print() ...\n\n";
	mat.print();
}

// 定义派生类Book
class Book :public LibMat {
public:
	Book() {};
	Book(const string& title, const string& author) :_title(title), _author(author)
	{
		cout << "Book(" << _title << "," << _author << ") constructor!\n\n";
	}
	virtual ~Book() { cout << "Book destructor!\n\n"; }
	// 'virtual' here is not necessary. It will be added by compiler automaticaly. But always indicating it is a good habit.
	virtual void print() const
	{
		cout << "Book::print(): I am a Book object!\n\n"
			<< "My title is: " << _title
			<< ", My author is: " << _author << endl <<endl;
	}

protected:
	string _title = "Unkonwn";
	string _author = "Unknown";
};

// 接下来看看会发生什么有趣的事情吧:)
int main()
{
	cout << "Starting...\n" << endl;

	Book a;
	Book b("Hello World", "Eight_Eggs");
	print(a);
	print(b);
	
	return 0;
}