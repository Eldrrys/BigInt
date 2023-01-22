#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "BigInt.h"
#include "tests.h"
using namespace std;

int main() {
	test_sum();
	test_sub();
	test_mult();
	test_div();
	test_remainder();
	test_assign();
	test_comparison();
	test_unary();
	test_consructor_from_string();
	test_inc_and_dec();
	test_type_change();
	test_size();
	return 0;
}