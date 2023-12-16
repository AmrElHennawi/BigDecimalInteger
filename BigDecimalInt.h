#pragma once
#include <iostream>
#include <deque>
#include <regex>

using namespace std;

// class
class BigDecimalInt
{
private:
	string decStr;
	string signType = "+";
	void storeInDeque(deque<int>&, deque<int>&, BigDecimalInt, int);
	void add(deque<int>&, deque<int>&, int);
	void subtract(deque<int>&, deque<int>&, int);
	bool isSmaller(deque<int>&, deque<int>&, int);
	bool isBigger(deque<int>&, deque<int>&, int);
	bool isEqual(deque<int>&, deque<int>&, int);
	void removeZeros(deque<int>&, deque<int>&, int);

public:
	BigDecimalInt(string);
	BigDecimalInt(int);
	string operator+(BigDecimalInt);
	string operator-(BigDecimalInt);
	bool operator<(BigDecimalInt);
	bool operator>(BigDecimalInt);
	bool operator==(BigDecimalInt);
	void operator=(BigDecimalInt);
	int size();
	string sign();
	friend ostream& operator<<(ostream&, BigDecimalInt);
};

// function prototype
bool isNumberValid(string);
