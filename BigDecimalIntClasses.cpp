#include "BigDecimalInt.h"

using namespace std;

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
void BigDecimalInt::storeInDeque(deque<int> &numList, deque<int> &oprndNumList, BigDecimalInt oprndObj, int mxSize)
{
	int counter, toInt, difference;
	/*Calculate the difference in length between the two numbers
	to fill the beginning of the smallest number in length with zeros*/
	difference = mxSize - decStr.length();
	counter = 0;
	/*This for loop store the string numbers from the end to the begining in the deque after turning it to int*/
	for (int i = difference; i < decStr.length() + difference; i++)
	{
		toInt = decStr[counter] - '0';
		numList[i] = toInt;
		counter++;
	}
	difference = mxSize - oprndObj.decStr.length();
	counter = 0;
	for (int i = difference; i < oprndObj.decStr.length() + difference; i++)
	{
		toInt = oprndObj.decStr[counter] - '0';
		oprndNumList[i] = toInt;
		counter++;
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________

void BigDecimalInt::add(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	int check;
	// looping on the two deques fom the end to the begining to add them in the first one
	for (int i = mxSize - 1; i >= 0; i--)
	{
		check = (numList[i] + oprndNumList[i]);
		numList[i] = (numList[i] + oprndNumList[i]) % 10;
		// check for remender
		if (check > 9)
		{
			if (i == 0)
			{
				numList.emplace_front(1);
			}
			else
			{
				numList[i - 1]++;
			}
		}
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________

void BigDecimalInt::subtract(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	// check for the smaller number to swap lists
	for (int i = 0; i < mxSize; i++)
	{
		if (numList[i] < oprndNumList[i])
		{
			numList.swap(oprndNumList);
			break;
		}
		else if (numList[i] > oprndNumList[i])
		{
			break;
		}
	}
	// subtract
	for (int i = mxSize - 1; i >= 0; i--)
	{
		if (numList[i] - oprndNumList[i] < 0)
		{
			numList[i] = 10 + (numList[i] - oprndNumList[i]);
			numList[i - 1]--;
		}
		else
		{
			numList[i] = numList[i] - oprndNumList[i];
		}
	}
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::isSmaller(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	// check for the smallest number
	for (int i = 0; i < mxSize; i++)
	{
		if (numList[i] < oprndNumList[i])
		{
			return true;
		}
		else if (numList[i] > oprndNumList[i])
		{
			return false;
		}
	}
	return false;
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::isBigger(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	// check for the biggest number
	for (int i = 0; i < mxSize; i++)
	{
		if (numList[i] > oprndNumList[i])
		{
			return true;
		}
		else if (numList[i] < oprndNumList[i])
		{
			return false;
		}
	}
	return false;
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::isEqual(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	for (int i = 0; i < mxSize; i++)
	{
		if (numList[i] != oprndNumList[i])
		{
			return false;
		}
	}
	return true;
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
void BigDecimalInt::removeZeros(deque<int> &numList, deque<int> &oprndNumList, int mxSize)
{
	// Removing the zeros in the begining of the number
	for (int i = 0; i < numList.size(); i++)
	{
		if (numList[i] == 0)
		{
			numList.pop_front();
			i--;
		}
		else
		{
			break;
		}
	}
	// Retun one zero if the deque is empty
	if (numList.empty())
	{
		numList.emplace_back(0);
	}
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
BigDecimalInt::BigDecimalInt(string sNumber)
{
	// class string constructor
	if (isNumberValid(sNumber) && sNumber != "-0")
	{
		if (sNumber[0] == '-' || sNumber[0] == '+')
		{
			signType = sNumber[0];
			sNumber.erase(sNumber.begin());
		}
		decStr = sNumber;
	}
	else
	{
		cout << "Invalid Input ";
		exit(0);
	}
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
BigDecimalInt::BigDecimalInt(int iNumber)
{
	// class overloaded int constructor
	string strNum;
	strNum = to_string(iNumber);
	if (isNumberValid(strNum))
	{
		if (strNum[0] == '-' || strNum[0] == '+')
		{
			signType = strNum[0];
			strNum.erase(strNum.begin());
		}
		decStr = strNum;
	}
	else
	{
		cout << "Invalid pararmeter ";
		exit(0);
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________

string BigDecimalInt::operator+(BigDecimalInt oprndObj)
{
	string finalStrNumber;
	// finding the size of the biggest number to initialize the size of the two deques
	int mxSize = max(decStr.length(), oprndObj.decStr.length());
	deque<int> numList(mxSize);
	deque<int> oprndNumList(mxSize);

	storeInDeque(numList, oprndNumList, oprndObj, mxSize);
	// choosing the type of the operation depending on the signs of the numbers
	if (signType == "-" && oprndObj.signType == "-")
	{
		finalStrNumber += "-";
		add(numList, oprndNumList, mxSize);
	}
	else if (signType == "+" && oprndObj.signType == "+")
	{
		add(numList, oprndNumList, mxSize);
	}
	else if (signType == "+" && oprndObj.signType == "-")
	{
		for (int i = 0; i < mxSize; i++)
		{
			if (numList[i] < oprndNumList[i])
			{
				finalStrNumber += "-";
				break;
			}
			else if (numList[i] > oprndNumList[i])
			{
				break;
			}
		}
		subtract(numList, oprndNumList, mxSize);
	}
	else if (signType == "-" && oprndObj.signType == "+")
	{
		for (int i = 0; i < mxSize; i++)
		{
			if (numList[i] > oprndNumList[i])
			{
				finalStrNumber += "-";
				break;
			}
			else if (numList[i] < oprndNumList[i])
			{
				break;
			}
		}
		subtract(numList, oprndNumList, mxSize);
	}

	removeZeros(numList, oprndNumList, mxSize);
	// Converting the deque to string to return it as the operation return
	for (int i = 0; i < numList.size(); i++)
	{
		finalStrNumber += to_string(numList[i]);
	}

	return finalStrNumber;
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________

string BigDecimalInt::operator-(BigDecimalInt oprndObj)
{
	string finalStrNumber;
	// finding the size of the biggest number to initialize the size of the two deques
	int mxSize = max(decStr.length(), oprndObj.decStr.length());

	deque<int> numList(mxSize);
	deque<int> oprndNumList(mxSize);

	storeInDeque(numList, oprndNumList, oprndObj, mxSize);
	// choosing the type of the operation depending on the signs of the numbers
	if (signType == "-" && oprndObj.signType == "-")
	{
		for (int i = 0; i < mxSize; i++)
		{
			if (numList[i] > oprndNumList[i])
			{
				finalStrNumber += "-";
				break;
			}
			else if (numList[i] < oprndNumList[i])
			{
				break;
			}
		}
		subtract(numList, oprndNumList, mxSize);
	}
	else if (signType == "+" && oprndObj.signType == "+")
	{
		for (int i = 0; i < mxSize; i++)
		{
			if (numList[i] < oprndNumList[i])
			{
				finalStrNumber += "-";
				break;
			}
			else if (numList[i] > oprndNumList[i])
			{
				break;
			}
		}
		subtract(numList, oprndNumList, mxSize);
	}

	else if (signType == "+" && oprndObj.signType == "-")
	{
		add(numList, oprndNumList, mxSize);
	}
	else if (signType == "-" && oprndObj.signType == "+")
	{
		finalStrNumber += "-";
		add(numList, oprndNumList, mxSize);
	}
	removeZeros(numList, oprndNumList, mxSize);
	// Converting the deque to string to return it as the operation return
	for (int i = 0; i < numList.size(); i++)
	{
		finalStrNumber += to_string(numList[i]);
	}

	return finalStrNumber;
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::operator<(BigDecimalInt oprndObj)
{
	// search for the smallest number by signs
	if (signType == "-" && oprndObj.signType == "+")
	{
		return true;
	}
	else if (signType == "+" && oprndObj.signType == "-")
	{
		return false;
	}
	else
	{
		// finding the size of the biggest number to initialize the size of the two deques
		int mxSize = max(decStr.length(), oprndObj.decStr.length());

		deque<int> numList(mxSize);
		deque<int> oprndNumList(mxSize);

		storeInDeque(numList, oprndNumList, oprndObj, mxSize);
		// Search for the smallest number
		if (signType == "-" && oprndObj.signType == "-")
		{
			return isBigger(numList, oprndNumList, mxSize);
		}
		return isSmaller(numList, oprndNumList, mxSize);
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::operator>(BigDecimalInt oprndObj)
{
	// Finding the biggest number by the signs
	if (signType == "+" && oprndObj.signType == "-")
	{
		return true;
	}
	else if (signType == "-" && oprndObj.signType == "+")
	{
		return false;
	}
	else
	{
		// finding the size of the biggest number to initialize the size of the two deques
		int mxSize = max(decStr.length(), oprndObj.decStr.length());

		deque<int> numList(mxSize);
		deque<int> oprndNumList(mxSize);

		storeInDeque(numList, oprndNumList, oprndObj, mxSize);
		// Search for the beggist number
		if (signType == "-" && oprndObj.signType == "-")
		{
			return isSmaller(numList, oprndNumList, mxSize);
		}
		return isBigger(numList, oprndNumList, mxSize);
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
bool BigDecimalInt::operator==(BigDecimalInt oprndObj)
{
	// check if numbers are equal
	if (signType == oprndObj.signType)
	{
		// finding the size of the biggest number to initialize the size of the two deques
		int mxSize = max(decStr.length(), oprndObj.decStr.length());

		deque<int> numList(mxSize);
		deque<int> oprndNumList(mxSize);

		storeInDeque(numList, oprndNumList, oprndObj, mxSize);
		return isEqual(numList, oprndNumList, mxSize);
	}
	else
	{
		return false;
	}
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
void BigDecimalInt::operator=(BigDecimalInt oprndObj)
{
	// copying the data to operand object
	decStr = oprndObj.decStr;
	signType = oprndObj.signType;
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
ostream &operator<<(ostream &out, BigDecimalInt b)
{
	/*Check for the signType to determine whether it will
	 be printed with the number or not*/
	if (b.signType == "+")
	{
		out << b.decStr;
	}
	else
	{
		out << b.signType << b.decStr;
	}
	return out;
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
int BigDecimalInt::size()
{

	return decStr.length();
}
//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
string BigDecimalInt::sign()
{
	return signType;
}

//_______________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________
// Check if the input number valid or not
bool isNumberValid(string number)
{
	regex isValid("[+-]?[0-9]+");
	return regex_match(number, isValid);
}