// TestRomanNumeral.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "gtest\gtest.h"

#include "RomanNumeral.h"

#include <vector>
#include <string>

using namespace std;

TEST(Roman_numeral_single_letter_validation, RomanNumeral)
{
	vector<pair<string, bool>> testRomans{
		{ "I", true },
		{ "V", true },
		{ "X", true },
		{ "L", true },
		{ "C", true },
		{ "D", true },
		{ "M", true },
		{ "Z", false },
		{ "&", false },
	};

	for (auto& x : testRomans)
	{
		bool bIsValid = RomanNumeral::containsValidRomanNumeralChar(x.first);
		EXPECT_EQ(bIsValid, x.second);
		cout << x.first << "=>" << x.second << ", ";
	}
	cout << endl;
}


/*
{ "XXX", true },
{ "XXXX", false },
{ "XXXIX", true },
{ "IIIII", false },
*/
TEST(Roman_numeral_duplicate_letter_validation, RomanNumeral)
{
	vector<pair<string, bool>> testRomans{
		{ "II", true },
		{ "III", true },
		{ "IIII", false },
		{ "IIIII", false },
		{ "XXXIX", true },
		{ "XXIXX", true },
		{ "LLX", false },
		{ "DD", false },
		{ "LLDD", false },
		{ "DDDDD", false },
		{ "VV", false },
		{ "V", true },
		{ "IV", true },
		{ "XXXMX", false },
		{ "XXXLX", false },
		{ "XXXCX", false },
		{ "XXXDX", false }
	};

	for (auto& x : testRomans)
	{
		bool bIsValid = RomanNumeral::IsDuplicationOfCharValid(x.first);
		EXPECT_EQ(bIsValid, x.second);
		cout << x.first << "=>" << x.second << ", ";
	}
	cout << endl;
}



TEST(Roman_numeral_subtraction_rules_validation, RomanNumeral)
{
	vector<pair<string, bool>> testRomans{
		{ "IV", true },
		{ "IX", true },

		{ "IL", false },
		{ "IC", false },
		{ "ID", false },
		{ "IM", false },

		{ "IVIL", false },
		{ "IXIC", false },
		{ "IXID", false },
		{ "IXIM", false },


		{ "XL", true },
		{ "XC", true },

		{ "XI", true },
		{ "XD", false },
		{ "XM", false },

		{ "XVIL", false },
		{ "IXXC", true },
		{ "IXXL", true },

		{ "XLXI", true },

		{ "CD", true },
		{ "CM", true },


		{ "LD", false },
		{ "LD", false },

		{ "MCMII", true },
	};

	for (auto& x : testRomans)
	{
		bool bIsValid = RomanNumeral::IsSubtractionSequenceValid(x.first);
		EXPECT_EQ(bIsValid, x.second);
		cout << x.first << "=>" << x.second << ", ";
	}
	cout << endl;
}


TEST(valid_numeral_check, RomanNumeral)
{
	vector<pair<string, bool>> testRomans{

		{ "I", true },
		{ "V", true },
		{ "X", true },
		{ "L", true },
		{ "C", true },
		{ "D", true },
		{ "M", true },
		{ "Z", false },
		{ "&", false },

		{ "IV", true },
		{ "IX", true },

		{ "IL", false },
		{ "IC", false },
		{ "ID", false },
		{ "IM", false },

		{ "IVIL", false },
		{ "IXIC", false },
		{ "IXID", false },
		{ "IXIM", false },


		{ "XL", true },
		{ "XC", true },

		{ "XI", true },
		{ "XD", false },
		{ "XM", false },

		{ "XVIL", false },
		{ "IXXC", true },
		{ "IXXL", true },

		{ "XLXI", true },

		{ "CD", true },
		{ "CM", true },


		{ "LD", false },
		{ "LD", false },

		{ "II", true },
		{ "III", true },
		{ "IIII", false },
		{ "IIIII", false },
		{ "XXXIX", true },
		{ "XXIXX", true },
		{ "LLX", false },
		{ "DD", false },
		{ "LLDD", false },
		{ "DDDDD", false },
		{ "VV", false },
		{ "V", true },
		{ "IV", true },
		{ "XXXMX", false },
		{ "XXXLX", false },
		{ "XXXCX", false },
		{ "XXXDX", false },
		{ "MCMII", true },
	};

	for (auto& x : testRomans)
	{
		bool bIsValid = RomanNumeral::isRomanNumberValid(x.first);
		EXPECT_EQ(bIsValid, x.second);
		cout << x.first << "=>" << x.second << ", ";
	}
	cout << endl;
}

TEST(Evaluation, RomanNumeral)
{
	vector<pair<string, int>> testRomans{
		{ "I", 1 }, { "II", 2 }, { "III", 3 }, { "IV", 4 }, { "V", 5 },
		{ "VI", 6 }, { "VII", 7 }, { "VIII", 8 }, { "IX", 9 }, { "X", 10 },
		{ "XI", 11 }, { "XII", 12 }, { "XIII", 13 }, { "XIV", 14 }, { "XV", 15 },
		{ "XVI", 16 }, { "XVII", 17 }, { "XVIII", 18 }, { "XIX", 19 }, { "XX", 20 },
		{ "XXI", 21 }, { "XXII", 22 }, { "XXIII", 23 }, { "XXIV", 24 }, { "XXV", 25 },
		{ "XXVI", 26 }, { "XXVII", 27 }, { "XXVIII", 28 }, { "XXIX", 29 }, { "XXX", 30 },
		{ "XL", 40 }, { "L", 50 }, { "LIX", 59 }, { "LX", 60 }, { "LXIV", 64 },
		{ "XCIX", 99 }, { "C", 100 }, { "MCMXCIX", 1999 }, { "MMXIV", 2014 }, { "IIII", 4 },
		{ "VIIII", 9 }, { "XIIX", 18 }, { "XIIIII", 15 }, { "MDCCCCX", 1910 }, { "MDCDIII", 1903 },
		{ "XXXXXX", 60 }, { "XXXXXX", 60 }, { "MCMIII", 1903 } };

	for (const auto& x : testRomans) {
		auto num = RomanNumeral::getDecimalEquivalent(x.first);
		assert(num == x.second);
		cout << num << ", ";
	}
	cout << endl;
}
