#include "CCanvas.h"
// constructor 
CCanvas::CCanvas(unsigned int X, unsigned int Y,unsigned int dataSize, int DefaultValue)
{

	if (isDataSizeSupported(dataSize))
	{
		m_Rows = X;
		m_Columns = Y;
		m_Pitch = dataSize * m_Rows;

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
			FormatoSetValue(DefaultValue);
			mptr_Buffer += m_sizeDataType;
		}
		ResetBufferPointerBeginning();
	}
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

int CCanvas::Get(float X, float Y){

	int RetValue = std::numeric_limits<unsigned char>::min();

	if (isInputValid(X, Y))
	{
		// llegar a la fila desiada 
		mptr_Buffer += static_cast<int>((m_Rows * m_sizeDataType) * X);
		// llegar a la columna desiada 
		mptr_Buffer += static_cast<int>((m_Pitch* (m_Columns - 1) ) * Y);

		RetValue = *mptr_Buffer;
	}
	ResetBufferPointerBeginning();

	return RetValue;
}


void CCanvas::Set(unsigned int X, unsigned int Y , int Value)
{
	if(isInputValid(X,Y))
	{
		mptr_Buffer += ((Y - 1) * m_Pitch) + (X - 1) * m_sizeDataType;
		FormatoSetValue(Value);
	}
	ResetBufferPointerBeginning();
}

void CCanvas::Set(float X, float Y, int Value){
	// llegar a la fila desiada 
	mptr_Buffer += static_cast<int>((m_Rows * m_sizeDataType) * X);
	// llegar a la columna desiada 
	mptr_Buffer += static_cast<int>((m_Pitch * (m_Columns - 1)) * Y);

	FormatoSetValue(Value);

	ResetBufferPointerBeginning();
}

/* Imprime todos los valores del arreglo 
   En forma de matrice */

void CCanvas::PrintMatriceValues()
{
	// to know where to place the character '\n'
	unsigned int Count = 0;
	std::cout << "---Here are the values of the matrice--- \n\n";

	// Interrate though the matrix 
	while(mptr_Buffer < mptr_Ending)
	{

		if (Count == m_Rows)
		{
			std::cout << '\n';
			Count = 0;
		}
		std::cout << '[' <<(double)(*mptr_Buffer) << "] ";
		Count++;

		mptr_Buffer += m_sizeDataType;
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
		if (Count == m_Rows)
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

void CCanvas::DrawHLine(unsigned int X, unsigned int Y, unsigned int Length, int Value)
{
	if (isInputValid(X, Y))
	{
		if (((X - 1) + Length) > m_Rows)
		{
			std::clog << "[ERROR] Length is too large \n";
		}
		else
		{
			// move pointer to starting position 
			mptr_Buffer += ((Y -1) * m_Pitch) + ((X - 1) * m_sizeDataType);

			for (int i = 0; i < Length; ++i)
			{
				FormatoSetValue(Value);
				mptr_Buffer += m_sizeDataType;
			}
		}
	}
	ResetBufferPointerBeginning();
}

void CCanvas::DrawVLine(unsigned int X, unsigned int Y, unsigned int Length, int Value)
{
	if (isInputValid(X, Y))
	{
		if (((Y - 1) + Length) > m_Columns)
		{
			std::clog << "[ERROR] Length is too large \n";
		}
		else
		{
			// move pointer to starting position 
			mptr_Buffer += ((Y -1) * m_Pitch) + ((X - 1) * m_sizeDataType);

			for (int i = 0; i < Length; ++i)
			{
				FormatoSetValue(Value);
				mptr_Buffer += m_Pitch;
			}
		}
	}
	ResetBufferPointerBeginning();
}

void CCanvas::CopyTo(CCanvas& other)
{
	float intercambio = 0.00f;
	for (float i = 0.00f; i < 1.00f; i += 0.02f)
	{
		for(float j = 0.00f; j < 1.00f; j+= 0.02f)
		{
			
		}
	}

}

/* check if the size of the data is in a format we can 
*  use */
bool CCanvas::isDataSizeSupported(unsigned int DataSize)
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

		default:
	   formato = Error;
		 std::cerr << "[ERROR] Size of data not Supported for CCanvas";
		 return false;
		break;
	}
}

bool CCanvas::isInputValid(unsigned int X, unsigned int Y)
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
	else if (X > m_Rows)
	{
		std::cerr << "[ERROR] Input of 'x' is Larger than the quantity of rows \n";
		return false;
	}
	else if(Y > m_Columns)
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

/*!

	/param Value es el value que sera asignado en 
	diferentes espacios de memoria dependiendo del formato 

*/
void CCanvas::FormatoSetValue(int Value)
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


	mptr_Buffer = static_cast<unsigned char*> (ResetPtr);
	ResetPtr = nullptr;
}