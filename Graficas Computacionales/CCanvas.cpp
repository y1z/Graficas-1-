#pragma once
#include "CCanvas.h"
// constructor 
CCanvas::CCanvas(uint32_t X, uint32_t Y,uint32_t dataSize, int DefaultValue)
{
	Init(X, Y, dataSize, DefaultValue);
}

CCanvas::CCanvas(uint32_t X, uint32_t Y, uint32_t dataSize, float DefaultValue){
	Init(X, Y, dataSize, DefaultValue);
}

// destructor 
CCanvas::~CCanvas(){

	if (mptr_Buffer != nullptr)
	{
		free(mptr_Buffer);
		mptr_Buffer = nullptr;
	}
	mptr_Beginning = nullptr;
	mptr_Ending = nullptr;
}


/*
int CCanvas::Get(unsigned int X, unsigned int Y)
{
	int Value = std::numeric_limits<int>::min();
	
	if (isInputValid(X, Y))
	{
		mptr_Buffer += ((Y - 1) * m_Pitch) + (X - 1) * m_sizeDataType;
		Value = *mptr_Buffer;
	}
	ResetBufferPointerBeginning();
	return Value;
}*/

float CCanvas::Get(float X, float Y){
	float RetValue = 0.0f;

	if (isInputValid(X, Y))
	{
		// llegar a la fila desiada 
		mptr_Buffer += static_cast<int>((m_RowLength * m_sizeDataType) * X);
		// llegar a la columna desiada 
		mptr_Buffer += static_cast<int>((m_Pitch* (m_ColumnsCount - 1) ) * Y);

		if (formato != Formatos::DataSize_RGBAF32)
		{
			RetValue = static_cast<float> (*mptr_Buffer);
		}
		else
		{
			float *ptr_temp = (float*) mptr_Buffer;
			RetValue = *ptr_temp;
		}
	}
	ResetBufferPointerBeginning();
	return RetValue;
}

/*! Fin a place in the buffer a set a value ther */
void CCanvas::Set(float X, float Y, int Value){
	// llegar a la fila desiada 
	mptr_Buffer += static_cast<int>((m_RowLength * m_sizeDataType) * X);
	// llegar a la columna desiada 
	mptr_Buffer += static_cast<int>((m_Pitch * (m_ColumnsCount - 1)) * Y);

	SetValueByFormat(Value);

	ResetBufferPointerBeginning();
}

void CCanvas::Set(float X, float Y, float Value){
	// llegar a la fila desiada 
	mptr_Buffer += static_cast<int>((m_RowLength * m_sizeDataType) * X);
	// llegar a la columna desiada 
	mptr_Buffer += static_cast<int>((m_Pitch * (m_ColumnsCount - 1)) * Y);

	SetValueByFormat(Value);

	ResetBufferPointerBeginning();
}

/*! Prints all the value in the 
	Buffer */

void CCanvas::PrintMatriceValues()
{
	// to know where to place the character '\n'
	unsigned int Count = 0;
	std::cout << "---Here are the values of the matrice--- \n\n";

	// Interrate though the matrix 
	if (formato != Formatos::DataSize_RGBAF32)
	{
		while(mptr_Buffer < mptr_Ending)
		{

			if (Count == m_RowLength)
			{
				std::cout << '\n';
				Count = 0;
			}
			std::cout << '[' <<(double)(*mptr_Buffer) << "] ";
			Count++;

			mptr_Buffer += m_sizeDataType;
		}

	}
	else
	{
		while(mptr_Buffer < mptr_Ending)
		{

			if (Count == m_RowLength)
			{
				std::cout << '\n';
				Count = 0;
			}
			float *ptr_temp = (float*)mptr_Buffer;

			std::cout << '[' <<*ptr_temp << "] ";
			Count++;

			mptr_Buffer += m_sizeDataType;
		}

	}
	ResetBufferPointerBeginning();

	std::cout <<'\n'<< std::endl;
}

void CCanvas::PrintMatriceAddresses()
{
	// to know where to place the character '\n'
	unsigned int Count = 0;
	std::cout << "---Here are the addresses of the matrice--- \n\n";
	while (mptr_Buffer < mptr_Ending)
	{
		if (Count == m_RowLength)
		{
			std::cout << '\n';
			Count = 0;
		}
		// casting is done so the output is NOT garbage
		std::cout << '[' <<std::hex<<(int)mptr_Buffer << "] ";
		Count++;

		mptr_Buffer += m_sizeDataType;
	}
	ResetBufferPointerBeginning();

	std::cout << '\n' << std::endl;
}

void CCanvas::DrawHLine(uint32_t X, uint32_t Y, uint32_t Length, uint8_t Value)
{
	if (isInputValid(X, Y))
	{
		if (((X - 1) + Length) > m_RowLength)
		{
			std::clog << "[ERROR] Length is too large \n";
		}
		else
		{
			// move pointer to starting position 
			mptr_Buffer += ((Y -1) * m_Pitch) + ((X - 1) * m_sizeDataType);

			for (int i = 0; i < Length; ++i)
			{
				SetValueByFormat(Value);
				mptr_Buffer += m_sizeDataType;
			}
		}
	}
	ResetBufferPointerBeginning();
}

void CCanvas::DrawVLine(uint32_t X, uint32_t Y, uint32_t Length, uint8_t Value)
{
	if (isInputValid(X, Y))
	{
		if (((Y - 1) + Length) > m_ColumnsCount)
		{
			std::clog << "[ERROR] Length is too large \n";
		}
		else
		{
			// move pointer to starting position 
			mptr_Buffer += ((Y -1) * m_Pitch) + ((X - 1) * m_sizeDataType);

			for (int i = 0; i < Length; ++i)
			{
				SetValueByFormat(Value);
				mptr_Buffer += m_Pitch;
			}
		}
	}
	ResetBufferPointerBeginning();
}

void CCanvas::DrawDiagonal(float X1, float Y1,float X2, float Y2, uint8_t Value)
{
	/*Para saber la fila y Columna de Origin*/
	int RowAndColumnsOrigin[2];
	RowAndColumnsOrigin[0] = X1 * m_RowLength;
	RowAndColumnsOrigin[1] = Y1 * m_ColumnsCount;
	/*Para saber la fila y Columna de Destino */

	int RowAndColumnsEnding[2];
	RowAndColumnsEnding[0] = X2 * m_RowLength;
	RowAndColumnsEnding[1] = Y2 * m_ColumnsCount;

	int Avances = RowAndColumnsEnding[0] + RowAndColumnsEnding[1];
	// Mover el puntero de buffer al primer punto 
	mptr_Buffer += RowAndColumnsOrigin[0] * m_sizeDataType;
	mptr_Buffer += RowAndColumnsOrigin[1] * m_Pitch;
	// para saber a donde debe ir el buffer ;
	uint8_t *ptr_EndingPoint = mptr_Beginning;
	ptr_EndingPoint += RowAndColumnsEnding[0] * m_sizeDataType;
	ptr_EndingPoint += RowAndColumnsEnding[1] * m_Pitch;

	// para saber cuantas filas o columnas tengo que avansar 
	int CountEjeX = RowAndColumnsOrigin[0];
	int CountEjeY = RowAndColumnsOrigin[1];

	/*Avansar el buffer y poner el valor si el 
	otro punto esta en un lugar mas adelante del 
	buffer */

	if (mptr_Buffer < ptr_EndingPoint)
	{
		for (uint32_t i = 0; i < Avances; ++i)
		{
			if (CountEjeX < RowAndColumnsEnding[0])
			{
				CountEjeX++;
				SetValueByFormat(Value);
				mptr_Buffer += m_sizeDataType;
			}
			if (CountEjeY < RowAndColumnsEnding[1])
			{
				CountEjeY++;
				SetValueByFormat(Value);
				mptr_Buffer += m_Pitch;
			}
		}
	}
	else
	{
		for (uint32_t i = 0; i <RowAndColumnsOrigin[0] +RowAndColumnsOrigin[1] ; ++i)
		{
			if (CountEjeX > RowAndColumnsEnding[0])
			{
				CountEjeX--;
				SetValueByFormat(Value);
				mptr_Buffer -= m_sizeDataType;
			}
			if (CountEjeY > RowAndColumnsEnding[1])
			{
				CountEjeY--;
				SetValueByFormat(Value);
				mptr_Buffer -= m_Pitch;
			}
		}
	}
	ResetBufferPointerBeginning();
}

void CCanvas::CopyTo(CCanvas& other)
{

		for (float i = 0.00f; i < 1.00f; i += 0.02f)
		{
			for(float j = 0.00f; j < 1.00f; j+= 0.02f)
			{
				auto temp = this->Get(i, j);
				other.Set(i, j, temp);
			}
		}

}

/*! check if the size of the data is in a format we can 
*  use */
bool CCanvas::isDataSizeSupported(uint32_t DataSize)
{
	switch (DataSize)
	{
		// 1 
		case(Formatos::DataSize_R):
		 formato = DataSize_R;
		 return true;

		 // 2
		case(Formatos::DataSize_RG):
			formato = DataSize_RG;
			return true;

			// 3
		case(Formatos::DataSize_RGB):
			formato = DataSize_RGB;
			return true;

		 // 4 
		case(Formatos::DataSize_RGBA):
		 formato = DataSize_RGBA;
		 return true;
		 // 16
		case(Formatos::DataSize_RGBAF32):
			formato = DataSize_RGBAF32;
			return true;

		default:
	   formato = Error;
		 std::cerr << "[ERROR] Size of data not Supported for CCanvas";
		 return false;
		break;
	}
}

bool CCanvas::isInputValid(uint32_t X, uint32_t Y)
{
	if(formato == Formatos::Error)
	{
		std::cerr << "[ERROR] Format of data not supported cannot do ANYTHING \n";
	}

	if (X < 1 || Y < 1) 
	{
		std::cerr << "[ERROR] Input of 'x' or 'y' smaller than 1 \n";
		return false;
	}
	else if (X > m_RowLength)
	{
		std::cerr << "[ERROR] Input of 'x' is Larger than the quantity of rows \n";
		return false;
	}
	else if(Y > m_ColumnsCount)
	{
		std::cerr << "[ERROR] Input of 'Y' is Larger than the quantity of colums \n";
		return false;
	}

	return true;
}

bool CCanvas::isInputValid(float X, float Y)
{
	if (X < 0.0f || Y < 0.0f)
	{
		std::clog << "[ERROR] input of 'x' or 'y' is lesser than 0\n";
		return false;
	}
	else if (X > 1.0f || Y > 1.0f)
	{
		std::clog << "[ERROR] input of 'x' or 'y' is Greater than 0 \n";
		return false;
	}
	return true;
}

void CCanvas::ResetBufferPointerBeginning()
{
	mptr_Buffer = mptr_Beginning;
}

/*! initialize the buffer and prepare other variables 
	for later manipulation of the same buffer 
*/
template <typename T>
void CCanvas::Init(uint32_t X, uint32_t Y, uint32_t dataSize, T DefaultValue)
{

	if (isDataSizeSupported(dataSize))
	{
		m_RowLength = X;
		m_ColumnsCount = Y;
		m_Pitch = dataSize * m_RowLength;

		m_sizeDataType = dataSize;
		m_sizeBuffer = X * Y;

		// create our buffer 
		mptr_Buffer = (unsigned char *) malloc(m_sizeBuffer * dataSize);
		// to reset buffer 
		mptr_Beginning = mptr_Buffer;
		// to Iterate through the buffer 
		mptr_Ending = mptr_Buffer + (m_sizeDataType * m_sizeBuffer);

		// assigns the value to the matrice of the buffer
		while(mptr_Buffer < mptr_Ending)
		{
			SetValueByFormat(DefaultValue);
			mptr_Buffer += m_sizeDataType;
		}
		ResetBufferPointerBeginning();
	}
}

/*!
/param Value es el value que sera asignado en 
diferentes espacios de memoria dependiendo del formato 

*/
template<typename T>
void CCanvas::SetValueByFormat(T Value)
{
	// para que el puntero pueda regresar al su lugar de oringin 
	void * ResetPtr = mptr_Buffer;

	if(formato == Formatos::DataSize_R)
	{
		*mptr_Buffer = Value;
	}

	else if(formato == Formatos::DataSize_RG)
	{
		for (int i = 0; i < 2; ++i)
		{
			*mptr_Buffer = Value;
			mptr_Buffer++;
		}
	}
	else if(formato == Formatos::DataSize_RGB)
	{
		for(int i= 0; i<3;++i)
		{
			*mptr_Buffer = Value;
			mptr_Buffer++;
		}		
	}
	else if(formato == Formatos::DataSize_RGBA)
	{
		for(int i= 0; i<4;++i)
		{
			*mptr_Buffer = Value;
			mptr_Buffer++;
		}		
	}

	else if(formato == Formatos::DataSize_RGBAF32)
	{
		float *ptr_temp = (float*)mptr_Buffer;
		
		for (int i = 0; i < 4; ++i)
		{
			*ptr_temp = Value;
			ptr_temp++;
		}
		ptr_temp = nullptr;
	}

	/*To Reset the buffer to its orinal 
	Position */
	mptr_Buffer = static_cast<unsigned char*> (ResetPtr);
	ResetPtr = nullptr;
}
