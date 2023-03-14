#include "BigInt.h"

std::vector<char> BigInt::GetData() const {
	return this->data;
}

bool BigInt::GetSign() const
{
	return this->pos;
};

void BigInt::SetData(std::vector<char> A)
{
	this->data = A;
}

void BigInt::SetSign(bool A)
{
	this->pos = A;
}

BigInt::BigInt()
{
	this->pos = true;
};

BigInt::BigInt(int b)
{
	long long a = long long(b);
	if (a == 0)
	{
		this->data.push_back((a % 10) + '0');
		this->pos = true;
		return;
	}
	this->pos = (a >= 0);
	a = std::abs(a);

	while (double(a) / 10)
	{
		this->data.push_back((a % 10) + '0');
		a /= 10;
	}
};

BigInt::BigInt(std::string str)
{
	this->pos = (str[0] != '-');

	reverse(str.begin(), str.end());

	if (!pos)
	{
		str.pop_back();
	}

	for (auto x : str)
	{
		if (x < '0' or x > '9') throw std::invalid_argument("String contains extra characters.\n");
	}

	for (auto x : str)
	{
		this->data.push_back(x);
	}


}; // бросать исключение std::invalid_argument при ошибке

BigInt::BigInt(const BigInt& a)
{
	this->data = a.data;
	this->pos = a.pos;
};

BigInt::~BigInt()
{
	this->data.clear();
};

BigInt BigInt::abs() const
{
	BigInt A;
	A.data = this->data;
	return A;
};

std::vector<char> bin(const BigInt& A)
{
	std::vector<char> binA;
	BigInt result= A.abs();
	bool flag = A < BigInt(0);
	while (result != BigInt(0))
	{
		int a = int(result % (BigInt(2)));
		char z = char(a != flag);
		binA.push_back(char(z));
		result /= (BigInt(2));
	}
	if (!flag)
	{
		binA.push_back(0);
		return binA;
	}

	for (int i = 0; i < binA.size(); i++)
	{
		if (binA[i])
			binA[i] = 0;
		else
		{
			binA[i] = 1;
			break;
		}
	}
	binA.push_back(char(1));
	return binA;
}

BigInt dec(std::vector<char>& A)
{
	BigInt bigint(0);

	if (A[A.size() - 1])
	{
		for (int i = 0; i < A.size()-1; i++)
		{
			if (A[i])
			{
				A[i] = 0;
				break;
			}
			else
			{
				A[i] = 1;
			}
		}
		for (int i = 0; i < A.size()-1; i++)
		{
			A[i] = !A[i];
		}
	}
	for (int i = 0; i < A.size()-1; i++)
	{
		if (A[i])
		{
			bigint += BigInt(pow(2, i));
		}
	}
	bigint.SetSign(!A[A.size() - 1]);
	return bigint;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (*this != other)
	{
		this->data.clear();
		this->data = other.data;
		this->pos = other.pos;
	}
	return *this;
};

BigInt BigInt::operator~() const
{
	std::vector<char> thisBin(bin(*this));
	thisBin.push_back(thisBin[thisBin.size() - 1]);
	for (size_t i = 0; i < thisBin.size(); i++)
		thisBin[i] = !thisBin[i];
	BigInt result = dec(thisBin);
	return result;
};

BigInt& BigInt::operator++()
{
	*this = *this + BigInt(1);
	return *this;
};

const BigInt BigInt::operator++(int) const
{
	BigInt A(*this);
	++(const_cast<BigInt&>(*this));
	return A;
};

BigInt& BigInt::operator--()
{
	this->pos = !this->pos;
	++(*this);
	this->pos = !this->pos;
	return *this;
};

const BigInt BigInt::operator--(int) const
{
	BigInt A = *this;
	--(const_cast<BigInt&>(*this));
	return A;
};

BigInt& BigInt::operator+=(const BigInt& other)
{
	int d = 0;
	int d1 = 0;
	if (this->pos == other.pos)
	{
		for (int i = 0; (i < this->data.size()) or (i < other.data.size()); i++)
		{
			int m, n;
			bool u1 = i < this->data.size();
			bool u2 = i < other.data.size();
			(u1) ? (m = this->data[i] - '0') : (m = 0);
			(u2) ? (n = other.data[i] - '0') : (n = 0);
			int z = m * u1 + n * u2 + d;
			if (u1)
				this->data[i] = (z % 10) + '0';
			else
				this->data.push_back((z % 10) + '0');
			d = z / 10;
		}
		if (d)
		{
			this->data.push_back('1');
		}
	}
	else
	{
		BigInt maxBigInt;
		BigInt minBigInt;
		if (this->abs() >= other.abs())
		{
			maxBigInt = *this;
			minBigInt = other;
		}
		else
		{
			minBigInt = *this;
			maxBigInt = other;
		}
		for (int i = 0; i < maxBigInt.data.size(); i++)
		{
			int m, n;
			m = maxBigInt.data[i] - '0';
			bool u2 = i < minBigInt.data.size();
			(u2) ? (n = minBigInt.data[i] - '0') : (n = 0);
			d1 = (m - u2 * n - d < 0);
			maxBigInt.data[i] = std::abs(10 * d1 + m - u2 * n - d) + '0';
			d = d1;
		}
		if (maxBigInt.data[maxBigInt.data.size() - 1] <= '0')
		{
			maxBigInt.data.pop_back();
		}
		for (int i = maxBigInt.data.size() - 1; i >= 1; i--)
		{
			if (maxBigInt.data[i] <= '0')
			{
				maxBigInt.data.pop_back();
			}
			else
			{
				break;
			}
		}

		*this = maxBigInt;
	}
	return *this;
};

BigInt& BigInt::operator-=(const BigInt& other)
{
	return *this += -other;
};

BigInt& BigInt::operator*=(const BigInt& other)
{
	if (other == BigInt("0") or (*this == BigInt("0")))
	{
		*this = BigInt("0");
		return *this;
	}
	BigInt res(int(0));
	BigInt maxBigInt;
	BigInt minBigInt;
	if (this->abs() >= other.abs())
	{
		maxBigInt = *this;
		minBigInt = other;
	}
	else
	{
		minBigInt = *this;
		maxBigInt = other;
	}

	for (int j = 0; j < minBigInt.data.size(); j++)
	{
		int d = 0;
		if (!minBigInt.data[j])
		{
			continue;
		}
		BigInt str;

		for (int i = 0; i < maxBigInt.data.size(); i++)
		{
			int m, n;
			m = maxBigInt.data[i] - '0';
			n = minBigInt.data[j] - '0';
			int z = m * n + d;
			str.data.push_back((z % 10) + '0');
			d = z / 10;
		}
		if (d)
		{
			str.data.push_back(d + '0');
		}
		reverse(str.data.begin(), str.data.end());
		for (int i = 0; i < j; i++)
		{
			str.data.push_back('0');
		}
		reverse(str.data.begin(), str.data.end());
		res += str;

	}
	*this = res;
	this->pos = (maxBigInt.GetSign() == minBigInt.GetSign());
	return *this;
};

BigInt& BigInt::operator/=(const BigInt& other)
{
	if (other == BigInt("0"))
	{
		throw std::overflow_error("Divide by zero");
	}
	if (this->abs() < other.abs())
	{
		*this = BigInt(0);
		return *this;
	}
	reverse(this->data.begin(), this->data.end());
	BigInt cnt(0);
	BigInt A;
	cnt.data.pop_back();
	for (int i = 0; i < this->data.size(); i++)
	{
		reverse(cnt.data.begin(), cnt.data.end());
		cnt.data.push_back(this->data[i]);
		reverse(cnt.data.begin(), cnt.data.end());
		if (cnt == BigInt(0))
		{
			A.data.push_back(0 + '0');
			cnt.data.clear();
			continue;
		}
		if (cnt >= (other.abs()))
		{
			for (int j = 9; j >= 1; j--)
			{
				BigInt B = (other.abs()) * BigInt(j);
				if (cnt >= B)
				{
					A.data.push_back(j + '0');
					cnt = (cnt - B);
					if (cnt == BigInt(0))
					{
						cnt.data.pop_back();
					}
				}
			}
		}
		else
		{
			A.data.push_back(0 + '0');
		}
	}
	reverse(A.data.begin(), A.data.end());
	if ((cnt.data.size() != 0) and ((!this->pos) and (other.pos)))
	{
		A -= BigInt(-1);
	}
	this->pos = (this->GetSign() == other.GetSign());
	this->data = A.data;
	return *this;
};

BigInt& BigInt::operator^=(const BigInt& other)
{
	std::vector<char> this_bin(bin(*this));
	std::vector<char> other_bin(bin(other));
	std::vector<char>* vec_min = (this_bin.size() < other_bin.size()) ? (&this_bin) : (&other_bin);
	std::vector<char>* vec_max = (this_bin.size() < other_bin.size()) ? (&other_bin) : (&this_bin);
	for (int i = 0; vec_max->size() != vec_min->size(); i++)
	{
		vec_min->push_back((*vec_min)[vec_min->size() - 1]);
	}
	for (int i = 0; i < vec_max->size(); i++)
	{
		this_bin[i] |= other_bin[i];
	}
	*this = dec(this_bin);
	return *this;
};

BigInt& BigInt::operator%=(const BigInt& other)
{
	BigInt A = *this;
	A /= other;
	*this -= (A * other);
	return *this;
};

BigInt& BigInt::operator&=(const BigInt& other)
{
	std::vector<char> this_bin(bin(*this));
	std::vector<char> other_bin(bin(other));
	std::vector<char>* vec_min = (this_bin.size() < other_bin.size()) ? (&this_bin) : (&other_bin);
	std::vector<char>* vec_max = (this_bin.size() < other_bin.size()) ? (&other_bin) : (&this_bin);
	for (int i = 0; vec_max->size() != vec_min->size(); i++)
	{
		vec_min->push_back((*vec_min)[vec_min->size() - 1]);
	}
	for (int i = 0; i < vec_max->size(); i++)
	{
		this_bin[i] &= other_bin[i];
	}
	*this = dec(this_bin);
	return *this;
};

BigInt& BigInt::operator|=(const BigInt& other)
{
	std::vector<char> this_bin(bin(*this));
	std::vector<char> other_bin(bin(other));
	std::vector<char>* vec_min = (this_bin.size() < other_bin.size()) ? (&this_bin) : (&other_bin);
	std::vector<char>* vec_max = (this_bin.size() < other_bin.size()) ? (&other_bin) : (&this_bin);
	for (int i = 0; vec_max->size() != vec_min->size(); i++)
	{
		vec_min->push_back((*vec_min)[vec_min->size() - 1]);
	}
	for (int i = 0; i < vec_max->size(); i++)
	{
		this_bin[i] |= other_bin[i];
	}
	*this = dec(this_bin);
	return *this;
};

BigInt BigInt::operator+() const
{
	BigInt A = *this;
	A.pos = this->pos;
	return A;
};

BigInt BigInt::operator-() const
{
	BigInt A = *this;
	A.pos = !this->pos;
	return A;
};

bool BigInt::operator==(const BigInt& other) const
{
	return (this->pos == other.pos) and (this->data == other.data);
};

bool BigInt::operator!=(const BigInt& other) const
{
	return (this->data != other.data) or (this->pos != other.pos);
};

bool BigInt::operator<(const BigInt& other) const
{
	if (this->pos != other.pos)
	{
		return other.pos;
	}
	if (this->data.size() != other.data.size())
	{
		return !this->pos == (this->data.size() > other.data.size());
	}
	for (int i = this->data.size() - 1; i >= 0; i--)
	{
		if (this->data[i] != other.data[i])
			return this->pos == (this->data[i] < other.data[i]);
	}
	return false;
};

bool BigInt::operator>(const BigInt& other) const
{
	return other < *this;
};

bool BigInt::operator<=(const BigInt& other) const
{
	return (*this < other) or (*this == other);
};

bool BigInt::operator>=(const BigInt& other) const
{
	return (*this > other) or (*this == other);
};

BigInt::operator int() const
{
	if ((*this > BigInt(INT_MAX)) or (*this < BigInt(INT_MIN)))
	{
		throw std::out_of_range("The number " + std::string(*this) + " is out of range int.\n");
	}

	int a = 0;

	for (int i = 0; i < this->data.size(); i++)
	{
		a += ((this->data[i] - '0')) * pow(10, i);
	}
	return a * (pow((-1), (!this->pos)));
};

BigInt::operator std::string() const
{
	std::string str;
	for (auto x : this->data)
	{
		str.push_back(x);
	}
	if (not this->pos)
	{
		str.push_back('-');
	}

	reverse(str.begin(), str.end());
	return str;
};

size_t BigInt::size() const
{
	return this->data.size() + !this->pos;
};

BigInt operator+(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a += B;
};

BigInt operator-(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a -= B;
};

BigInt operator*(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a *= B;
};

BigInt operator/(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a /= B;
};

BigInt operator^(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a /= B;
};

BigInt operator%(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a %= B;
};

BigInt operator&(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a &= B;
};

BigInt operator|(const BigInt& A, const BigInt& B)
{
	BigInt a = A;
	return a |= B;
};

std::ostream& operator<<(std::ostream& out, const BigInt& A)
{
	if (!A.GetSign())
	{
		out << "-";
	}

	for (int i = A.GetData().size() - 1; i >= 0; i--)
	{
		out << +((A.GetData())[i] - '0');
	}

	return out;
}

std::istream& operator>>(std::istream& in, BigInt& A)
{
	std::string str;
	while (true)
	{
		in >> str;
		try
		{
			A = BigInt(str);
			break;
		}
		catch (std::invalid_argument)
		{
			std::cerr << "Error: String contains extra characters" << std::endl << "Try again: ";
		}
	}

	return in;
}
