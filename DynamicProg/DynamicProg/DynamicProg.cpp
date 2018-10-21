// DynamicProg.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

////////////////////////////////////////////////////
//     fibonachi
long long FibonacciExp(int N)
{
	if( N < 0 )
		return 0;
	if (N <= 1)
		return N;
	return FibonacciExp(N - 1) + FibonacciExp(N - 2);
}

static vector<long long> fibs;
long long CalcFibTD(size_t N)
{
	if (fibs[N] == -1)
	{
		if (N <= 1)
			fibs[N] = N;
		else
			fibs[N] = CalcFibTD(N - 1) + CalcFibTD(N - 2);
	}
	return fibs[N];
}
long long FibTD(size_t N)
{
	if (fibs.size() < N + 1)
		fibs.resize(N+1, -1);
	return CalcFibTD(N);
}

long long CalcFibDT(size_t N)
{
	vector<long long> v(N + 1,-1);
	v[0] = 0;
	v[1] = 1;
	for (int i = 2; i <= N; i++)
		v[i] = v[i - 2] + v[i - 1];
	return v[N];
}

long long SimpleFib(size_t N)
{
	long long prev = 0;
	long long cur = 1;
	for (int i = 2; i <= N; i++)
	{
		auto next = prev + cur;
		prev = cur;
		cur = next;
	}
	return cur;
}
void Fibonacci()
{
	auto start = chrono::steady_clock::now();
	auto fib = FibonacciExp(40);
	auto end = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	std::cout << "Exponent for 40 - " << elapsed.count() << " ns\n";

	start = chrono::steady_clock::now();
	auto fib1 = FibTD(100);
	end = chrono::steady_clock::now();
	elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	std::cout << "Top to down for 40 - " << elapsed.count() << " ns\n";

	start = chrono::steady_clock::now();
	auto fib2 = CalcFibDT(100);
	end = chrono::steady_clock::now();
	elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	std::cout << "Down to top for 40 - " << elapsed.count() << " ns\n";

	start = chrono::steady_clock::now();
	auto fib3 = SimpleFib(100);
	end = chrono::steady_clock::now();
	elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	std::cout << "Without additional memory - " << elapsed.count() << " ns\n";
}
template<class T>
void Print(const string& title, const T& vec )
{
	cout << title.c_str();
	for (auto i : vec)
		cout << i << " ";
	cout << endl;
}

void LISBottomUp(const vector<int>& seq)
{
	Print( "Sequensce    - ", seq);
	vector<int> lenghts( seq.size(), 0);

	for( int i = 0; i < seq.size(); i++)
	{
		int prev = 0;
		for( int j = 0; j <= i-1; j++ )
		{
			if (seq[j] < seq[i] && lenghts[j] > prev)
				prev = lenghts[j];
		}
		lenghts[i] = prev + 1;
	}
	Print( "Lenghts      - " , lenghts);

	auto itMax = max_element(lenghts.begin(), lenghts.end());
	auto maxLen = *itMax;
	auto maxIndex = distance(lenghts.begin(), itMax);

	list<int> res;
	res.push_front(seq[maxIndex]);

	for (int prevIndex = maxIndex-1; prevIndex >= 0 && maxLen >= 1; prevIndex--)
	{
		if (lenghts[prevIndex] == lenghts[maxIndex] - 1 && seq[prevIndex] < seq[maxIndex])
		{
			res.push_front(seq[prevIndex]);
			maxIndex = prevIndex;
			--maxLen;
		}
	}
	Print("Results      - ", res);
	//return 0;
}

/*
Ребенок поднимается по лестнице из n ступенек. За один шаг он может переместиться на одну, две или три ступеньки. 
Реализуйте метод, рассчитывающий количество возможных вариантов перемещения ребенка по лестнице.
*/
int GirlStairs( const int N)
{
	vector<int> stairs(N +1, 0);
	stairs[0] = 1;
	stairs[1] = 1;
	stairs[2] = 2;
	for (int i = 3; i <= N; i++)
	{
		stairs[i] = stairs[i - 1] + stairs[i - 2] + stairs[i - 3];
	}
	return stairs[N];
}

/*
Определим «волшебный» индекс для массива A [ 0".n - 1 ] как индекс, для которого выполняется условие А[i] =i. Для заданного отсортированого массива,
не содержащего одинаковых значений, напишите метод воиска «волшебного» индекса в массиве А (если он существует).
*/
int MagicIndex( const vector<int>& vec )
{
	int begin = 0;
	int end = vec.size()-1;
	
	auto ggg = binary_search(vec.begin(), vec.end(), 9);

	while (begin <= end )
	{
		int mid = begin + (end - begin) / 2;
		if (vec[mid] == mid)
			return mid;
		else if (vec[mid] > mid)
			end = mid - 1;
		else
			begin = mid + 1;
	}
	return -1;
}


//class MyClass
//{
//	string m_name;
//public:
//	 MyClass(const string& name): m_name(name) {};
//	 get_name()
//};

//template <class T>
//void f(T* t)
//{
//}
//
//template <class T>
//void g(T t)
//{
//	f(t);
//}
class A
{
	int i;
public:
};

class B
{
	int i;
public:
};

void f(int)
{
}

void f(A*)
{
}

void f(B*)
{
}

char firstNotRepeatingCharacter(const std::string& s)
{
	std::vector<int> counts(256, 0);
	std::vector<int> firsts(256, 0);
	for (size_t idx = 0; idx < s.size(); ++idx)
	{
		if (counts[s[idx]] == 0)
			firsts[s[idx]] = idx;

		counts[s[idx]] += 1;
	}

	int min_indx = s.size();
	for (size_t idx = 1; idx < counts.size(); ++idx)
	{
		if(counts[idx] == 1)
		{
			if( firsts[idx] < min_indx )
				min_indx = firsts[idx];
		}
	}

	if (min_indx == s.size())
		return '_';
	else 
		return s[min_indx];
};

template <class Type>
class MyTemp
{
	Type val;
public:
	MyTemp(Type i) : val(i) {};
	Type get() { return val.get(); };
};
template MyTemp<int>;

int main()
{
	MyTemp<int> ddd(4);
	
	constexpr auto ff = 10'000'000;
 	mutex mtx;
//	std::unique_lock<mutex> f( mtx,  );
	auto kk = firstNotRepeatingCharacter("abacabad");
	auto x  { 1 };
	std::vector<int> v1{ 5 };
	std::vector<int> v2(5);
	std::vector<int> v3({ 5 });
	std::vector<int> v4{ 5 };
	//std::vector<int> v5 = 5;

	std::initializer_list<int> hhh{ 1,2,3,4,5,6 };
	int * i = new int(5); 
	cout << i << " " << endl;
	i = nullptr;
	delete i;
	cout << i << " " << endl;

	string str = "frefewf";


	//set<int> ssss;
	//ssss.insert(5);
	//vector<int> seq(30);// = { 7, 2, 1, 3, 8, 4, 9, 1, 2, 6, 5, 9, 3, 8, 1 };
	//std::for_each(seq.begin(), seq.end(), [](int& i) {i = rand() % 30; });
	//LISBottomUp(seq);

	//// girl 
	//GirlStairs( 10 );

	//// magicIndex
	//vector<int> magicVec = { -40, -20, -1,	1,	2 , 3, 5, 7, 9, 12, 13, 23};
	//int magicI = MagicIndex(magicVec);
	//magicVec = { -10, - 5,	2,	2,	2,	3,	4,	7,	9,	12,	13 };
	//magicI = MagicIndex(magicVec);
	////Fibonacci();

	//vector<int> v(61);
	//std::for_each(v.begin(), v.end(), [](int& i) {i = rand() % 100; });
	////= { 17, 3, 5, 6, 1, 22 , 19, 18, 23, 51, 26, 21, 12, 13, 33,41, 100 };
	//vector<int> v2 = v;
	//Print("v -", v);

	//nth_element(v.begin(), v.begin() + v.size()/2, v.end());
	//Print("v -", v);
	////nth_element(v2.begin(), v2.begin() + 3, v2.end());
	////Print("v -", v2);
	//nth_element(v2.begin(), v2.begin() + 11, v2.end());
	//Print("v -", v2);

	//sort(v.begin(), v.end());
	//Print("v -", v);

	//vector<int> v_part(100);
	//std::for_each(v_part.begin(), v_part.end(), [](int& i) {i = rand() % 100; });
	//partial_sort(v_part.begin(), v_part.begin() + 20, v_part.end());
	//Print("v_part -", v_part);


	//int * i = new int(6);
	//shared_ptr<int> p1(i);
	//shared_ptr<int> p2(i);

	//vector<int> v{ 1,2,3,4,5 };
	//for( auto& i: v )
	
	return 0;
}

