/*
*<Created by Eight_Eggs. 4,April,2021>
*Something about designing a class.
*Design a Person class by hand from zero.
*/
#include <iostream>
#include <random>
using namespace std;

class Person
{
public:
	// 默认构造函数
	Person() :_name("<Unknown>"), _age(0), _height(50.f), _weight(3.f)
	{
		cout << "A default person was born." << endl;
	}
	// 带参构造函数
	Person(const string name, const unsigned short age = 0, const float height = 50.f, const float weight = 3.f) :
		_name(name), _age(age), _height(height), _weight(weight)
	{
		cout << _name << " was born. Height is " << _height << ", weight is " << _weight << "." << endl;
	}
	//析构函数
	~Person()
	{
		cout << _name << " passed away." << endl;
	}
	// 更改名字
	void change_name(const string newName)
	{
		if (newName == _name) cout << "Are you kidding me?!" << endl;
		else {
			string oldName = _name;
			_name = newName;
			cout << oldName << " now is called " << _name << endl;
		}
	}
	// 吃
	void eat(const string food, const unsigned num = 1)
	{
		srand(static_cast<unsigned>(time(NULL)));
		float addition = (rand() % 10 + 1) / 10.f;
		_height += addition * (1.05 + num / 10.f);
		_weight += addition * (1.0 + num / 10.f);
		cout << _name << " ate " << food << "*" << num << ".\n"
			<< "Now, height is " << _height << ", weight is " << _weight << "." << endl;
	}
	// 睡
	void sleep()
	{
		srand(static_cast<unsigned>(time(NULL)) + 1);
		float addition = (rand() % 15 + 1) / 10.f;
		if (rand() % 2)
		{
			_height += addition * 1.05;
			cout << _name << " had a good sleep.\nNow, height is " << _height << endl;
		}
		else
		{
			_height += addition * 0.55;
			cout << _name << " had a bad sleep.\nNow, height is " << _height << endl;
		}
	}
	// 年龄增长
	void grow()
	{
		_age++;
		cout << _name << " just grew up.\nNow, age is " << _age << "." << endl;
	}
	// kill
	void kill()
	{
		cout << _name << " was killed by an unknown force." << endl;
		this -> ~Person();
	}

private:
	string _name;
	unsigned short _age;
	float _height, _weight;
};

int main()
{
	Person p1;
	Person p2("Chihara", 0, 55.0, 3.5);
	p1.eat("apple");
	p2.eat("strawberry", 9);
	p1.sleep();
	p2.sleep();
	p1.grow();
	p2.grow();
	p2.grow();
	p1.kill();

	return 0;
}