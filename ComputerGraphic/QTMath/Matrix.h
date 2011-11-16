#include <stdio.h>

#ifndef __MATRIX_H_
#define __MATRIX_H_
class CMatrix {
protected:
	int m_irow;
	int m_icol;
	float* m_fdata;
public:
	CMatrix();
	CMatrix(int row, int col);
	CMatrix(float* arr, int row, int col);
	
	void getfromMatrix(void* arr, int row, int col, bool makeTranspose = false);
	void makeTranspose();

	virtual ~CMatrix();

	int row();
	int col();
	float* getData();

	float det();
	CMatrix invert();

	void loadIdentity();

	void multMatrix(const CMatrix& op);
	void multMatrix(const CMatrix* op);

	CMatrix operator + (const CMatrix& op);
	CMatrix operator + (const CMatrix* op);

	CMatrix operator - (const CMatrix& op);
	CMatrix operator - (const CMatrix* op);

	CMatrix operator * (const CMatrix& op);
	CMatrix operator * (const CMatrix* op);

	void PrintInfo();
};
#endif