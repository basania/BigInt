#pragma once

#include <array>
#include <iostream>
#include <bitset>

template<int size> 
class BigInteger 
{
public:
	BigInteger() = delete;


	explicit BigInteger(const char* s)
		: str_sz(strlen(s))
	{
		if (str_sz > size)
		{
			std::cout << "Size overflow\n";
			is_too_big = true;
		}

		if (!is_too_big)
		{
			int tmp_sz = str_sz;
			int exp = 10;
			int power = 0;
			int carry = 0;
			std::bitset<size> auxiliary;
			std::bitset<size> sum;
			
			--tmp_sz;
			for (; tmp_sz >= 0; tmp_sz--)
			{
				if (isdigit(s[tmp_sz]))
				{
					auxiliary = (s[tmp_sz] - 48) * pow(exp, power);
					for (int i = 0; i < size - 1; i++)
					{
						std::bitset<size> tmp = sum;

						sum[i] = tmp[i] ^ auxiliary[i] ^ carry;
						carry = ((tmp[i] & auxiliary[i]) | (tmp[i] & carry)) | (auxiliary[i] & carry);	// full adder
					}
					++power;
				}
				else
				{
					std::cout << "Exception: invalid string.\n";
				}
			}
			number = sum;
		}
		
	}

	void print()
	{
		bool is_zero = true;
		for (int i = 0; i < size; ++i)
		{
		/*	if (number[i] != 0)
				is_zero = false;
			if (!is_zero)
				*/
			std::cout << number[i];
		}
		std::cout << '\n';
	}

	BigInteger& operator+ (const BigInteger& other)
	{
		int carry = 0;
		if (other.str_sz > this->str_sz)
			std::cout << "Addition will cause an overflow\n";
		else if (other.str_sz == this->str_sz && this->number[size - 1] == 1 && other.number[size - 1] == 1)
			std::cout << "Addition will cause an overflow\n";
		else
		{
			std::bitset<size> sum;
			for (int i = 0; i < size - 1; ++i)
			{
				sum[i] = this->number[i] ^ other.number[i];
				if (this->number[i] == 1 && other.number[i] == 1)
				{
					sum[i + 1] = 1;
				}
			}
			this->number = sum;
		}
		return *this;

	}

	~BigInteger()
	{

	}

private: 
	std::bitset<size> number; 
	int str_sz;
	int m_s_bit;
	bool is_too_big = false;
	bool is_negative;
};







/*template<int size>
class BigInteger
{
public:
	BigInteger() = delete;


	explicit BigInteger(const char* s)
		: str_sz(strlen(s))
	{
		if (str_sz > size)
		{
			std::cout << "Size overflow\n";
			is_too_big = true;
		}

		if (!is_too_big)
		{
			number.fill(0);
			int temp = str_sz;
			--temp;

			for (int i = size - 1; temp >= 0; --i, --temp)
			{

				if (!isdigit(s[temp]))
				{
					std::cout << "Number is invalid\n";
					break;
				}
				number[i] = s[temp] - 48;

				if (number[i] != 0)
					m_s_bit = number[i];
			}
		}

	}

	void print()
	{
		bool is_zero = true;
		for (int i = 0; i < size; ++i)
		{
			if (number[i] != 0)
				is_zero = false;
			if (!is_zero)
				std::cout << number[i];
		}
		std::cout << '\n';
	}

	BigInteger& operator+ (const BigInteger& other)
	{
		if (other.str_sz > this->str_sz)
			std::cout << "Addition will cause an overflow\n";
		else if (other.str_sz == this->str_sz && this->m_s_bit + m_s_bit > 9)
			std::cout << "Addition will cause an overflow\n";
		else
		{
			int temp = size - 1;
			for (int i = temp; i >= 0; --temp, --i)
			{
				this->number[i] += other.number[i];
			}
		}
		return *this;

	}

	~BigInteger()
	{

	}

private:
	std::array<int, size> number;
	int str_sz;
	int m_s_bit;
	bool is_too_big = false;
};
*/