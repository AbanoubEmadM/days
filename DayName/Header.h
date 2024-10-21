#pragma once
#include <iostream>
using namespace std;

namespace Numbers
{
	bool LeapYear(int Year)
	{
		if (Year % 100 == 0 && Year % 400 == 0)
		{
			return true;
		}
		if (Year % 4 == 0 && Year % 100 != 0)
		{
			return true;
		}
		return false;
	}
	int ReadPositiveNumber(string Text)
	{
		int Number;
		do
		{
			cout << Text;
			cin >> Number;
		} while (Number < 0);
		return Number;
	}

	int RandomNumber(int From, int To)
	{
		int RandomNumber = rand() % (To - From + 1) + From;
		return RandomNumber;
	}
}