// 测试vector的默认扩容机制
void TestVectorExpand()
{
	size_t sz;
	vector<int> v;
	sz = v.capacity();
	cout << "making v grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}
//vs：运行结果：vs下使用的STL基本是按照1.5倍方式扩容
//making foo grow :
//capacity changed : 1
//capacity changed : 2
//capacity changed : 3
//capacity changed : 4
//capacity changed : 6
//capacity changed : 9
//capacity changed : 13
//capacity changed : 19
//capacity changed : 28
//capacity changed : 42
//capacity changed : 63
//capacity changed : 94
//capacity changed : 141
//g++运行结果：linux下使用的STL基本是按照2倍方式扩容
//making foo grow :
//capacity changed : 1
//capacity changed : 2
//capacity changed : 4
//capacity changed : 8
//capacity changed : 16
//capacity changed : 32
//capacity changed : 64
//capacity changed : 128

// 如果已经确定vector中要存储元素大概个数，可以提前将空间设置足够
// 就可以避免边插入边扩容导致效率低下的问题了
void TestVectorExpandOP()
{
	vector<int> v;
	size_t sz = v.capacity();
	v.reserve(100); // 提前将容量设置好，可以避免一遍插入一遍扩容
	cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

#include <iostream>
using namespace std;
#include <vector>
int main()
{
	vector<int> v{ 1,2,3,4,5,6 };

	auto it = v.begin();

	// 将有效元素个数增加到100个，多出的位置使用8填充，操作期间底层会扩容
	// v.resize(100, 8);

	// reserve的作用就是改变扩容大小但不改变有效元素个数，操作期间可能会引起底层容量改变
	// v.reserve(100);

	// 插入元素期间，可能会引起扩容，而导致原空间被释放
	// v.insert(v.begin(), 0);
	// v.push_back(8);

	// 给vector重新赋值，可能会引起底层容量改变
	v.assign(100, 8);

	/*
	出错原因：以上操作，都有可能会导致vector扩容，也就是说vector底层原理旧空间被释放掉，
   而在打印时，it还使用的是释放之间的旧空间，在对it迭代器操作时，实际操作的是一块已经被释放的
   空间，而引起代码运行时崩溃。
	解决方式：在以上操作完成之后，如果想要继续通过迭代器操作vector中的元素，只需给it重新
   赋值即可。
	*/
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}

#include <iostream>
using namespace std;
#include <vector>
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	// 使用find查找3所在位置的iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	// 删除pos位置的数据，导致pos迭代器失效。
	v.erase(pos);
	cout << *pos << endl; // 此处会导致非法访问
	return 0;
}
