/*!
	\class CCanvas 
	The Canvas is an interface for manipulation of a buffer .
	
*/

#pragma once
#include<iostream>
#include <cstdlib>
#include <cinttypes>
#include <limits>

class CCanvas
{
public: // constructor y destructor 
	CCanvas(uint32_t X, uint32_t Y, uint32_t dataSize, int DefaultValue);
	CCanvas(uint32_t X, uint32_t Y, uint32_t dataSize, float DefaultValue);
	virtual ~CCanvas();
protected:// Variables 
	
	uint32_t m_sizeDataType;/*!<To know how much memory are cells take up */
	
	uint32_t m_sizeBuffer = 0;/*!<To know how many cells the buffer takes up  */

	uint32_t m_RowLength = 0;/*!< To know how many Rows existe per column*/

	uint32_t m_ColumnsCount = 0;/*!<para saber la cantidad de columnas en total */

	uint64_t m_Pitch = 0;/*!<To have the ability to move 1 column in the buffer */

	uint8_t *mptr_Beginning = nullptr;/*!<To know where are buffer begins and reset the buffer ptr*/
	uint8_t *mptr_Ending = nullptr;/*!<To iterate through the buffer without going out of bounds */
	uint8_t *mptr_Buffer = nullptr;/*!<The ptr to the buffer itself  */
protected:
	
	enum  Formatos : unsigned int
	{
		Error = 0,
		DataSize_R = 1,
		DataSize_RG = 2,
		DataSize_RGB = 3,
		DataSize_RGBA = 4,

		DataSize_RGBAF32 = 16
	};

	Formatos formato = Formatos::DataSize_R;//<! Aqui se declara un valor por defecto 
public:// Functions for the user 

	//!Encuentra el value que esta en 'X' y 'Y' 
	//! Para retornarlo 
	float Get(float X, float Y);
	//! Usando la pose 'X' cobinado con 'Y' para encontra una celda 
	//! cambiar el valor que esta dentro de la misma 
	void Set(float X, float Y, int Value);
	void Set(float X, float Y, float Value);
	//! imprime los valores de la matrice 
	void PrintMatriceValues();
	//! imprime las direcciones de memoria 
	void PrintMatriceAddresses();
	//! fills a row with a value 
	void DrawHLine(uint32_t X, uint32_t Y, uint32_t Length, uint8_t Value);
	//! fills a column with a value 
	void DrawVLine(uint32_t X, uint32_t Y, uint32_t Length, uint8_t Value);
	//! filla row and column in a way to make a line 
	void DrawDiagonal(float X1, float Y1,float X2, float Y2, uint8_t Value);
	//! Copies Value of 1 buffer to a different buffer 
	void CopyTo(CCanvas&);
private:// Funtions to help other functions 

	bool isDataSizeSupported(uint32_t);

	bool isInputValid(uint32_t, uint32_t);
	bool isInputValid(float, float);

	void ResetBufferPointerBeginning();
	//! Asigna valores dependiendo del formato 
	template<typename T>
	void SetValueByFormat(T Value);

	template<typename T>
	void Init(uint32_t X, uint32_t Y, uint32_t dataSize, T DefaultValue);

};

