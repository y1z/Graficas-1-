#pragma once
#include <iostream>

void * operator new(size_t size)
{
	std::cout << "Alocando ["<<size << "] Bytes" << std::endl;
	return malloc(size);
}

void Stop(){
	std::cin.ignore();
	std::cin.get();
}
