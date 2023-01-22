#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "BigInt.h"
#include <cassert>
using namespace std;

BigInt::BigInt() {
	this->is_negative = false;
	this->digits = new int[1];
	this->digits[0] = 0;
	this->size = 1;
}

BigInt::BigInt(int value) {
	this->is_negative = false;
	if (value < 0) {
		this->is_negative = true;
		value *= -1;
	}
	if (value == 0) {
		this->size = 1;
		this->digits = new int[size];
		this->digits[0] = 0;
	}
	else {
		int size = 0;
		int temp = value;
		while (temp > 0) {
			temp /= 10;
			size++;
		}

		this->digits = new int[size];
		this->size = size;

		for (int i = size - 1; i >= 0; i--) {
			int a = value % 10;
			this->digits[i] = a;
			value /= 10;
		}
	}
}

BigInt::BigInt(string& value) {
	bool value_is_negative = value[0] == '-' ? true : false;
	for (int i = 0; i < value.length() - 1; i++) {
		if (!(value[i] < '9' && value[i] > '0')) {
			if (value[0] == '-' && i == 0) continue;
			throw("Invalid Argument");
		} 
	}
	this->is_negative = value_is_negative;
	size_t size = value_is_negative ? value.length() - 1 : value.length();
	this->digits = new int[size];
	this->size = size;

	if (value_is_negative) {
		for (int i = 0; i < size; i++) {
			this->digits[i] = (int)value[i + 1] - '0';
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			this->digits[i] = (int)value[i] - '0';
		}
	}
}

BigInt::BigInt(const BigInt& value) {
	this->is_negative = value.is_negative;
	this->digits = new int[value.size];
	this->size = value.size;

	for (int i = 0; i < value.size; i++) {
		this->digits[i] = value.digits[i];
	}
}

BigInt::~BigInt() {
	if (this->digits != nullptr) {
		delete[] digits;
	}
};

BigInt& BigInt::operator =(const BigInt& value) {
	this->is_negative = value.is_negative;
	this->digits = new int[value.size];
	this->size = value.size;

	for (int i = 0; i < value.size; i++) {
		this->digits[i] = value.digits[i];
	}

	return *this;
}

BigInt BigInt::operator +(const BigInt& value) {
	if (this->is_negative) {
		if (value.is_negative) return -(abs(*this) + abs(value));
		else return value - -*this;
	}
	else if (value.is_negative) return *this - (-value);
	BigInt result;
	if (*this > value) {
		result = *this;
	}
	else result = value;
	
	size_t min_size = min(this->size, value.size);
	int tens = 0;

	for (size_t i = 0; i < min_size; i++) {
		int temp = this->digits[this->size - i - 1] + value.digits[value.size - i - 1] + tens;
		tens = temp / 10;
		result.digits[result.size - i - 1] = temp % 10;
	}

	if (tens == 0) {
		return result;
	}

	delete[] this->digits;
	this->is_negative = result.is_negative;
	this->digits = new int[result.size + 1];
	this->size = result.size + 1;

	for (int i = 0; i < this->size; i++) {
		this->digits[i + 1] = result.digits[i];
	}
	this->digits[0] = tens;

	return *this;
}

BigInt BigInt::operator +=(const BigInt& value) {
	*this = (*this + value);
	return *this;
}

BigInt BigInt::operator -(const BigInt& value) {
	if (value.is_negative) return *this + (-value);
	else if (this->is_negative) return -(-*this + value);
	else if (*this < value) return -(value - *this);

	BigInt temp = value;
	temp.shift_right(this->size - value.size);

	for (size_t i = this->size - 1; i > 0; i--) {
		if (this->digits[i] >= temp.digits[i]) {
			this->digits[i] -= temp.digits[i];
		}
		else {
			this->digits[i - 1]--;
			this->digits[i] = 10 + this->digits[i] - temp.digits[i];
		}
	}

	this->digits[0] -= temp.digits[0];
	this->ignore_leading_zeros();

	return *this;
}

BigInt BigInt::operator -=(const BigInt& value) {
	*this = (*this - value);
	return *this;
}

BigInt BigInt::operator *(const BigInt& value) {
	BigInt result;
	for (size_t i = 0; i < this->size; i++) {
		for (size_t j = 0; j < value.size; j++) {
			int val = this->digits[this->size - i - 1] * value.digits[value.size - j - 1] * pow(10, i) * pow(10, j);
			BigInt temp(val);
			result += temp;
		}
	}
	result.is_negative = this->is_negative != value.is_negative;
	return result;
}

BigInt BigInt::operator *=(const BigInt& value) {
	*this = (*this * value);
	return *this;
}

BigInt BigInt::operator/(const BigInt& value) {
	BigInt buffer;
	BigInt result;
	BigInt abs_value = abs(value);

	if (value == BigInt(0)) throw("Arithmetic Error: Division By 0");

	for (size_t i = 0; i < this->size; i++) {
		buffer.push(this->digits[i]);
		buffer.ignore_leading_zeros();

		if (buffer < abs_value) {
			continue;
		}

		int count = 0;

		while (buffer >= abs_value) {
			buffer = buffer - abs_value;
			count++;
		}

		result.push(count);
	}

	result.ignore_leading_zeros();
	result.is_negative = false;

	if (this->is_negative != value.is_negative && result.digits[0] != 0)
		result.is_negative = true;

	return result;
}

BigInt BigInt::operator /=(const BigInt& value) {
	*this = (*this / value);
	return *this;
}

BigInt BigInt::operator %(const BigInt& value) {
	BigInt result = (*this / value) * value;
	result = abs(*this) - abs(result);

	return result;
}

BigInt BigInt::operator %=(const BigInt& value) {
	*this = (*this % value);
	return *this;
}

BigInt BigInt::operator++() {
	return (*this += BigInt(1));
}

BigInt BigInt::operator ++(int) {
	*this += BigInt(1);

	return BigInt(*this) - BigInt(1);
}

BigInt BigInt::operator --() {
	return *this -= BigInt(1);
}

BigInt BigInt::operator --(int) {
	*this -= BigInt(1);
	return BigInt(*this) + BigInt(1);
}

BigInt BigInt::operator +() const {
	return BigInt(*this);
}

BigInt BigInt::operator -() const {
	BigInt copy(*this);
	if(*this != BigInt(0)) copy.is_negative = !copy.is_negative;
	return copy;
}

bool BigInt::operator==(const BigInt& value) const {
	if (this->is_negative != value.is_negative) return false;
	if (this->size != value.size) return false;

	for (int i = 0; i < value.size; i++) {
		if (this->digits[i] != value.digits[i]) return false;
	}

	return true;
}

bool BigInt::operator!=(const BigInt& value) const {
	return !(*this == value);
}

bool BigInt::operator<(const BigInt& value) const {
	if (this->is_negative && !value.is_negative) return true;
	if (!this->is_negative && value.is_negative) return false;
	if (this->is_negative && value.is_negative) return (-*this > -value);
	if (this->size > value.size) return false;
	if (this->size < value.size) return true;

	for (int i = 0; i < value.size; i++) {
		if (this->digits[i] > value.digits[i]) return false;
		if (this->digits[i] < value.digits[i]) return true;
	}

	return false;
}

bool BigInt::operator>(const BigInt& value) const {
	if (!this->is_negative && value.is_negative) return true;
	if (this->is_negative && !value.is_negative) return false;
	if (this->is_negative && value.is_negative) return (-*this < -value);
	if (this->size < value.size) return false;
	if (this->size > value.size) return true;

	for (int i = 0; i < value.size; i++) {
		if (this->digits[i] < value.digits[i]) return false;
		if (this->digits[i] > value.digits[i]) return true;
	}

	return false;
}

bool BigInt::operator<=(const BigInt& value) const {
	return !(*this > value);
}

bool BigInt::operator>=(const BigInt& value) const {
	return !(*this < value);
}

BigInt::operator int() const {
	int result = 0;

	for (int i = 0; i < this->size; i++) {
		result *= 10;
		result += this->digits[i];
	}
	if (this->is_negative) result *= -1;
	return result;
}

BigInt::operator std::string() const {
	int minus = this->is_negative ? 1 : 0;
	char* temp = new char[this->size + minus + 1];
	if (this->is_negative) temp[0] = '-';
	for (int i = 0; i < this->size + minus; i++) {
		temp[i + minus] = this->digits[i] + '0';
	}
	temp[this->size + minus] = '\0';
	std::string str = temp;
	delete[] temp;
	return str;
}

std::ostream& operator<< (std::ostream& out, BigInt const& value) {
	if (value.is_negative) {
		out << '-';
	}
	for (int i = 0; i < value.size; i++) {
		out << value.digits[i];
	}
	return out;
}

BigInt BigInt::abs(const BigInt& value) {
	return value.is_negative ? -value : value;
}

void BigInt::shift_right(size_t value) {
	if (this->size == 0) {
		this->size = 1;
		this->digits = new int[1];
		this->digits[0] = 0;
		return;
	}

	if (value <= 0) {
		return;
	}

	BigInt temp;
	temp = *this;

	this->size = temp.size + value;
	this->digits = new int[temp.size + value];

	for (size_t i = 0; i < value; i++) this->digits[i] = 0;
	for (size_t i = 0; i < temp.size; i++) this->digits[i + value] = temp.digits[i];
}

void BigInt::push(int value) {
	BigInt temp;
	temp = *this;

	this->size = temp.size + 1;
	this->digits = new int[temp.size + 1];

	for (size_t i = 0; i < this->size; i++) this->digits[i] = temp.digits[i];
	this->digits[temp.size] = value;
}

void BigInt::ignore_leading_zeros() {
	int count = 0;

	while (this->digits[count] == 0) {
		count++;
	}

	if (count == this->size) {
		this->size = 1;
		this->digits[0] = 0;
		return;
	}
	
	BigInt temp = *this;
	delete[] this->digits;
	this->size = this->size - count;
	this->digits = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		this->digits[i] = temp.digits[i + count];
	}
}

size_t BigInt::size_in_bytes() const {
	return this->size * sizeof(int);
}