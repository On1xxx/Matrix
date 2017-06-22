
#include "matrix.hpp"


/*****************************************************************************/

Matrix::Matrix( int _Rows, int _Collums)
	:Rows(_Rows), Collums(_Collums)
{
	IsValid(_Rows, _Collums);
	
	double * Arr = new  double [_Rows * _Collums];

	for (int i = 0; i < _Rows; i++)
		for (int j = 0; j < _Collums; j++)
			Arr[i*_Collums+j] = 0.0;

	m_data = Arr;

}

Matrix::Matrix(int _Rows, int _Collums, double * _ptr)
	:Rows(_Rows), Collums(_Collums)
{
	IsValid(_Rows, _Collums);
	if (_ptr == nullptr) throw std::logic_error("Bad data pointer");
	else m_data=_ptr;

	
}

void Matrix::IsValid(int _Rows, int _Collums)
{
	if (_Rows <= 0 || _Collums <= 0) throw std::logic_error("Invalid dimensions");
}

Matrix::Matrix(const Matrix & _m)
	: Rows(_m.Rows), Collums(_m.Collums)
{
	m_data = new  double[_m.Rows* _m.Collums];
	
	for (int i = 0; i < _m.Rows; i++)
		for (int j = 0; j < _m.Collums; j++)
			m_data[i*_m.Collums + j] = _m.m_data[i*_m.Collums + j];
}

Matrix::Matrix(Matrix && _m)
	: Rows(std::move(_m.Rows)), Collums(std::move(_m.Collums)), m_data(std::move(_m.m_data))
{}

Matrix::~Matrix()
{}

/*****************************************************************************/
