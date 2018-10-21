// Containers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>
#include <thread>
#include <queue>
#include <forward_list>
#include <array>


using namespace std;

/* 1.1 */
bool HasDublicateCharacter_11(const string& str)
{
	unordered_set<char> chars;
	for (auto ch : str)
		if (chars.find(ch) != chars.end())
			return true;
		else
			chars.insert(ch);
	return false;
}

/* 1.2 */
bool IsPermutation(const string& str1, const string& str2)
{
	if (str1.length() != str2.length())
		return false;

	int letters[128] = {};
	for (auto letter : str1)
		letters[letter]++;

	for (auto letter : str2)
	{
		letters[letter]--;
		if (letters[letter] < 0)
			return false;
	}

	return true;
}

/* 1.4 */
bool IsPolygramPermutation(const string& str)
{
	unordered_map<char, int> counts;
	for (auto ch : str)
		if (isalpha(ch))
			counts[ch]++;

	short count = 0;
	for (auto it : counts)
		count += it.second % 2;
	if (count > 1)
		return false;
	return true;
}

/* 1.5 */
bool SameWidth(const string& str1, const string& str2)
{
	int count = 0;
	for (int i = 0; i < str1.length(); ++i)
	{
		count += (str1[i] != str2[i]);
		if (count > 1)
			return false;
	}
	return true;
}


bool SameReplace(const string& str1, const string& str2)
{
	return true;
}

bool oneEditinsert(string s1, string s2) {
	int index1 = 0;
	int index2 = 0;
	while( index2 < s2.length() && index1 < s1.length() )
	{
		if( s1[index1] != s2[index2] )
		{
			if( index1 != index2 )
				return false;
			index2++;
		}
		else 
		{
			index1++;
			index2++;
		}
	}
	return true;
}

/* 1.6 */
template <typename T, const unsigned int N> __inline const unsigned int countof(T(&)[N]) { return N; }

string itoa(int i, int radix=10)
{
	char	buffer[65];

	_itoa_s(i, buffer, countof(buffer), radix);
	return buffer;
}

string Compress(const string& str)
{
	string compressed = "";
	int counter = 0;
	for (int i = 0; i < str.length(); i++)
	{
		counter++;
		if(i+1 >= str.length() || str[i] != str[i + 1])
		{
			compressed += str[i] + itoa(counter);
			counter = 0;
		}
	}
	return str.length() > compressed.length() ? compressed : str;
}

bool OneChange(const string& str1, const string& str2)
{
	if (str1.length() == str2.length())
		return SameWidth(str1, str2);

	if (str1.length() < str2.length())
		return SameReplace(str1, str2);
	else
		return SameReplace(str2, str1);
}

/* 2.1*/
void DeleteDuplicate(list<int>& ls)
{
	unordered_set<int> uniqe = {};
	for (auto it = ls.begin(); it != ls.end(); ++it)
	{
		if (uniqe.find(*it) != uniqe.end())
		{
			it = ls.erase(it);
			--it;
		}
		else
			uniqe.insert(*it);
	}
}

void SortStack( stack<int>& st )
{
	int top = st.top();
	if( st.size() == 2)
	{
		st.pop();
		int topNext = st.top();
		if (topNext > top)
		{
			st.pop();
			st.push(top);
			st.push(topNext);
		}
	}
	if (st.size() > 2)
	{
		st.pop();
		int topNext = st.top();
		if (topNext > top)
		{
			st.pop();
			st.push(top);
			//st.push(topNext);
			top = topNext;
		}

		SortStack(st);
		st.push(top);
		SortStack(st);
	}
}

bool IsBalanced(const string& str)
{
	stack<char> st;
	for (auto sym : str)
	{
		if (sym == '[' || sym == '(')
			st.push(sym);
		else
		{
			if (st.empty())
				return false;
			
			char prev = st.top();
			if ((sym == ']' && prev != '[') || (sym == '(' && prev != ')'))
				return false;
			
			st.pop();
		}
	}

	return st.empty();
}
class MyClass
{

};

string RetString()
{
	string ret;
	ret = "Брожектор";
	
	return std::move(ret);
}
int main()
{
	string sss = RetString();

	SameWidth("eade", "eadd");
	/* 1.1 */
	string str = "edqefdfrgvv kdfvbsbvdfvafv";
	cout << "string - " << str.c_str() << (HasDublicateCharacter_11(str) ? " contain duplicate chars" : " doesn't contain duplicate chars") << "\n";
	str = "qwertyuiopasdfghjklzxcvbn";
	cout << "string - " << str.c_str() << (HasDublicateCharacter_11(str) ? " contain duplicate chars" : " doesn't contain duplicate chars") << "\n";

	/* 1.2 */
	cout << "strings: abcdef, fedcab is " << (IsPermutation("abcdef", "fedcab") ? " is permutation" : " doesn't permutation") << "\n";
	cout << "strings: Abcdef, fedcab is " << (IsPermutation("Abcdef", "fedcab") ? " is permutation" : " doesn't permutation") << "\n";

	/* 1.4 */
	cout << "strings: abcdefC fedcba" << (IsPolygramPermutation("abcdefC fedcba") ? " is polygramm permutation" : " doesn't polygramm permutation") << "\n";
	cout << "strings: abcdefCC fedcba" << (IsPolygramPermutation("abcdefCC fedcba") ? " is polygramm permutation" : " doesn't polygramm permutation") << "\n";
	cout << "strings: abcdefCD fedcba" << (IsPolygramPermutation("abcdefCD fedcba") ? " is polygramm permutation" : " doesn't polygramm permutation") << "\n";
	
	/* 1.6 */
	cout << "compress aabbccddee - " << Compress("aabbccddee").c_str() << "\n";
	cout << "compress aaabbbccddee - " << Compress("aaabbbccddee").c_str() << "\n";

	vector<int> v;
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(1);
		cout << "v.capacity() - " << v.capacity() << "v.size() - " << v.size() << "\n";
	}

	cout << "v.capacity() - " << v.capacity() << "v.size() - " << v.size() << "\n";
	for (int i = 0; i < 100; ++i)
	{
		v.pop_back();
		cout << "v.capacity() - " << v.capacity() << "v.size() - " << v.size() << "\n";
	}

	list<int> ls = { 1,2,9, 8, 3,4,1,3,7,8,9, 1, 1 };
	ls.sort();
	DeleteDuplicate(ls);

	stack<int> st;
	st.push(3);
	st.push(16);
	st.push(1);
	st.push(2);
	st.push(15);
	st.push(4);

	SortStack(st);

	bool balans = IsBalanced( "([][])");
	balans = IsBalanced("][])");
	balans = IsBalanced("([]");

	queue<int> dd;


	priority_queue<int> pq;
	pq.push(11);
	pq.push(16);
	pq.push(1);
	pq.push(2);
	pq.push(4);
	pq.push(5);
	pq.push(6);
	pq.push(10);
	pq.push(8);
	pq.push(9);

	int i = pq.top();

	vector<int> v1;
	v1.push_back(2);
	v1.push_back(5);
	v1.push_back(4);
	v1.push_back(14);
	v1.push_back(5);
	v1.push_back(22);
	v1.push_back(17);
	v1.push_back(9);
	const int * hh = v1.data();
	
	make_heap(v1.begin(), v1.end());
	sort_heap(v1.begin(), v1.end());
	///*bool isHeap = is_heap(v1.begin(), v1.end());
	bool isHeap = is_heap(v1.begin(), v1.end());

	//pop_heap(v1.begin(), v1.end());

	deque<int> dq;
	dq.push_front(7);
	map<int, int> mapInt;
	mapInt.insert(make_pair(1,5));
	mapInt.insert(make_pair(5, 5));
	mapInt.insert(make_pair(3, 5));
	mapInt.insert(make_pair(2, 5));
	for (auto it = mapInt.cbegin(); it != mapInt.end(); ++it)
		cout << (*it).first << " " << endl;

	vector<string> sv;
	sv.push_back("111");
	sv.emplace_back("223");	
	sv.emplace_back("223");
	sv.emplace_back("225");
	sv.emplace_back("225");
	sv.emplace_back("225");
	sv.emplace_back("223");
	auto ita = sv.begin();
	auto ri=std::remove(sv.begin(), sv.end(), "223");
	
	
	multiset<int> mapTest;
	mapTest.insert(1);
	mapTest.insert(7);
	mapTest.insert(3);
	mapTest.insert(3);
	mapTest.insert(3);
	mapTest.insert(5);
	mapTest.insert(11);
	mapTest.insert(21);
	mapTest.insert(31);
	mapTest.insert(4);
	mapTest.insert(8);

	cout << " set  " << endl;
	auto fi = mapTest.lower_bound(3);
	auto la = mapTest.upper_bound(11);
	auto eq = mapTest.equal_range(33);
	for( auto it = fi; it != la; ++it )
		cout << *it << " " << endl;
	
	cout << " set  " << endl;
	for( auto it: mapTest )
		cout << it << " " << endl;
	
	bitset<34> fff;
	vector<bool> qqqq;

	deque<int> deq = { 1,2,3,4 };
	int g = deq[3];
	unordered_map<int, int> mapInt1;
	mapInt1.insert(make_pair(1, 5));
	mapInt1.insert(make_pair(5, 5));
	mapInt1.insert(make_pair(3, 5));
	mapInt1.insert(make_pair(2, 5));
	for (auto it = mapInt1.cbegin(); it != mapInt1.end(); ++it)
		cout << (*it).first << " " << endl;

	std::forward_list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	//    l.erase( l.begin() ); // ERROR: No function erase

	l.erase_after(l.before_begin()); // Removes first element

	for (auto n : l) std::cout << n << " ";
	std::cout << '\n';

	for (auto n : l) std::cout << n << " ";
	std::cout << '\n';
	
	//stack<int> jjj;
	//queue<int> hhh;
	//forward_list<int> fl;// = { 1,2,3,4,5 };
	////fl.push_front(4);
	//fl.insert_after(fl.begin(), 3);
	//fl.insert_after(fl.begin(), 2);
	//fl.insert_after(fl.begin(), 1);
	////fl.push_front(2);
	////fl.push_front(3); 
	////fl.push_front(4);
	////int sz = fl.max_size();
	////fl.empty();
	//
	//auto it = fl.before_begin();
	//for (auto it : fl)
	//	cout << it << endl;
	//return 0;
}

/*
int main(void)
{
	vector <int> vec;
	vector <int>::iterator Iter1;
	int i;

	// push data in range
	for (i = 1; i <= 9; i++)
		vec.push_back(i);

	// make vec vector a heap with default less-than ordering
	cout << "Operation: random_shuffle(vec.begin(), vec.end())" << endl;
	random_shuffle(vec.begin(), vec.end());
	make_heap(vec.begin(), vec.end());
	cout << "The heaped version of vec vector data is: ";
	for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++)
		cout << *Iter1 << " ";

	cout << endl;

	// add an element to the back of the heap
	vec.push_back(11);
	push_heap(vec.begin(), vec.end());
	cout << "The re-heaped vec vector data with 11 added: ";

	for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << endl;

	// remove the largest element from the heap
	cout << "\nOperation: pop_heap(vec.begin(), vec.end())" << endl;
	pop_heap(vec.begin(), vec.end());
	cout << "The heap vec vector data with 11 removed is: ";
	for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++)
		cout << *Iter1 << " ";

	cout << endl;

	// make vec a heap with greater-than ordering with a 0 element

	cout << "\nOperation: make_heap(vec.begin(), vec.end(), greater<int>())" << endl;

	make_heap(vec.begin(), vec.end(), greater<int>());

	vec.push_back(0);

	push_heap(vec.begin(), vec.end(), greater<int>());

	cout << "The greater than re-heaped vec vector data puts the smallest element first:";

	for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++)

		cout << *Iter1 << " ";

	cout << endl;

	// application of pop_heap() to remove the smallest element

	cout << "\nOperation: pop_heap(vec.begin(), vec.end(), greater<int>())" << endl;

	pop_heap(vec.begin(), vec.end(), greater<int>());

	cout << "The greater than heaped vec vector data with the smallest element removed from the heap is: ";

	for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++)

		cout << *Iter1 << " ";

	cout << endl;

	return 0;

}
*/