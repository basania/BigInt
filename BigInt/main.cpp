// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigInteger.h"

int main()
{
	BigInteger<8> q("250");
	
	BigInteger<8> q1("5");

	//q = q + q1;

	q.print();
    return 0;
}

