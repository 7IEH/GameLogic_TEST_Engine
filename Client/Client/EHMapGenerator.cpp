#include "pch.h"
#include "EHMapGenerator.h"

int MapGenerator::i_mProgress = 0;
extern HANDLE test;

void MapGenerator::Start()
{
	::WaitForSingleObject(test, INFINITE);
	Divide();
	GenerateRoom();
	GenerateRoad();
}

bool Find_prime_num(int n)
{
	int count = 0;
	for (int i = 2;i < n;i++)
	{
		if (!(n % i))
			return false;
	}

	return true;
}

void MapGenerator::Divide()
{
	for (int i = 0;i < 900000;i++)
	{
		if(Find_prime_num(i))
			i_mProgress++;
	}
}

void MapGenerator::GenerateRoom()
{
	for (int i = 0;i < 900000;i++)
	{
		if (Find_prime_num(i))
			i_mProgress++;
	}
}

void MapGenerator::GenerateRoad()
{
	for (int i = 0;i < 900000;i++)
	{
		if (Find_prime_num(i))
			i_mProgress++;
	}
}
