
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

/*****************************************************************************/

#include <iostream>
#include <stdexcept> 
#include <iomanip>


/*****************************************************************************/


class Matrix
{
	int Rows;
	int Collums;
	double * m_data;
	
	
	/*-----------------------------------------------------------------*/

public:

	/*------------------------------------------------------------------*/

	template< typename _MatrixType >
	class MatrixRowAccessor
	{
		_MatrixType & m_matrix;
		const int m_rowIndex;

	public:

		MatrixRowAccessor(_MatrixType & _matrix, int _rowIndex)
			: m_matrix(_matrix), m_rowIndex(_rowIndex)
		{
		}

		double operator[] (int _columnIndex) const
		{
			if (m_rowIndex >= m_matrix.Rows || _columnIndex >= m_matrix.Collums
				|| m_rowIndex < 0 || _columnIndex < 0)
				throw std::range_error("Out of range");

			return m_matrix.m_data[m_matrix.Collums * m_rowIndex + _columnIndex];
		}

		double& operator[] (int _columnIndex)
		{
			if (m_rowIndex >= m_matrix.Rows || _columnIndex >= m_matrix.Collums
				|| m_rowIndex < 0 || _columnIndex < 0)
				throw std::range_error("Out of range");

			return m_matrix.m_data[m_matrix.Collums * m_rowIndex + _columnIndex];
		}
	};


	/*****************************************************************************/

	template< typename > friend class MatrixRowAccessor;

	Matrix( int _Rows, int _Collums); 
	Matrix(int _Rows, int _Collums, double *_ptr);
	~Matrix();

	int getNumRows() const;
	int getNumColumns() const;

	void IsValid(int _Rows, int _Collums);


	Matrix(const Matrix & _m);
	Matrix(Matrix && _m);

	Matrix & operator = (const Matrix & _m);
	Matrix & operator = (Matrix && _m);
	Matrix operator+ (const Matrix & _m);
	Matrix & operator+= (const Matrix & _m);
	Matrix & operator-= (const Matrix & _m);
	Matrix operator- (const Matrix & _m);
	bool operator== (const Matrix & _m) const;
	bool operator!= (const Matrix & _m) const;
	Matrix operator* (const Matrix & _m);
	
	Matrix operator* (const double _v);
	Matrix & operator*= (const double _v);

	friend std::ostream &operator<< (std::ostream & o, const Matrix & _m); // перегруженный оператор вывода



	/*------------------------------------------------------------------*/


	MatrixRowAccessor< const Matrix > operator[] (int _rowIndex) const 
	{
		
		if (_rowIndex >= Rows || _rowIndex < 0)
			throw std::logic_error("Out of range");

		return MatrixRowAccessor<const Matrix>( *this, _rowIndex);
	}

	MatrixRowAccessor< Matrix > operator[] (int _rowIndex)
	{

		if (_rowIndex >= Rows || _rowIndex < 0)
			throw std::logic_error("Out of range");

		return MatrixRowAccessor<Matrix>(*this, _rowIndex);
	}

	/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int Matrix::getNumRows() const
{
	return Rows;
}

/*****************************************************************************/

inline
int Matrix::getNumColumns() const
{
	return Collums;
}

/*****************************************************************************/

inline
Matrix & Matrix::operator= (const Matrix & _m)
{

	if (&_m == this)
		return *this;

	Rows = _m.Rows;
	Collums = _m.Collums;

	m_data = new  double[_m.Rows* _m.Collums];

	for (int i = 0; i < _m.Rows; i++)
		for (int j = 0; j < _m.Collums; j++)
			m_data[i*_m.Collums + j] = _m.m_data[i*_m.Collums + j];
	return *this;
}

/*****************************************************************************/

inline
Matrix & Matrix::operator = (Matrix && _m)
{

	if (&_m == this)
		return *this;

	std::swap(Rows, _m.Rows);
	std::swap(Collums, _m.Collums);
	std::swap(m_data, _m.m_data);


	return *this;
}

/*****************************************************************************/

inline 
Matrix & Matrix::operator+= (const Matrix & _m) //оператор сложени€
{
	if (Rows != _m.Rows || Collums != _m.Collums) throw std::logic_error("Size mismatch");
	
	for (int i = 0; i < _m.Rows; i++)
		for (int j = 0; j < _m.Collums; j++)
			m_data[i*_m.Collums + j] = m_data[i*_m.Collums + j] + _m.m_data[i*_m.Collums + j];

	return *this;
}

/*****************************************************************************/

inline
Matrix Matrix::operator+ (const Matrix & _m) // оператор сложени€, результат в новый обьект
{
	Matrix Result = *this;

	if (Rows != _m.Rows || Collums != _m.Collums) throw std::logic_error("Size mismatch");

	Result += _m;

	return Result;
}

/*****************************************************************************/

inline
Matrix & Matrix::operator-= (const Matrix & _m) //оператор вычитани€
{
	if (Rows != _m.Rows || Collums != _m.Collums) throw std::logic_error("Size mismatch");

	for (int i = 0; i < _m.Rows; i++)
		for (int j = 0; j < _m.Collums; j++)
			m_data[i*_m.Collums + j] = m_data[i*_m.Collums + j] - _m.m_data[i*_m.Collums + j];

	return *this;
}

/*****************************************************************************/

inline 
Matrix Matrix::operator - (const Matrix & _m) // оператор вычитани€, результат в новый обьект
{
	Matrix Result = *this;

	if (Rows != _m.Rows || Collums != _m.Collums) throw std::logic_error("Size mismatch");

	Result -= _m;

	return Result;
}



/*****************************************************************************/

inline
Matrix Matrix::operator * (const Matrix & _m) //умножение матриц, результат в новый обьект
{
	Matrix Result(Rows, _m.Collums);

	if (Collums != _m.Rows) throw std::logic_error("Size mismatch");

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < _m.Collums; j++)
		{
			for (int k = 0; k < Collums; k++)
				Result.m_data[_m.Collums * i + j] += m_data[Collums * i + k] * _m.m_data[_m.Collums * k + j];
		}

	return Result;

}

/*****************************************************************************/

inline
Matrix Matrix::operator* (const double _v) //умножение на скал€р
{
	Matrix Result = *this;


	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Collums; j++)
			Result.m_data[i*Collums + j] = m_data[i*Collums + j] * _v;


	return Result;
}

/*****************************************************************************/

inline
Matrix & Matrix::operator*= (const double _v) //умножение на скал€р, результат в новый обьект
{
	
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Collums; j++)
			m_data[i*Collums + j] = m_data[i*Collums + j] * _v;

	return *this;
}

/*****************************************************************************/

inline
bool Matrix::operator== (const Matrix & _m) const // оператор сравнени€
{
	if (Rows != _m.Rows || Collums != _m.Collums)
		return false; // матрицы с разным количеством элементов

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Collums; j++)
			if (m_data[i*_m.Collums + j] != _m.m_data[i*_m.Collums + j])
				return false; // матрицы не равны

	return true; // матрицы равны
}

/*****************************************************************************/

inline
bool Matrix::operator!= (const Matrix & _m) const //оператор "не равно"
{
	return !(*this == _m);
}

/*****************************************************************************/

inline 
std::ostream &operator<< (std::ostream & o, const Matrix & _m) //перегруженый оператор сдвига
{
	
	for (int i = 0; i < _m.Rows; i++)
	{
		for (int j = 0; j < _m.Collums; j++)
		{	
			o  << _m.m_data[i*_m.Collums + j];
			if (j != _m.Collums - 1) o << '\t';
		}
			o << '\n';
	}

	return o;
}
/*****************************************************************************/

#endif //  _MATRIX_HPP_
