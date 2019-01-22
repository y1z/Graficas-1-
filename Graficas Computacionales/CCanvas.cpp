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
			*mptr_Buffer = DefaultValue;
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
}


void CCanvas::Set(unsigned int X, unsigned int Y , int Value)
{
	if(isInputValid(X,Y))
	{
		mptr_Buffer += ((Y - 1) * m_Pitch) + (X - 1) * m_sizeDataType;
		*mptr_Buffer = (unsigned char)Value;
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
				*mptr_Buffer = Value;
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
				*mptr_Buffer = Value;
				mptr_Buffer += m_Pitch;
			}
		}
	}
	ResetBufferPointerBeginning();
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
	if(formato == Formatos::Error)
	{
		std::cerr << "[ERROR] Format of data not soported cannot ANYTHING \n";
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

void CCanvas::ResetBufferPointerBeginning()
{
	mptr_Buffer = mptr_Beginning;
}