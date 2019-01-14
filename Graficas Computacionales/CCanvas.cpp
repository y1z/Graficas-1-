#include "CCanvas.h"
// constructor 
CCanvas::CCanvas(unsigned int X, unsigned int Y,unsigned int dataSize, int DefaultValue)
{

	if (isDataSizeSupported(dataSize))
	{
		Rows = X;
		Columns = Y;
		Pitch = dataSize * Rows;

		sizeDataType = dataSize;
		sizeBuffer = X * Y;

		// create our buffer 
		ptr_Buffer = (unsigned char *) malloc(sizeBuffer * dataSize);
		// to reset buffer 
		ptr_Beginning = ptr_Buffer;
		// to Iterate through the buffer 
		ptr_Ending = ptr_Buffer + (sizeDataType * sizeBuffer);

		// assigns the value to the matrice of the buffer
		while(ptr_Buffer < ptr_Ending)
		{
			*ptr_Buffer = DefaultValue;
			ptr_Buffer += sizeDataType;
		}
		ResetBufferPointerBeginning();
	}
}
// destructor 
CCanvas::~CCanvas(){

	if (ptr_Buffer != nullptr)
	{
		free(ptr_Buffer);
		ptr_Buffer = nullptr;
	}
	ptr_Beginning = nullptr;
	ptr_Ending = nullptr;
}



int CCanvas::Get(unsigned int X, unsigned int Y)
{
	int Value = std::numeric_limits<int>::min();
	
	if (isInputValid(X, Y))
	{
		ptr_Buffer += ((Y - 1) * Pitch) + (X - 1) * sizeDataType;
		Value = *ptr_Buffer;
	}
	ResetBufferPointerBeginning();
	return Value;
}


void CCanvas::Set(unsigned int X, unsigned int Y , int Value)
{
	if(isInputValid(X,Y))
	{
		ptr_Buffer += ((Y - 1) * Pitch) + (X - 1) * sizeDataType;
		*ptr_Buffer = (unsigned char)Value;
	}

	ResetBufferPointerBeginning();
}

/* Imprime todos los valores del arreglo 
   En forma de matrice */

void CCanvas::PrintMatriceValues()
{
	// to know where to place the character '\n'
	unsigned int Count = 0;
	std::cout << "---Here are the values of the matrice--- \n\n";
	while(ptr_Buffer < ptr_Ending)
	{

		if (Count == Rows)
		{
			std::cout << '\n';
			Count = 0;
		}
		std::cout << '[' <<(double)(*ptr_Buffer) << "] ";
		Count++;

		ptr_Buffer += sizeDataType;
	}
	ResetBufferPointerBeginning();

	std::cout <<'\n'<< std::endl;
}

void CCanvas::PrintMatriceAddresses()
{
	// to know where to place the character '\n'
	unsigned int Count = 0;
	std::cout << "---Here are the addresses of the matrice--- \n\n";
	while (ptr_Buffer < ptr_Ending)
	{
		if (Count == Rows)
		{
			std::cout << '\n';
			Count = 0;
		}
		// casting is done so the output is NOT garbage
		std::cout << '[' <<std::hex<<(int)ptr_Buffer << "] ";
		Count++;

		ptr_Buffer += sizeDataType;
	}
	ResetBufferPointerBeginning();

	std::cout << '\n' << std::endl;
}

/* check if the size of the data is in a format we can 
*  use */
bool CCanvas::isDataSizeSupported(unsigned int DataSize)
{
	switch (DataSize)
	{
		case(Formatos::DataSize_1B):
		 formato = DataSize_1B;
		 return true;

		case(Formatos::DataSize_4B):
		 formato = DataSize_4B;
		 return true;

		default:
	   	 formato = Error;
		 std::cerr << "[ERROR] Size of data not Supported for CCanvas";
		 return false;
		break;
	}
}

bool CCanvas::isInputValid(unsigned int X, unsigned int Y)
{
	if (X < 1 || Y < 1) 
	{
		std::cerr << "[ERROR] Input of 'x' or 'y' smaller than 1 \n";
		return false;
	}
	else if (X > Rows)
	{
		std::cerr << "[ERROR] Input of 'x' is Larger than the quantity of rows \n";
		return false;
	}
	else if(Y > Columns)
	{
		std::cerr << "[ERROR] Input of 'Y' is Larger than the quantity of colums \n";
		return false;
	}

	return true;
}

void CCanvas::ResetBufferPointerBeginning()
{
	ptr_Buffer = ptr_Beginning;
}