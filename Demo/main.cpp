#include <iostream>
#include "../Vector/Vector.h"

using namespace miit::vector;
int main()
{
	try
	{
		Vector vector_1{ 12, 33,44,55,11 };
		const Vector vector_2{ 33, 22 ,44, 55 };
		std::cout << vector_2[1];
		std::cout << vector_1 << std::endl;
	}
	catch (const std::exception& err)
	{
		std::cout << err.what();
	}

	return 0;
}