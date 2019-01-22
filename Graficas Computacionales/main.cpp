#include <iostream>
#include "DebugFunccions.h"
#include "CCanvas.h"

void CreateCanvas();

void TestCanvas(CCanvas&);

void PrintMenuOption();

int main(){

	//{
	//	CCanvas Test(3, 6, 4, 4);

	//	Test.PrintMatriceValues();
	//	Test.PrintMatriceAddresses();

	////	Test.Set(3, 5,200);

	//	//Test.PrintMatrice();

	//	//int Temp = Test.Get(3, 5);

	//	//std::cout << '{'<<Temp<<"}\n";
	//	//Test.PrintMatriceValues();
	//	TestCanvas(Test);
	//}
	CreateCanvas();


	Stop();
	return 0;
}

void CreateCanvas(){
	unsigned int X = 0;
	unsigned int Y = 0;
	unsigned int DataSize = 0;
	int DefaultValue = 0;
	short eleccion = 0;

	using std::cin;


	printf("Cuantas fillas quieres en el canvas \n");
	std::cin >> X;
	printf("Cuantas Columnas quieres en el canvas \n");
	std::cin >> Y;
	printf("Que tan grande sera el tipo de dato en Bytes \n");
	cin >> DataSize;
	printf("Ahora solo necesitamos el valor que va a tener toda la matrice \n");
	cin >> DefaultValue;
	printf("Desea Reniciar \n 0) No \n 1) Si \n");
	cin >> eleccion;
	if(eleccion == 0)
	{
		CCanvas canvas(X,Y,DataSize,DefaultValue);
		TestCanvas(canvas);
	}
	else if(eleccion == 1)
	{
		bool Reniciar = false;
		printf("Quiere reniciar \n 0) No \n 1) Si \n");
		if (Reniciar)
		{
			CreateCanvas();
		}
	}
}
 
void TestCanvas(CCanvas &canvas)
{
	//PrintMenuOption();
  	
	bool Running = true;

	int Opciones = 0;

	unsigned int X, Y, Length;
		int Value;							
		int temp=0;
	do
	{
		PrintMenuOption();
		std::cin >> Opciones;
		switch (Opciones)
		{
			case(-1):
				Running = false;
				std::cout << "Se Termino el menu \n"; 
				break;
			case(1):
				printf("Porfavor ingresa la coordenada x\n");
				std::cin >> X;
				printf("\nPorfavor ingresa la coordenada y\n");
				std::cin >> Y;
			  temp =canvas.Get(X,Y);
				printf("Aqui esta el valor [%d]\n", temp);
				break;
			case(2):
				printf("Porfavor ingresa la coordenada x\n");
				std::cin >> X;
				printf("\nPorfavor ingresa la coordenada y\n");
				std::cin >> Y;
				printf("\nPorfavor Ingrese el valor que desea settiar \n");
				std::cin >> Value;
				canvas.Set(X,Y,Value);
				break;
			case(3):
				canvas.PrintMatriceValues();
				break;
			case(4):
				canvas.PrintMatriceAddresses();
				break;
			case(5):
				printf("Porfavor ingresa la posicion en [X] donde inicia la linea\n");
				std::cin >> X;
				printf("\nPorfavor ingresa la posicion en [Y] donde se ubica la linea\n");
				std::cin >> Y;
				printf("\nPorfavor ingrese el [valor] que desea rellenar la filla indicada\n");
				std::cin >> Value;
				printf("\nPorfavor ingrese la [longitud] de la linea \n");
				std::cin >> Length;
				canvas.DrawHLine(X,Y,Length,Value);
				break;
			case(6):
				printf("Porfavor ingresa la posicion en [X] donde inicia la linea\n");
				std::cin >> X;
				printf("\nPorfavor ingresa la posicion en [Y] donde se ubica la linea\n");
				std::cin >> Y;
				printf("\nPorfavor ingrese el [valor] que desea rellenar la columna indicada\n");
				std::cin >> Value;
				printf("\nPorfavor ingrese la [longitud] de la linea \n");
				std::cin >> Length;
				canvas.DrawVLine(X,Y,Length,Value);
				break;
			default:
				std::clog << "[ERROR] Option does not exist \n\n";
				break;
		}

	} while (Running);


}

void PrintMenuOption(){
	printf("\n===> Aqui un menu para manipular canvas <=== \n");
	printf("1) Get\n");
	printf("2) Set\n");
	printf("3) PrintMatrice Values \n");
	printf("4) PrintMatrice Adreses \n");
	printf("5) Draw Horizontal line \n");
	printf("6) Draw Vertical line \n");

	printf("To leave input '-1' \n");
}