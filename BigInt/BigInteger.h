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
			std::bitset<size + 1> auxiliary;
			std::bitset<size + 1> sum;
			
			--tmp_sz;

			for (; tmp_sz >= 0; tmp_sz--)
			{
				if (s[tmp_sz] != 0)
					is_zero = false;

				if (isdigit(s[tmp_sz]))
				{
					auxiliary = (s[tmp_sz] - 48) * pow(exp, power);
					for (int i = 0; i < size + 1; i++)
					{
						std::bitset<size + 1> tmp = sum;
						
						sum[i] = tmp[i] ^ auxiliary[i] ^ carry;
						carry = ((tmp[i] & auxiliary[i]) | (tmp[i] & carry)) | (auxiliary[i] & carry);	// full adder
					}
					++power;
				}
				else
				{
					std::cout << "Exception: invalid string.\n";
					is_wrong = true;
				}
			}
			if (sum[sum.size() - 1] == 1)
			{
				std::cout << "Bit overflow in the constructor.\n";
				is_wrong = true;
			}
			else if (str_sz != 0 && sum.to_ulong() == 0 && !is_zero)	/* For cases when '1' is only the MSB (e.g. 256, 512...) */
			{
				std::cout << "Bit overflow in the constructor (2).\n";
				is_wrong = true;
			}
			if (!is_wrong)
			for (int i = 0; i < size + 1; i++)
				number[i] = sum[i];
		}
		
	}

	void print()
	{
		if (!is_wrong)
		{
			for (int i = 0; i < size + 1; ++i)
			{
				std::cout << number[i];
			}
			std::cout << '\n';
		}
		else
			std::cout << "Something is wrong with the class instance.\n";
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
				if (this->number[size - 1] == 1 && other.number[size - 1] == 1)
				{
					std::cout << "Overflow in the constructor.\n";
					break;
				}
				sum[i] = this->number[i] ^ other.number[i] ^ carry;
				carry = ((this->number[i] & other.number[i]) | (this->number[i] & carry)) | (other.number[i] & carry);	// full adder
			}
			this->number = sum;
		}
		return *this;

	}

	~BigInteger()
	{

	}

private: 
	std::bitset<size + 1> number; 
	int str_sz;
	int m_s_bit;
	bool is_too_big = false;
	bool is_wrong = false;
	bool is_zero;
};





