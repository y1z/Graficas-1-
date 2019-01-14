#pragma once
#include<iostream>
#include <cstdlib>
#include <limits>
class CCanvas
{
public: // constructor y destructor 
	CCanvas(unsigned int X, unsigned int Y, unsigned int dataSize, int DefaultValue);
	virtual ~CCanvas();


protected:// Variables 
	// para saber el tamaño de nuestro dato 
	unsigned int sizeDataType;
	// para saber el tamaño del buffer 
	unsigned int sizeBuffer = 0;
	// para saber la cantidad de fillas en total 
	unsigned int Rows = 0;
	// para saber la cantidad de columnas en total 
	unsigned int Columns = 0;
	// para saber el tamaño de una fila 
	unsigned long long Pitch = 0;
	// para conocer el inicio y final de nuestro buffer 
	unsigned char *ptr_Beginning = nullptr;
	unsigned char *ptr_Ending = nullptr;
	// Aqui se ubica el buffer 
	unsigned char *ptr_Buffer = nullptr;
protected:
	enum  Formatos : unsigned int
	{
		Error = 0,
		DataSize_1B = 1,
		DataSize_4B = 4
	};

	Formatos formato = Formatos::DataSize_1B;

public:// Funciones 
	// return the value stored on the 'X' and 'Y' 
	// positions 
	int Get(unsigned int X, unsigned int Y);
	// set a value stored on the 'X' and 'Y' positions
	void Set(unsigned int X, unsigned int Y, int Value);
	void PrintMatriceValues();
	void PrintMatriceAddresses();
private:
	bool isDataSizeSupported(unsigned int);
	bool isInputValid(unsigned int, unsigned int);
	void ResetBufferPointerBeginning();

};

