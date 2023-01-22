#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

class BigInt {
	int* digits;
	bool is_negative;
	size_t size;

public:
	BigInt();
	BigInt(int value);
	BigInt(string& value);
	BigInt(const BigInt&);
	~BigInt();


	BigInt operator +(const BigInt&);
	BigInt operator -(const BigInt&);
	BigInt operator *(const BigInt&);
	BigInt operator /(const BigInt&);
	BigInt operator %(const BigInt&);

	BigInt& operator =(const BigInt&);
	BigInt operator +=(const BigInt&);
	BigInt operator -=(const BigInt&);
	BigInt operator *=(const BigInt&);
	BigInt operator /=(const BigInt&);
	BigInt operator %=(const BigInt&);

	BigInt operator++();
	BigInt operator++(int);
	BigInt operator--();
	BigInt operator--(int);

	BigInt operator+() const;
	BigInt operator-() const;

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	friend std::ostream& operator<< (std::ostream&, BigInt const&);
	operator int() const;
	operator std::string() const;

	BigInt abs(const BigInt&);
	void shift_right(size_t);
	void push(int);
	void ignore_leading_zeros();
	size_t size_in_bytes() const;
};