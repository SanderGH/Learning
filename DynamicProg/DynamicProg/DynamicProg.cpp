// DynamicProg.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

////////////////////////////////////////////////////
//     fibonachi
long long FibonacciExp(int N)
{
	if (N < 0)
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
		fibs.resize(N + 1, -1);
	return CalcFibTD(N);
}

long long CalcFibDT(size_t N)
{
	vector<long long> v(N + 1, -1);
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
void Print(const string& title, const T& vec)
{
	cout << title.c_str();
	for (auto i : vec)
		cout << i << " ";
	cout << endl;
}

void LISBottomUp(const vector<int>& seq)
{
	Print("Sequensce    - ", seq);
	vector<int> lenghts(seq.size(), 0);

	for (int i = 0; i < seq.size(); i++)
	{
		int prev = 0;
		for (int j = 0; j <= i - 1; j++)
		{
			if (seq[j] < seq[i] && lenghts[j] > prev)
				prev = lenghts[j];
		}
		lenghts[i] = prev + 1;
	}
	Print("Lenghts      - ", lenghts);

	auto itMax = max_element(lenghts.begin(), lenghts.end());
	auto maxLen = *itMax;
	auto maxIndex = distance(lenghts.begin(), itMax);

	list<int> res;
	res.push_front(seq[maxIndex]);

	for (int prevIndex = maxIndex - 1; prevIndex >= 0 && maxLen >= 1; prevIndex--)
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
int GirlStairs(const int N)
{
	vector<int> stairs(N + 1, 0);
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
int MagicIndex(const vector<int>& vec)
{
	int begin = 0;
	int end = vec.size() - 1;

	auto ggg = binary_search(vec.begin(), vec.end(), 9);

	while (begin <= end)
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
		if (counts[idx] == 1)
		{
			if (firsts[idx] < min_indx)
				min_indx = firsts[idx];
		}
	}

	if (min_indx == s.size())
		return '_';
	else
		return s[min_indx];
};


class Solution {
public:

	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
			return l2;

		if (l2 == nullptr)
			return l1;

		ListNode* result = new ListNode(0), *cur = result;
		int carry = 0;
		while (l1 != nullptr || l2 != nullptr)
		{
			int dig1 = l1 ? l1->val : 0;
			int dig2 = l2 ? l2->val : 0;
			int sum = dig1 + dig2 + carry;
			carry = sum / 10;

			cur->next = new ListNode(sum % 10);
			cur = cur->next;

			if (l1 != nullptr)
				l1 = l1->next;

			if (l2 != nullptr)
				l2 = l2->next;
		}

		if (carry)
			cur->next = new ListNode(carry);

		cur = result->next;
		delete result;
		return cur;
	}

	vector<int> twoSum(vector<int>& nums, int target) {

		std::unordered_map<int, int> addit;
		for (int i = 0; i < nums.size(); i++)
		{
			auto it = addit.find(target - nums[i]);
			if (it != addit.end())
				return { it->second, i };
			addit.insert(make_pair(nums[i], i));
		}
		return {};
	}

	bool isPalindrome(int x) {
		if (x < 0)
			return false;

		std::string s = std::to_string(x);
		for (int begin = 0, end = s.length() - 1; begin <= end; begin++, end--)
			if (s[begin] != s[end])
				return false;
		return true;
	}

	bool isPalindrome2(int x) {
		if (x < 0)
			return false;

		vector<int> digs;
		while (x >= 10)
		{
			digs.push_back(x % 10);
			x = x / 10;
		}
		digs.push_back(x);

		for (int begin = 0, end = digs.size() - 1; begin <= end; begin++, end--)
			if (digs[begin] != digs[end])
				return false;
		return true;
	}

	bool isPalindrome3(int x) {
		if (x < 0)
			return false;

		int del = x;
		int result = 0, remind = 0;
		while (del >= 10)
		{
			remind = del % 10;
			result = (result + remind) * 10;
			del = del / 10;
		}
		result += del;
		return result == x;
	}

	vector<int> plusOne(vector<int>& digits) {
		vector<int> result(digits.begin(), digits.end());

		int carry = 1;
		for (int i = digits.size() - 1; i >= 0; --i)
		{
			result[i] = ((digits[i] + carry) % 10);
			carry = (digits[i] + carry) / 10;
		}

		if (carry)
			result.insert(result.begin(), carry);

		return result;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* result = new ListNode(0), *curr = result;

		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				curr->next = new ListNode(l1->val);
				curr = curr->next;
				l1 = l1->next;
			}
			else
			{
				curr->next = new ListNode(l2->val);
				curr = curr->next;
				l2 = l2->next;
			}
		}

		ListNode*  remind = l1 ? l1 : l2;
		while (remind)
		{
			curr->next = new ListNode(remind->val);
			curr = curr->next;
			remind = remind->next;
		}

		curr = result->next;
		delete result;
		return curr;
	}

	int maxSubArray(vector<int>& nums) {
		int prevSum = nums[0], maxSum = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			prevSum = max(nums[i], nums[i] + prevSum);
			if (prevSum > maxSum)
				maxSum = prevSum;
		}

		return maxSum;
	}

	vector<int> cachedSum;

	void NumArray(vector<int> nums) {
		if (!nums.size())
			return;

		cachedSum = vector<int>(nums.size());
		cachedSum[0] = nums[0];
		for (int i = 1; i < nums.size(); i++)
			cachedSum[i] = cachedSum[i - 1] + nums[i];
	}

	int sumRange(int i, int j) {
		if (!cachedSum.size())
			return 0;
		if (i == 0)
			return cachedSum[j];
		return cachedSum[j] - cachedSum[i - 1];
	}


	int numJewelsInStones(string J, string S) {
		int counter = 0;
		unordered_set<char> jewels;
		for_each(J.begin(), J.end(), [&](char ch) { jewels.insert(ch); });
		for_each(S.begin(), S.end(), [&](char ch) {
			if (jewels.find(ch) != jewels.end())
				++counter;
		});
		return counter;
	}

	vector<string> subdomainVisits(vector<string>& cpdomains) {
		vector<string> res;
		unordered_map<string, int> counts;
		for (auto cpdomain : cpdomains)
		{
			auto index = cpdomain.find(' ');
			if (index != string::npos)
			{
				int count = std::stoi(cpdomain.substr(0, index));
				string domains = cpdomain.substr(index + 1);

			}
		}
		return res;
	}

	int removeElement(vector<int>& nums, int val) {
		auto newEnd = std::remove(nums.begin(), nums.end(), val);
		return std::distance(nums.begin(), newEnd);
	}

	int searchInsert(vector<int>& nums, int target) {
		if (nums[0] >= target)
			return 0;

		if (nums[nums.size() - 1] < target)
			return nums.size();

		if (nums[nums.size() - 1] == target)
			return nums.size() - 1;

		for (int i = 0; i < nums.size() - 1; i++)
		{
			if (nums[i] == target)
				return i;
			if (nums[i] < target && nums[i + 1] > target)
				return i + 1;
		}
	}

	int lengthOfLastWord(string s) {
		if (s.empty())
			return 0;
		auto index = s.rfind(' ');
		return index == string::npos ? s.length() : s.length() - index - 1;
	}

	int findComplement(int num) {
		int count = 1, tmp = num;
		while (tmp = tmp >> 1)
			++count;

		int mask = 1;
		while (--count)
			mask = (mask << 1) + 1;

		return (~num)&mask;
	}

	char findTheDifference(string s, string t) {
		/*unordered_map<char, int> counts;
		for (auto i : t)
		{
			auto find = counts.find(i);
			if (find != counts.end())
				++find->second;
			else
				counts.insert(make_pair( i, 1));
		}

		for (auto i : s)
		{
			auto find = counts.find(i);
			if (find != counts.end())
				if (find->second == 1)
					counts.erase(i);
				else
					--find->second;
		}

		return counts.begin()->first;*/

		char r = 0;
		for (char c : s)
			r ^= c;
		for (char c : t)
			r ^= c;
		return r;
	}
};

int main()
{
	Solution sol;
	sol.findComplement(5);
	auto dif = sol.findTheDifference("aaabcd", "abacade");

	vector<int> remov{ 0,1,2,2,3,0,4,2 };
	auto count = sol.removeElement(remov, 2);
	vector<int> vInsert{ 1,3,5,6 };
	auto index = sol.searchInsert(vInsert, 5);

	constexpr auto ff = 10'000'000;
	mutex mtx;
	//	std::unique_lock<mutex> f( mtx,  );
	auto kk = firstNotRepeatingCharacter("abacabad");
	auto x{ 1 };
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
	vector<int> in({ 1,3,5,6,9,7 });
	auto indexes = sol.twoSum(in, 17);

	bool poly = sol.isPalindrome3(-12);
	poly = sol.isPalindrome3(10);
	poly = sol.isPalindrome3(121);
	poly = sol.isPalindrome3(1211);
	poly = sol.isPalindrome3(1221);


	auto plus = sol.plusOne(vector<int>{1, 2, 3, 4});
	plus = sol.plusOne(vector<int>{1, 2, 3, 9});
	plus = sol.plusOne(vector<int>{1, 9, 9, 9});
	plus = sol.plusOne(vector<int>{9, 9, 9, 9});
	plus = sol.plusOne(vector<int>{0});

	Solution::ListNode* l1 = new Solution::ListNode(1);
	l1->next = new Solution::ListNode(2);

	Solution::ListNode* l2 = new Solution::ListNode(1);
	l2->next = new Solution::ListNode(3);

	auto res = sol.mergeTwoLists(l1, l2);

	sol.NumArray({});
	auto sum = sol.sumRange(0, 2);

	auto jewels = sol.numJewelsInStones("aA", "aAAAAA");
	sol.subdomainVisits(vector<string>{ "900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org" });

	return 0;
}

