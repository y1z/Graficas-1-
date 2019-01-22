/**
*
*
*
*
*
*
*/

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
	unsigned int m_sizeDataType;
	// para saber el tamaño del buffer 
	unsigned int m_sizeBuffer = 0;
	// para saber la cantidad de fillas en total 
	unsigned int m_Rows = 0;
	// para saber la cantidad de columnas en total 
	unsigned int m_Columns = 0;
	// para saber el tamaño de una fila 
	unsigned long long m_Pitch = 0;
	// para conocer el inicio y final de nuestro buffer 
	unsigned char *mptr_Beginning = nullptr;
	unsigned char *mptr_Ending = nullptr;
	// Aqui se ubica el buffer 
	unsigned char *mptr_Buffer = nullptr;
protected:
	
	enum  Formatos : unsigned int
	{
		Error = 0,
		DataSize_1B = 1,
		DataSize_4B = 4
	};

	Formatos formato = Formatos::DataSize_1B;

public:// Functions for the user 

	// return the value stored on the 'X' and 'Y' 
	// positions 
	int Get(unsigned int X, unsigned int Y);
	// set a value stored on the 'X' and 'Y' positions
	void Set(unsigned int X, unsigned int Y, int Value);
	// print values store in the matrice 
	void PrintMatriceValues();
	// print the addresses 
	void PrintMatriceAddresses();
	// fills a row with a value 
	void DrawHLine(unsigned int X, unsigned int Y, unsigned int Length , int Value);
	// fills a column with a value 
	void DrawVLine(unsigned int X, unsigned int Y, unsigned int Length , int Value);
private:// Funtions to help other functions 
	bool isDataSizeSupported(unsigned int);
	bool isInputValid(unsigned int, unsigned int);
	void ResetBufferPointerBeginning();

};
