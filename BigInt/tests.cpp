#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "BigInt.h"
using namespace std;

	void test_sum() {
		assert(BigInt(25) + BigInt(2) == BigInt(25 + 2));
		assert(BigInt(25) + BigInt(25) == BigInt(25 + 25));
		assert(BigInt(2) + BigInt(25) == BigInt(2 + 25));
		assert(BigInt(25) + BigInt(-25) == BigInt(25 + -25));
		assert(BigInt(-25) + BigInt(25) == BigInt(-25 + 25));
		assert(BigInt(-25) + BigInt(-25) == BigInt(-25 + -25));
		assert(BigInt(25) + BigInt(-26) == BigInt(25 + -26));
		cout << "SUM TESTS SUCCESS" << endl;
	}

	void test_sub() {
		assert(int(BigInt(25) - BigInt(25)) == 25 - 25);
		assert(int(BigInt(25) - BigInt(26)) == 25 - 26);
		assert(int(BigInt(-25) - BigInt(-25)) == -25 - -25);
		assert(int(BigInt(25) - BigInt(2)) == 25 - 2);
		assert(int(BigInt(2) - BigInt(25)) == 2 - 25);
		assert(int(BigInt(25) - BigInt(-25)) == 25 - -25);
		assert(int(BigInt(-25) - BigInt(25)) == -25 - 25);
		cout << "SUB TESTS SUCCESS" << endl;
	}

	void test_mult() {
		assert(int(BigInt(25) * BigInt(25)) == 25 * 25);
		assert(int(BigInt(25) * BigInt(-25)) == 25 * -25);
		assert(int(BigInt(25) * BigInt(0)) == 25 * 0);
		assert(int(BigInt(0) * BigInt(0)) == 0 * 0);
		assert(int(BigInt(25) * BigInt(1)) == 25 * 1);
		cout << "MULT TESTS SUCCESS" << endl;
	}

	void test_div() {
		assert(int(BigInt(25) / BigInt(25)) == 25 / 25);
		assert(int(BigInt(26) / BigInt(25)) == 26 / 25);
		assert(int(BigInt(25) / BigInt(26)) == 25 / 26);
		assert(int(BigInt(-625) / BigInt(25)) == -625 / 25);
		assert(int(BigInt(0) / BigInt(25)) == 0 / 25);
		try {
			cout << BigInt(25)/BigInt(0) << endl;
		}
		catch (const char* string) {
			assert(string == "Arithmetic Error: Division By 0");
		}
		cout << "DIV TESTS SUCCESS" << endl;
	}
	
	void test_remainder() {
		assert(int(BigInt(25) % BigInt(25)) == 25 % 25);
		assert(int(BigInt(25) % BigInt(2)) == 25 % 2);
		assert(int(BigInt(25) % BigInt(5)) == 25 % 5);
		assert(int(BigInt(-25) % BigInt(25)) == -25 % 25);
		assert(int(BigInt(-27) % BigInt(25)) == 2);
		assert(int(BigInt(25) % BigInt(251)) == 25 % 251);
		cout << "REMAINDER TESTS SUCCESS" << endl;
	}

	void test_assign() {
		BigInt x(25), y(20), z(30);
		x = y;
		assert(x == y);
		x += z;
		assert(x == y + z);
		x = y;
		x -= z;
		assert(x == y - z);
		x = y;
		x *= z;
		assert(x == y * z);
		x = y;
		x /= z;
		assert(x == y / z);
		x = y;
		x %= z;
		assert(x == y % z);
		cout << "ASSIGN TESTS SUCCESS" << endl;
	}

	void test_comparison() {
		assert((BigInt(25) == BigInt(2)) == (25 == 2));
		assert((BigInt(25) == BigInt(25)) == (25 == 25));
		assert((BigInt(2) == BigInt(25)) == (2 == 25));
		assert((BigInt(25) != BigInt(2)) == (25 != 2));
		assert((BigInt(25) != BigInt(25)) == (25 != 25));
		assert((BigInt(2) != BigInt(25)) == (2 != 25));
		assert((BigInt(25) < BigInt(2)) == (25 < 2));
		assert((BigInt(25) < BigInt(25)) == (25 < 25));
		assert((BigInt(2) < BigInt(25)) == (2 < 25));
		assert((BigInt(25) > BigInt(2)) == (25 > 2));
		assert((BigInt(25) > BigInt(25)) == (25 > 25));
		assert((BigInt(2) > BigInt(25)) == (2 > 25));
		assert((BigInt(25) <= BigInt(2)) == (25 <= 2));
		assert((BigInt(25) <= BigInt(25)) == (25 <= 25));
		assert((BigInt(2) <= BigInt(25)) == (2 <= 25));
		assert((BigInt(25) >= BigInt(2)) == (25 >= 2));
		assert((BigInt(25) >= BigInt(25)) == (25 >= 25));
		assert((BigInt(2) >= BigInt(25)) == (2 >= 25));
		cout << "COMPARISON TESTS SUCCESS" << endl;
	}

	void test_unary() {
		assert(int(-BigInt(25)) == -25);
		assert(int(-BigInt(-25)) == 25);
		assert(int(+BigInt(25)) == 25);
		assert(int(+BigInt(-25)) == -25);
		assert(int(-BigInt(0)) == 0);
		assert(int(+BigInt(0)) == 0);
		cout << "UNARY TESTS SUCCESS" << endl;
	}

	void test_consructor_from_string() {
		string str1 = "-233";
		string str2 = "233";
		string str3 = "aaa";
		assert(BigInt(str1) == BigInt(-233));
		assert(BigInt(str2) == BigInt(233));
		try {
			cout << BigInt(str3) << endl;
		}
		catch (const char* string) {
			assert(string == "Invalid Argument");
		}
		cout << "CONSTRUCTOR TESTS SUCCESS" << endl;
	}

	void test_inc_and_dec() {
		BigInt x(25), y;
		y = ++x;
		assert((y == x) && (x == BigInt(26)));
		y = x++;
		assert((y == BigInt(26)) && (x == BigInt(27)));
		y = --x;
		assert((y == x) && (x == BigInt(26)));
		y = x--;
		assert((y == BigInt(26)) && (x == BigInt(25)));
		cout << "INCREMENT AND DECREMENT TESTS SUCCESS" << endl;
	}

	void test_type_change() {
		assert("-233" == string(BigInt(-233)));
		assert("233" == string(BigInt(233)));
		assert(-233 == int(BigInt(-233)));
		assert(233 == int(BigInt(233)));
		assert(0 == int(BigInt(0)));
		cout << "TYPE CHANGING TESTS SUCCESS" << endl;
	}

	void test_size() {
		BigInt x(326);
		assert(x.size_in_bytes() == 3 * sizeof(int));
		cout << "SIZE TESTS SUCCESS" << endl;
	}