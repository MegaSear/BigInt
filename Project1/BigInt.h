#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm> 

class BigInt 
{
public:

	BigInt abs() const;
	bool GetSign() const;
	std::vector<char>GetData() const;
	void SetData(std::vector<char> A);
	void SetSign(bool A);
	BigInt();
	BigInt(int);
	BigInt(std::string);
	BigInt(const BigInt&);
	~BigInt();

	BigInt& operator=(const BigInt&);

	BigInt operator~() const;

	BigInt& operator++();
	const BigInt operator++(int) const;
	BigInt& operator--();
	const BigInt operator--(int) const;

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;
	BigInt operator-() const;

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator long long int() const;
	operator std::string() const;

	size_t size() const;

private:
	std::vector<char> data;
	bool pos;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& out, const BigInt& A);
std::istream& operator>>(std::istream& in, BigInt& A);
