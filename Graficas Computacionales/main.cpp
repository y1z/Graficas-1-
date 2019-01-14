#include <iostream>
#include "DebugFunccions.h"
#include "CCanvas.h"


void TestCanvas(CCanvas&);

int main(){


	{
		CCanvas Test(3, 6, 4, 4);

		Test.PrintMatriceValues();
		Test.PrintMatriceAddresses();

		Test.Set(3, 5,200);

		//Test.PrintMatrice();

		int Temp = Test.Get(3, 5);

		std::cout << '{'<<Temp<<"}\n";
		Test.PrintMatriceValues();
	
	}

	Stop();
	return 0;
}

// TODO : Agregar un menu para manipular el objeto CCanvas 
void TestCanvas(CCanvas &canvas)
{
	printf("");


}