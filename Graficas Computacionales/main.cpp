#include <iostream>
#include "DebugFunccions.h"
#include "CCanvas.h"

//void CreateCanvas();

void TestCanvas(CCanvas&);

void PrintMenuOption();
/*
\fn Create a canvas through asking a series of 
question to the user .
*/

template <typename T>
void CreateCanvas(T DefualtValue);

void InitCanvas();

int main(){
	/*
	{
		CCanvas Test(3, 6, 3, 4);
		CCanvas Test2(3, 6, 4, 12);

		Test2.CopyTo(Test);

		Test.PrintMatriceValues();
		Test.PrintMatriceAddresses();

	//	Test.Set(3, 5,200);

		//Test.PrintMatrice();

		//int Temp = Test.Get(3, 5);

		//std::cout << '{'<<Temp<<"}\n";
		//Test.PrintMatriceValues();
		//TestCanvas(Test);

	}*/
	InitCanvas();

	Stop();
	return 0;
}


void TestCanvas(CCanvas &canvas)
{
	bool Running = true;

	int Opciones = 0;

	unsigned int X, Y, Length;
		float Value;							
		float temp = 0.0f;
		float yF1 = 0.0f;
		float xF1 = 0.0f;
		float xF2 = 0.0f;
		float yF2 = 0.0f;
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
				// llama la funcion Get 
				printf("Porfavor ingresa la coordenada flotantes en x\n");
				std::cin >> xF1;
				printf("\nPorfavor ingresa la coordenada flotantes en y\n");
				std::cin >> yF1;
			  temp =canvas.Get(xF1,yF1);
				std::cout << "Qui esta el valor [" << temp << "]\n";
				break;
			case(2):
				// llama la funcion Set 
				printf("Porfavor ingresa la coordenada x [rango 0...1]\n");
				std::cin >> xF1;
				printf("\nPorfavor ingresa la coordenada y [rango 0...1]\n");
				std::cin >> yF1;
				printf("\nPorfavor Ingrese el valor que desea settiar \n");
				std::cin >> Value;
				canvas.Set(xF1,yF1,Value);
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
			case(7):
				printf("Porfavor ingresa la primera Coordenada [U] \n");
				std::cin >> xF1;
				printf("Porfavor ingresa la primera Coordenada [V] \n");
				std::cin >> yF1;
				printf("Porfavor ingresa la Segunda Coordenada [U] \n");
				std::cin >> xF2;
				printf("Porfavor ingresa la Segunda Coordenada [V] \n");
				std::cin >> yF2;
				printf("Profavor ingresa el [Valor] \n");
				std::cin >> Value;
				canvas.DrawDiagonal(xF1, yF1, xF2, yF2, Value);
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
	printf("7) Draw diagalnal line \n");

	printf("To leave input '-1' \n");
}


template<typename T>
void CreateCanvas(T DefaultValue = 0){
	unsigned int X = 0;
	unsigned int Y = 0;
	unsigned int DataSize = 0;
	short eleccion = 0;
	bool isFloat = false;

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
		CreateCanvas<T>();
	}
}

void InitCanvas(){
	short Opciones = 0;
	std::cout << "Quieres un canvas conpuesto de Enteros o Flotantes \n"
		<< "1) Flotantes \n 2) Enteros \n" << std::endl;
	std::cin >> Opciones;
	if (Opciones == 1)
		CreateCanvas<float>();
	else if (Opciones == 2)
	{
		CreateCanvas<int>();
	}
	
}