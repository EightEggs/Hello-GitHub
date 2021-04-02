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
	Book() { cout << "Book default constructor!\n\n"; }
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
			<< ", My author is: " << _author << endl << endl;
	}

protected:
	string _title = "Unkonwn";
	string _author = "Unknown";
};

// 再定义一个派生类AudiBook
class AudiBook :public Book {
public:
	AudiBook() { cout << "AudiBook default constructor!\n\n"; }
	AudiBook(const string& title, const string& author, const string& reader) :
		Book(title, author), _reader(reader) // Why use Book(title,author) to initalize member data?
	{
		cout << "AudiBook(title,author,reader) constructer!\n\n";
	}
	/*See...If coding like this:
	* AudiBook(const string& title, const string& author, const string& reader) : _title(title), _author(author), _reader(reader) {//...}
	* It will cause an error: _title and _author are not the member data of AudiBook.
	* But why? They should have been inherited from Book, right?
	* Yes, they do have, but initializing like this is invalid.
	* Detailed information can be found here:
	* https://blog.csdn.net/L_Andy/article/details/80191619
	*/

	virtual ~AudiBook() { cout << "AudiBook desrtuctor!\n\n"; }
	virtual void print() const
	{
		cout << "AudiBook::print(): I am a AudiBook object!\n\n"
			<< "My title is: " << _title
			<< ", My author is: " << _author   // _title和_author可以直接访问
			<< ", My reader is:  " << _reader << endl << endl;
	}

protected:
	string _reader = "Unknown";
};

// 接下来看看会发生什么有趣的事情吧:)
int main()
{
	cout << "Starting...\n" << endl;

	Book a;
	Book b("Hello World", "Eight_Eggs");
	AudiBook c("Hello World 2","Eight_Eggs","Asaka");
	print(a);
	print(b);
	print(c);

	return 0;
}